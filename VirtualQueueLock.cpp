#include "VirtualQueueLock.hpp"

namespace lock {

__thread VQNode* VirtualQueueLock::_PRED;
__thread VQNode* VirtualQueueLock::_CURR;

VirtualQueueLock::VirtualQueueLock() {
  _tail = new VQNode();
  _tail->_locked = false;
}

VirtualQueueLock::~VirtualQueueLock() {
  delete _tail;
}

void VirtualQueueLock::lock() {
  if(!_CURR) _CURR = new VQNode();
  VQNode* pred = __atomic_exchange_n(&_tail, _CURR, __ATOMIC_SEQ_CST);
  _PRED = pred;
  while(pred->_locked) {}
}

void VirtualQueueLock::unlock() {
  _CURR->_locked = false;
  _PRED->_locked = true;
  _CURR = _PRED;
}

}
