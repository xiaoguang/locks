#ifndef __SPINLOCK_HPP__
#define __SPINLOCK_HPP__
#include "Lock.hpp"

namespace lock {

class SpinLock : public BaseLock {
 public:
  explicit SpinLock() : _locked(false) {}
  ~SpinLock() {}

  virtual void lock() {
    while(__sync_lock_test_and_set(&_locked, true)) {}
  }

  virtual void unlock() {
    __sync_lock_release(&_locked);
  }

 private:
  bool _locked;
  SpinLock(SpinLock & l);
  SpinLock& operator=(SpinLock &);
};

}

#endif
