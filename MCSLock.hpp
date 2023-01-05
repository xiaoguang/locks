#ifndef __MCS_LOCK_HPP__
#define __MCS_LOCK_HPP__

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

class MCSLock : public Lock {

 public:
  static __thread uint64_t _ME;

  MCSLock(uint64_t size);
  ~MCSLock();

  virtual void lock();

  virtual void unlock();

 private:
  uint64_t _size;
  uint64_t _ticket;
  uint64_t _turn;
  // ALIGNED * _flags;
  MCSLock();
  MCSLock(MCSLock &);
  MCSLock & operator=(MCSLock &);
};

}

#endif
