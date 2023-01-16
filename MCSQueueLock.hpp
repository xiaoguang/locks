#ifndef __MCS_QUEUE_LOCK_HPP__
#define __MCS_QUEUE_LOCK_HPP__

#include "Lock.hpp"
#include "MutexLock.hpp"

namespace lock {

struct MCSQNode {
  MCSQNode() {
    _locked = true;
    _next = nullptr;
  }
  Padding_54 _padding;
  bool _locked;
  MCSQNode* _next;
};

class MCSQueueLock : public BaseLock {
 public:
  static __thread MCSQNode* _CURR;

  explicit MCSQueueLock();
  ~MCSQueueLock();

  virtual void lock();
  virtual void unlock();

 private:
  MCSQNode* _tail;
  MCSQueueLock(MCSQueueLock&);
  MCSQueueLock& operator=(MCSQueueLock&);
};

}

#endif
