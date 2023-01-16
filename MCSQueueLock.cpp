#include "MCSQueueLock.hpp"

namespace lock {

__thread MCSQNode* _ME;

MCSQueueLock::MCSQueueLock() { _tail = nullptr; }
MCSQueueLock::~MCSQueueLock() {}

void MCSQueueLock::lock() {
  if(_ME == nullptr) _ME = new MCSQNode();
  MCSQNode* pred = __atomic_exchange_n(&_tail, _ME, __ATOMIC_RELAXED);

  if(pred != nullptr) {
    pred->_next = _ME;
    while(_ME->_locked) {}
  }
}

void MCSQueueLock::unlock() {
  _ME->_locked = true;
  if(_ME->_next == nullptr) {
    if(__sync_bool_compare_and_swap(&_tail, _ME, nullptr)) {
      return;
    }
    while(_ME->_next == nullptr);
  }
  _ME->_next->_locked = false;
  _ME->_next = nullptr;
}

}
