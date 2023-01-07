#ifndef __AARRAY_LOCK_HPP__
#define __AARRAY_LOCK_HPP__

#include <type_traits>
#include <time.h>
#include "Lock.hpp"

using std::aligned_storage;
using std::alignment_of;

namespace lock {

typedef aligned_storage<63, alignment_of<bool>::value>::type Align;

struct ALIGNED {
  ALIGNED() { flag = false; }
  Align padding;
  bool flag;
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
