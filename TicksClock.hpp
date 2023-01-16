#ifndef __LOCK_TICKS_CLOCK_HPP__
#define __LOCK_TICKS_CLOCK_HPP__

#include <time.h>
#include <inttypes.h>
#include <pthread.h>

namespace lock {
// The TicksClock is a very low overhead to measure elapsed time at
// the nanosecond granularity. It uses the CPU's internal timestamp
// counter.
//
// Usage:
// Measure how long a given computation takes
//    Ticks before = TicksClock::getTicks();
//    .... do computation ...
//    Ticks duration = TicksClock::getTicks() - before;
//
//    double in_seconds = duration / TicksClock::ticksPerSecond();
//

class TicksClock {
 public:
  typedef uint64_t Ticks;
  static double ticksPerSecond();
  static Ticks getTicks() {
    #if defined(__i386__) || defined(__x86_64__)
    uint32_t hi;
    uint32_t lo;
    __asm__ __volatile__ ("rdtsc" : "=a"(lo), "=d"(hi));
    return (uint64_t)hi << 32 | lo;
    #else
    return 0;
    #endif
  }

 private:
  static pthread_once_t _onceControl;
  TicksClock() {}
  ~TicksClock() {}

  // Non-copyable, non-assignable
  TicksClock(TicksClock&);
  TicksClock& operator=(TicksClock&);
};

}

#endif
