#ifndef __TEXTURE_BASE__
#define __TEXTURE_BASE__

#include "RubyObject.hpp"
#include <mruby.h>

namespace RubyAction
{

  class TextureBase : public RubyObject
  {
  protected:
    int width;
    int height;
  public:
    TextureBase(mrb_value);
    int getWidth();
    int getHeight();
  };

  void bindTextureBase(mrb_state*, RClass*);

}

#endif // __TEXTURE_BASE__
