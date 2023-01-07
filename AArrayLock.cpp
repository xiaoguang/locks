#include "AArrayLock.hpp"

namespace lock {

__thread uint64_t AArrayLock::_ME;

AArrayLock::AArrayLock(uint64_t size) {
  _size   = size;
  _ticket = 0;
  _flags = new ALIGNED[_size];
  for(int i = 0; i < _size; i++) {
    if(i == 0) _flags[i].flag = true;
    else _flags[i].flag = false;
  }
}

AArrayLock::~AArrayLock() {
  delete[] _flags;
}

void AArrayLock::lock() { 
  uint64_t slot = __sync_fetch_and_add(&_ticket, 1);
  _ME = slot % _size;
  while(!_flags[_ME].flag) {}
}

void AArrayLock::unlock() {
  uint64_t slot = (_ME + 1) % _size;
  __sync_bool_compare_and_swap(&_flags[_ME].flag, true, false);
  __sync_bool_compare_and_swap(&_flags[slot].flag, false, true);
}

}
