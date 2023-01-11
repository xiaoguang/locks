#ifndef __VIRTUAL_QUEUE_LOCK_HPP__
#define __VIRTUAL_QUEUE_LOCK_HPP__

#include <type_traits>
#include <time.h>
#include "Lock.hpp"

using std::aligned_storage;
using std::alignment_of;

namespace lock {

typedef aligned_storage<63, alignment_of<bool>::value>::type Align;

struct VQNode {
  VQNode() { _locked = true; }
  Align _padding;
  bool _locked;
};

class VirtualQueueLock : public BaseLock {
 public:
  static __thread VQNode* _PRED;
  static __thread VQNode* _CURR;

  explicit VirtualQueueLock();
  ~VirtualQueueLock();

  virtual void lock();
  virtual void unlock();

 private:
  VQNode* _tail;
  VirtualQueueLock(VirtualQueueLock&);
  VirtualQueueLock& operator=(VirtualQueueLock&);
};

}

#endif
