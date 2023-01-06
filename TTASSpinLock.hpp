#ifndef __TTAS_SPINLOCK_HPP__
#define __TTAS_SPINLOCK_HPP__
#include "Lock.hpp"

namespace lock {

class TTASSpinLock : public BaseLock {
 public:
  explicit TTASSpinLock() : _locked(false) {}
  ~TTASSpinLock() {}

  virtual void lock() {
    while(true) {
      while(_locked) {}
      if(!__sync_lock_test_and_set(&_locked, true))
        return;
    }
  }

  virtual void unlock() {
    __sync_lock_release(&_locked);
  }

 private:
  bool _locked;
  TTASSpinLock(TTASSpinLock &);
  TTASSpinLock& operator=(TTASSpinLock &);
};

}

#endif
