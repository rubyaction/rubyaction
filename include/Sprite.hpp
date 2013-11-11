#ifndef __SPRITE__
#define __SPRITE__

#include "EventDispatcher.hpp"
#include <SDL.h>

namespace RubyAction
{

  class Sprite : public EventDispatcher
  {
  private:
    int x;
    int y;
    int width;
    int height;
    float scaleX;
    float scaleY;
    float anchorX;
    float anchorY;
    float rotation;
    bool visible;
  protected:
    virtual void renderMe(SDL_Renderer *) {};
  public:
    Sprite(mrb_value);
    int getX();
    void setX(int);
    int getY();
    void setY(int);
    int getWidth();
    void setWidth(int);
    int getHeight();
    void setHeight(int);
    float getScaleX();
    void setScaleX(float);
    float getScaleY();
    void setScaleY(float);
    float getAnchorY();
    void setAnchorY(float);
    float getAnchorX();
    void setAnchorX(float);
    float getRotation();
    void setRotation(float);
    bool isVisible();
    void setVisible(bool);
    Sprite* getParent();
    void setParent(Sprite*);
    void addChild(mrb_value);
    void removeChild(mrb_value);
    void removeFromParent();
    SDL_Point globalToLocal(SDL_Point);
    bool collide(SDL_Point);
    virtual void render(SDL_Renderer *);
    virtual void dispatch(mrb_sym, mrb_value*, int);
  };

  void bindSprite(mrb_state*, RClass*);

}

#endif // __SPRITE__
