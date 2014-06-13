#include "Texture.hpp"
#include "Application.hpp"
#include <FreeImagePLus.h>

using namespace RubyAction;

Texture::Texture(mrb_value self, const char *filename) : TextureBase(self)
{
  // load image
  fipImage *image = new fipImage();
  if (!image->load(filename))
  {
    mrb_raise(RubyEngine::getInstance()->getState(), E_TYPE_ERROR, "Error on load the texture.");
  }
  if (!image->convertTo32Bits())
  {
    mrb_raise(RubyEngine::getInstance()->getState(), E_TYPE_ERROR, "Error on convert the texture.");
  }
  if (!image->flipVertical())
  {
    mrb_raise(RubyEngine::getInstance()->getState(), E_TYPE_ERROR, "Error on flip the texture.");
  }

  // load image info
  this->width = image->getWidth();
  this->height = image->getHeight();

  // create texture
  SDL_Renderer *renderer = Application::getInstance()->getRenderer();
  Uint32 format = SDL_PIXELFORMAT_ARGB8888;
  Uint32 access = SDL_TEXTUREACCESS_STATIC;
  this->texture = SDL_CreateTexture(renderer, format, access, this->width, this->height);

  // load texture
  SDL_Rect rect = { 0, 0, this->width, this->height };
  SDL_UpdateTexture(this->texture, &rect, image->accessPixels(), image->getLine());

  // delete image
  delete image;
}

Texture::~Texture()
{
  SDL_DestroyTexture(texture);
}

void Texture::render(SDL_Renderer *renderer, const SDL_Rect *srcrect, const SDL_Rect *dstrect)
{
  SDL_RenderCopy(renderer, texture, srcrect, dstrect);
}

static mrb_value Texture_initialize(mrb_state *mrb, mrb_value self)
{
  const char *filename;
  size_t length;
  mrb_get_args(mrb, "s", &filename, &length);

  SET_INSTANCE(self, new Texture(self, filename))
  return self;
}

void RubyAction::bindTexture(mrb_state *mrb, RClass *module)
{
  struct RClass *super = mrb_class_get_under(mrb, module, "TextureBase");
  struct RClass *clazz = mrb_define_class_under(mrb, module, "Texture", super);
  MRB_SET_INSTANCE_TT(clazz, MRB_TT_DATA);

  mrb_define_method(mrb, clazz, "initialize", Texture_initialize, MRB_ARGS_REQ(1));
}
