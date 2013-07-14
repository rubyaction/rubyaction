#include "Clock.hpp"
#include <mach/mach_time.h>
#include <ctime>


namespace RubyAction
{

  Clock::Clock(int fps): step(1000000.0 / fps)
  {
    last = mach_absolute_time();
  }

  void Clock::tick()
  {
    mach_timebase_info_data_t info;
    mach_timebase_info(&info);

    uint64_t duration = mach_absolute_time() - last;
    duration *= info.numer;
    duration /= info.denom;
    duration /= 1000; // from nanoseconds to microseconds

    long timeToSleep = step - duration;

    if (timeToSleep > 0.0) usleep(timeToSleep);

    last = mach_absolute_time();
  }

}
