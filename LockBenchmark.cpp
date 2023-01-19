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
  inline TicksClock::Ticks totalTicks() const { return _stats._totalTicks; }
  inline TicksClock::Ticks unlockTicks() const { return _stats._unlockTicks; }
  inline TicksClock::Ticks lockTicks() const { return _stats._lockTicks; }
  inline TicksClock::Ticks workTicks() const { return _stats._workTicks; }

  void correctness(int times, int workLoad, bool metrics) {
    for(int i = 0; i < times; i++) {
      if(!metrics) {
        ScopedLock sl(_lock);
        for(int j = 0; j < workLoad; j++) _count++;
        continue;
      }

      // lock stats
      {
        TicksClock::Ticks ltb = TicksClock::getTicks();
        _lock->lock();
        TicksClock::Ticks ltd = TicksClock::getTicks() - ltb;
        _stats._lockTicks += ltd;
        _stats._totalTicks += ltd;
      }
      // work stats
      {
        TicksClock::Ticks wtb = TicksClock::getTicks();
        for(int j = 0; j < workLoad; j++) _count++;
        TicksClock::Ticks wtd = TicksClock::getTicks() - wtb;
        _stats._workTicks += wtd;
        _stats._totalTicks += wtd;
      }
      // unlock stats
      {
        TicksClock::Ticks utb = TicksClock::getTicks();
        _lock->unlock();
        TicksClock::Ticks utd = TicksClock::getTicks() - utb;
        _stats._unlockTicks += utd;
        _stats._totalTicks += utd;
      }
    }
  }

 private:
  uint64_t _count;
  BaseLock* _lock;
  Stats _stats;
};

}
