#ifndef __FONT__
#define __FONT__

#include "BaseFont.hpp"

namespace RubyAction
{

  class Font : public BaseFont
  {
  public:
    Font(mrb_value, const char *, const char *);
  };

  void bindFont(mrb_state*, RClass*);

}

#endif // __FONT__
