
#ifndef __LOCK_HPP__
#define __LOCK_HPP__

#include <iostream>
#include <cstdlib>
#include "Config.hpp"

using std::cout;
using std::endl;

namespace lock {

class BaseLock {
 // interface pure virtual functions
 public:
  virtual void lock() = 0;
  virtual void unlock() = 0;
};

class ScopedLock {
public:
  explicit ScopedLock(BaseLock* lock) : _l(lock) { _l->lock(); }
  ~ScopedLock() { _l->unlock(); }

private:
  BaseLock* _l;

  // Non-copyable, non-assignable
  ScopedLock(ScopedLock&);
  ScopedLock& operator=(ScopedLock&);
};

}

#endif

