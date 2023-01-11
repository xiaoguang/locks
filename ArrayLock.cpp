#include "ArrayLock.hpp"

namespace lock {

__thread uint64_t ArrayLock::_ME;

ArrayLock::ArrayLock(uint64_t size) {
  _size   = size;
  _ticket = 0;
  _flags  = new bool[_size];
  for(int i = 0; i < _size; i++) {
    if(i == 0) _flags[i] = true;
    else _flags[i] = false;
  }
}

ArrayLock::~ArrayLock() {
  delete[] _flags;
}

void ArrayLock::lock() { 
  uint64_t slot = __atomic_fetch_add(&_ticket, 1, __ATOMIC_RELAXED);
  _ME = slot % _size;
  while(!_flags[_ME]) {}
}

void ArrayLock::unlock() {
  uint64_t slot = (_ME + 1) % _size;
  _flags[_ME] = false;
  _flags[slot] = true;
}

}
