#ifndef __AARRAY_LOCK_HPP__
#define __AARRAY_LOCK_HPP__

#include "Lock.hpp"

namespace lock {

struct ALIGNED {
  ALIGNED() { _flag = false; }
  Padding_63 _padding;
  bool _flag;
};

class AArrayLock : public BaseLock {
 public:
  static __thread uint64_t _ME;

  explicit AArrayLock(uint64_t size);
  ~AArrayLock();

  virtual void lock();
  virtual void unlock();

 private:
  uint64_t _size;
  uint64_t _ticket;
  ALIGNED* _flags;

  AArrayLock();
  AArrayLock(AArrayLock&);
  AArrayLock& operator=(AArrayLock &);
};

}

#endif
