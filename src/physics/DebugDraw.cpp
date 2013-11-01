#include "physics/DebugDraw.hpp"
#include "Application.hpp"
#include <SDL2_gfxPrimitives.h>

namespace RubyAction
{
namespace Physics
{

  DebugDraw::DebugDraw(mrb_value self)
    : Sprite::Sprite(self)
  {
    this->SetFlags(e_shapeBit | e_jointBit | e_aabbBit | e_pairBit | e_centerOfMassBit);
  }

  void DebugDraw::render(SDL_Renderer* renderer)
  {
    for (std::vector<DrawFunc>::iterator func = this->funcs.begin(); func != this->funcs.end(); ++func)
    {
      (*func)(renderer);
      SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    }
    this->funcs.clear();
  }

  void DebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
  {
    Sint16 *vx = new Sint16[vertexCount];
    Sint16 *vy = new Sint16[vertexCount];

    for (int i = 0; i < vertexCount; i++)
    {
      vx[i] = vertices[i].x;
      vy[i] = 600 - vertices[i].y;
    }

    this->funcs.push_back(
      [&, vx, vy, vertexCount, color](SDL_Renderer* renderer) {
        polygonRGBA(renderer, vx, vy, vertexCount, 255*color.r, 255*color.g, 255*color.b, 255);
        delete vx;
        delete vy;
      }
    );
  }

  void DebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
  {
    Sint16 *vx = new Sint16[vertexCount];
    Sint16 *vy = new Sint16[vertexCount];

    for (int i = 0; i < vertexCount; i++)
    {
      vx[i] = vertices[i].x;
      vy[i] = 600 - vertices[i].y;
    }

    this->funcs.push_back(
      [&, vx, vy, vertexCount, color](SDL_Renderer* renderer) {
        filledPolygonRGBA(renderer, vx, vy, vertexCount, 255*color.r, 255*color.g, 255*color.b, 255);
        delete vx;
        delete vy;
      }
    );
  }

  void DebugDraw::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
  {
    this->funcs.push_back(
      [&, center, radius, color](SDL_Renderer* renderer) {
        ellipseRGBA(renderer, center.x, center.y, radius, radius, 255*color.r, 255*color.g, 255*color.b, 255);
      }
    );
  }

  void DebugDraw::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
  {
    this->funcs.push_back(
      [&, center, radius, axis, color](SDL_Renderer* renderer) {
        filledEllipseRGBA(renderer, center.x, center.y, radius, radius, 255*color.r, 255*color.g, 255*color.b, 255);
      }
    );
  }

  void DebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
  {
    this->funcs.push_back(
      [&, p1, p2, color](SDL_Renderer* renderer) {
        lineRGBA(renderer, p1.x, p1.y, p2.x, p2.y, 255*color.r, 255*color.g, 255*color.b, 255);
      }
    );
  }

  void DebugDraw::DrawTransform(const b2Transform& xf)
  {
    this->funcs.push_back(
      [xf](SDL_Renderer* renderer) {
        float rx, ry;

        b2Rot redRot = xf.q;
        rx = redRot.c * TRANSFORM_LEN;
        ry = redRot.s * TRANSFORM_LEN;
        lineRGBA(renderer, xf.p.x, 600 - xf.p.y, xf.p.x + rx, 600 - xf.p.y - ry, 255, 0, 0, 255);

        b2Rot greenRot(redRot.GetAngle() - 90 * 3.14159 / 180.);
        rx = greenRot.c * TRANSFORM_LEN;
        ry = greenRot.s * TRANSFORM_LEN;
        lineRGBA(renderer, xf.p.x, 600 - xf.p.y, xf.p.x + rx, 600 - xf.p.y - ry, 0, 255, 0, 255);
      }
    );
  }

  static mrb_value DebugDraw_initialize(mrb_state *mrb, mrb_value self)
  {
    SET_INSTANCE(self, new DebugDraw(self));
    return self;
  }

  void bindDebugDraw(mrb_state *mrb, RClass *module, RClass *physics)
  {
    struct RClass *super = mrb_class_get_under(mrb, module, "Sprite");
    struct RClass *clazz = mrb_define_class_under(mrb, physics, "DebugDraw", super);
    MRB_SET_INSTANCE_TT(clazz, MRB_TT_DATA);

    mrb_define_method(mrb, clazz, "initialize", DebugDraw_initialize, MRB_ARGS_NONE());
  }

}
}
