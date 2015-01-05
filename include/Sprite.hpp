#ifndef __SPRITE__
#define __SPRITE__

#include "EventDispatcher.hpp"
#include <SFML/Graphics.hpp>

namespace RubyAction
{

  class Sprite : public EventDispatcher
  {
  private:
    float x;
    float y;
    int width;
    int height;
    float scaleX;
    float scaleY;
    float anchorX;
    float anchorY;
    float rotation;
    bool visible;
    sf::Transform transform;
  protected:
    virtual void renderMe(sf::RenderTarget *) {};
    const sf::Transform& getTransform();
  public:
    Sprite(mrb_value);
    float getX();
    void setX(float);
    float getY();
    void setY(float);
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
    virtual void addChild(mrb_value);
    virtual void removeChild(mrb_value);
    void removeFromParent();
    bool contains(mrb_value);
    void globalToLocal(float gx, float gy, float* x, float* y);
    bool collide(float gx, float gy);
    virtual void render(sf::RenderTarget *);
    virtual void dispatch(mrb_sym, mrb_value* = NULL, int = 0);
  };

  void bindSprite(mrb_state*, RClass*);

}

#endif // __SPRITE__
