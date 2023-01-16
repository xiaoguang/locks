#include "TicksClock.hpp"

namespace lock {

static double _ticksPerSecond = 0;

void moduleInit() {
  struct timespec ts;
  ts.tv_sec = 0;
  ts.tv_nsec = 500000000; // 500 ms
  TicksClock::Ticks before = TicksClock::getTicks();
  nanosleep(&ts, NULL);
  TicksClock::Ticks after = TicksClock::getTicks();
  _ticksPerSecond = (after - before) * 2;
}

pthread_once_t TicksClock::_onceControl = PTHREAD_ONCE_INIT;

double TicksClock::ticksPerSecond() {
  pthread_once(&_onceControl, moduleInit);
  return _ticksPerSecond;
}

}
