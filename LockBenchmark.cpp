#include <cstdint>
#include <assert.h>
#include "Stats.hpp"
#include "MutexLock.hpp"
#include "SpinLock.hpp"
#include "TTASSpinLock.hpp"
#include "AArrayLock.hpp"
#include "ArrayLock.hpp"
#include "TicketLock.hpp"
#include "VirtualQueueLock.hpp"
#include "MCSQueueLock.hpp"
#include "TicksClock.hpp"

using lock::BaseLock;
using lock::MutexLock;
using lock::SpinLock;
using lock::TTASSpinLock;
using lock::AArrayLock;
using lock::ArrayLock;
using lock::TicketLock;
using lock::VirtualQueueLock;
using lock::MCSQueueLock;
using lock::TicksClock;
using lock::Stats;

namespace lock {

class LockBenchmark {
 public:
  LockBenchmark(BaseLock* lock) : _count(0), _lock(lock), _stats(Stats(-1)) {}
  ~LockBenchmark() {}

  inline uint64_t count() const { return _count; }
  inline TicksClock::Ticks unlockTicks() const { return _stats._unlockTicks; }
  inline TicksClock::Ticks lockTicks() const { return _stats._lockTicks; }
  inline TicksClock::Ticks workTicks() const { return _stats._workTicks; }

  void correctness(int times) {
    for(int i = 0; i < times; i++) {
      // ScopedLock sl(_lock);

      // lock stats
      /*
      {
        TicksClock::Ticks before = TicksClock::getTicks();
        TicksClock::Ticks duration = TicksClock::getTicks() - before;
        _stats._lockTicks += duration;
      }
      */
      _lock->lock();

      // work stats
      {
        TicksClock::Ticks before = TicksClock::getTicks();
        for (int j = 0; j < WORK_LOAD; j++) _count++;
        TicksClock::Ticks duration = TicksClock::getTicks() - before;
        _stats._workTicks += duration;
      }

      // unlock stats
      {
        TicksClock::Ticks before = TicksClock::getTicks();
        _lock->unlock();
        TicksClock::Ticks duration = TicksClock::getTicks() - before;
        _stats._unlockTicks += duration;
      }
    }
  }

 private:
  uint64_t _count;
  BaseLock* _lock;
  Stats _stats;
};

}
