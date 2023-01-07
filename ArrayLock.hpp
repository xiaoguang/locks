#ifndef __ARRAY_LOCK_HPP__
#define __ARRAY_LOCK_HPP__

#include <type_traits>
#include <time.h>
#include "Lock.hpp"

namespace lock {

class ArrayLock : public BaseLock {
 public:
  static __thread uint64_t _ME;

  explicit ArrayLock(uint64_t size);
  ~ArrayLock();

  virtual void lock();
  virtual void unlock();

 private:
  uint64_t _size;
  uint64_t _ticket;
  bool* _flags;

  ArrayLock();
  ArrayLock(ArrayLock&);
  ArrayLock& operator=(ArrayLock&);
};

}

#endif
