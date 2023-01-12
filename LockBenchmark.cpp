#include <cstdint>
#include <assert.h>
#include "Config.hpp"
#include "MutexLock.hpp"
#include "SpinLock.hpp"
#include "TTASSpinLock.hpp"
#include "AArrayLock.hpp"
#include "ArrayLock.hpp"
#include "TicketLock.hpp"
#include "VirtualQueueLock.hpp"

using lock::BaseLock;
using lock::MutexLock;
using lock::SpinLock;
using lock::TTASSpinLock;
using lock::AArrayLock;
using lock::ArrayLock;
using lock::TicketLock;
using lock::VirtualQueueLock;

namespace lock {

class LockBenchmark {
 public:
  LockBenchmark() : _count(0) {}
  LockBenchmark(BaseLock* lock) : _count(0), _lock(lock) {}
  ~LockBenchmark() {}

  inline uint64_t count() const { return _count; }

  void correctness(int times) {
    for(int i = 0; i < times; i++) {
      ScopedLock sl(_lock);
      for (int j = 0; j < WORK_LOAD; j++) _count++;
    }
  }

 private:
  uint64_t _count;
  BaseLock* _lock;

};

}
