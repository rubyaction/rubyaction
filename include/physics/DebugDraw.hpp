#ifndef __PHYSICS_DEBUG_DRAW__
#define __PHYSICS_DEBUG_DRAW__

#include "Sprite.hpp"
#include <Box2D.h>
#include <functional>
#include <vector>

namespace RubyAction
{
namespace Physics
{

  class DebugDraw : public Sprite,
                    public b2Draw
  {
  private:
    static const int TRANSFORM_LEN = 20;

    typedef std::function<void(SDL_Renderer*)> DrawFunc;
    std::vector<DrawFunc> funcs;
  public:
    DebugDraw(mrb_value);
    virtual void render(SDL_Renderer *);
    virtual void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
    virtual void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
    virtual void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color);
    virtual void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color);
    virtual void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color);
    virtual void DrawTransform(const b2Transform& xf);
  };

  void bindDebugDraw(mrb_state*, RClass*, RClass*);

}
}

#endif // __PHYSICS_DEBUG_DRAW__
