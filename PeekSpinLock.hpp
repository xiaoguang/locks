#ifndef __PEEK_SPINLOCK_HPP__
#define __PEEK_SPINLOCK_HPP__
#include "Lock.hpp"

namespace lock {

class PeekSpinLock : public Lock {
 public:
  PeekSpinLock() : _locked(false) {}
  ~PeekSpinLock() {}

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
  int _locked;
  PeekSpinLock(PeekSpinLock &);
  PeekSpinLock & operator=(PeekSpinLock &);
};

}

#endif
