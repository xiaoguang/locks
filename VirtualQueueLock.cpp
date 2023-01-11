#include "VirtualQueueLock.hpp"

namespace lock {

__thread VQNode* VirtualQueueLock::_PRED;
__thread VQNode* VirtualQueueLock::_CURR;

// __thread int lockCount = 0;
// __thread int unlockCount = 0;

VirtualQueueLock::VirtualQueueLock() {
  _tail = new VQNode();
  _tail->_locked = false;
  // _l = new MutexLock();
}

VirtualQueueLock::~VirtualQueueLock() {
  delete _tail;
  // delete _l;
}

void VirtualQueueLock::lock() {
  // if(!_CURR) _CURR = new VQNode(pthread_self());
  if(!_CURR) _CURR = new VQNode();

  // lockCount++;
  VQNode* pred = __atomic_exchange_n(&_tail, _CURR, __ATOMIC_SEQ_CST);
  // _l->lock();
  // cout << pthread_self() << " spinning on " << pred->_owner << " locked " << pred->_locked << " round " << lockCount << endl;
  // _l->unlock();
  _PRED = pred;
  while(pred->_locked) {}
  // _l->lock();
  // cout << pthread_self() << " entered "  << pred->_owner << " locked " << pred->_locked << " round " << lockCount << endl;
  // _l->unlock();
}

void VirtualQueueLock::unlock() {
  // unlockCount++;
  _CURR->_locked = false;
  _PRED->_locked = true;
  // VQNode* tmp = _CURR;
  // _PRED = tmp;
  // _l->lock();
  // if(_CURR->_owner == _PRED->_owner)
  //   cout << pthread_self() << " out on same owner " << unlockCount << endl;
  // else
  //   cout << pthread_self() << " out " << unlockCount << endl;
  // _l->unlock();
  _CURR = _PRED;
}

}
