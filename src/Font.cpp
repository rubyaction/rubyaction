#include "Font.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
using namespace RubyAction;

bool startsWith(string line, string prefix)
{
  return (line.substr(0, prefix.size()) == prefix) && isspace(line[prefix.size()]);
}

vector<string> split(string line, char delim)
{
  vector<string> tokens;
  stringstream ss(line);
  string item;
  while (getline(ss, item, delim))
  {
    if (!item.empty()) tokens.push_back(item);
  }
  return tokens;
}

map<string, int> getParams(string line)
{
  map<string, int> params;
  vector<string> tokens = split(line, ' ');
  for(vector<string>::size_type i = 1; i != tokens.size(); i++)
  {
    vector<string> keyValue = split(tokens[i], '=');
    params[keyValue[0]] = atoi(keyValue[1].c_str());
  }
  return params;
}

Font::Font(mrb_value self, const char *descriptor, const char *filename)
  : FontBase(self)
{
  ifstream is(descriptor);
  string line;
  while (getline(is, line))
  {
    if (startsWith(line, "info"))
    {
      map<string, int> params = getParams(line);
      fontInfo.size = params["size"];
      fontInfo.smooth = params["smooth"];
    }
    else if (startsWith(line, "common"))
    {
      map<string, int> params = getParams(line);
      fontInfo.height = params["lineHeight"];
      fontInfo.ascender = params["base"];
    }
    else if (startsWith(line, "char"))
    {
      map<string, int> params = getParams(line);
      char chr = static_cast<char>(params["id"]);
      fontInfo.glyphs[chr] = { chr,
        params["x"], params["y"],
        params["width"], params["height"],
        params["xoffset"], params["yoffset"] - (fontInfo.height - fontInfo.ascender),
        params["xadvance"]
      };
    }
  }

  texture.loadFromFile(filename);
  texture.setSmooth(fontInfo.smooth);
  sprite.setTexture(texture);
}

void Font::render(sf::RenderTarget& target, const sf::Transform& transform, const sf::IntRect& bounds,
  const sf::Color& color, const char *text)
{
  sf::IntRect textBounds = getTextBounds(text);

  sf::Transform glyphTransform;
  glyphTransform.translate(-textBounds.left, -textBounds.top);
  // glyphTransform.scale(float(bounds.width) / width, float(bounds.height) / height);

  for (int i = 0; i < strlen(text); ++i)
  {
    TextureGlyph glyph = fontInfo.glyphs[text[i]];
    sprite.setColor(color);
    sprite.setTextureRect(sf::IntRect(glyph.x, glyph.y, glyph.width, glyph.height));

    glyphTransform.translate(glyph.left, glyph.top);
    target.draw(sprite, transform * glyphTransform);
    glyphTransform.translate(glyph.advancex - glyph.left, -glyph.top);
  }
}

sf::IntRect Font::getTextBounds(const char *text)
{
  sf::IntRect bounds;
  for (int i = 0; i < strlen(text); ++i)
  {
    TextureGlyph glyph = fontInfo.glyphs[text[i]];
    if (i == 0) bounds.left = glyph.left;
    bounds.top = min(bounds.top, glyph.top);
    bounds.width += glyph.advancex;
    bounds.height = max(bounds.height, glyph.height + glyph.top);
  }
  return bounds;
}

static mrb_value Font_initialize(mrb_state *mrb, mrb_value self)
{
  const char *descriptor;
  const char *texture;
  size_t length; // unused
  mrb_get_args(mrb, "ss", &descriptor, &length, &texture, &length);

  wrap(self, new Font(self, descriptor, texture));
  return self;
}

void RubyAction::bindFont(mrb_state *mrb, RClass *module)
{
  struct RClass *super = mrb_class_get_under(mrb, module, "FontBase");
  struct RClass *clazz = mrb_define_class_under(mrb, module, "Font", super);
  MRB_SET_INSTANCE_TT(clazz, MRB_TT_DATA);

  mrb_define_method(mrb, clazz, "initialize", Font_initialize, MRB_ARGS_REQ(2));
}
