#include "AArrayLock.hpp"

namespace lock {

__thread uint64_t AArrayLock::_ME;

AArrayLock::AArrayLock(uint64_t size) {
  _size   = size;
  _ticket = 0;
  _flags = new ALIGNED[_size];
  for(int i = 0; i < _size; i++) {
    if(i == 0) _flags[i]._flag = true;
    else _flags[i]._flag = false;
  }
}

AArrayLock::~AArrayLock() {
  delete[] _flags;
}

void AArrayLock::lock() {
  uint64_t slot = __atomic_fetch_add(&_ticket, 1, __ATOMIC_ACQUIRE);
  _ME = slot % _size;
  while(!_flags[_ME]._flag) {}
}

void AArrayLock::unlock() {
  uint64_t slot = (_ME + 1) % _size;
  // intel has strong coherent protocal
  // _flags[_ME]._flag = false;
  // _flags[slot]._flag = true;
  __atomic_store_n(&_flags[_ME], false, __ATOMIC_RELEASE);
  __atomic_store_n(&_flags[slot], true, __ATOMIC_RELEASE);
}

}
