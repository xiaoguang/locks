#ifndef __VIRTUAL_QUEUE_LOCK_HPP__
#define __VIRTUAL_QUEUE_LOCK_HPP__

#include "Lock.hpp"

namespace lock {

struct VQNode {
  VQNode() { _locked = true; }
  Padding_63 _padding;
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
