#ifndef __CLOCK__
#define __CLOCK__

#include <stdint.h>

namespace RubyAction
{

  class Clock
  {
  private:
    uint64_t step;
    uint64_t last;

  public:
    Clock(int);
    void tick();
  };

}

#endif // __CLOCK__
