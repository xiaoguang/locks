#include <cassert>
#include "MCSLock.hpp"

namespace lock {

__thread uint64_t MCSLock::_ME;

MCSLock::MCSLock(uint64_t size) {
  _size   = size;
  _ticket = 0;
  _flags = new ALIGNED[_size];
  _flags[_ticket].flag = true;
  cout << sizeof(ALIGNED) << endl;
}

MCSLock::~MCSLock() {
  delete[] _flags;
}

void MCSLock::lock() { 
  uint64_t slot = __sync_fetch_and_add(&_ticket, 1);
  _ME = slot % _size;
  while(!_flags[_ME].flag) {}
  // cout << _ME << " lock " << endl;
}

void MCSLock::unlock() {
  // cout << _ME << " unlock " << endl;
  uint64_t slot = (_ME + 1) % _size;
  __sync_bool_compare_and_swap(&_flags[_ME].flag, true, false);
  __sync_bool_compare_and_swap(&_flags[slot].flag, false, true);
}

}
