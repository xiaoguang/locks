#include <cstdint>
#include <assert.h>
#include "MutexLock.hpp"
#include "SpinLock.hpp"
#include "PeekSpinLock.hpp"
#include "MCSLock.hpp"
#include "TicketLock.hpp"

using lock::Lock;
using lock::MutexLock;
using lock::SpinLock;
using lock::PeekSpinLock;
using lock::MCSLock;
using lock::TicketLock;

namespace lock {

class LockBenchmark {

 public:

  LockBenchmark() : _count(0) {}
  LockBenchmark(Lock * lock) : _count(0), _lock(lock) {}
  ~LockBenchmark() {}

  inline uint64_t count() const { return _count; }

  void correctness(int times) {
    assert(times > 0);
    for(int i = 0; i < times; i++) {
      _lock->lock();
      for (int j = 0; j < 1024; j++) _count++;
      _lock->unlock();
    }
  }

 private:
  uint64_t _count;
  Lock * _lock;

};

}
