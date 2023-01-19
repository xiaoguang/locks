#ifndef __LOCK_STATS_HPP__
#define __LOCK_STATS_HPP__

#include "TicksClock.hpp"

namespace lock {

struct Stats {
  Stats(pthread_t owner) {
    _owner = owner;
    _totalTicks  = 0;
    _workTicks   = 0;
    _lockTicks   = 0;
    _unlockTicks = 0;
  }

  ~Stats() {}

  pthread_t _owner;
  TicksClock::Ticks _totalTicks;
  TicksClock::Ticks _workTicks;
  TicksClock::Ticks _lockTicks;
  TicksClock::Ticks _unlockTicks;
};

}

#endif
