#include <cassert>
#include "MCSLock.hpp"

namespace lock {

__thread uint64_t MCSLock::_ME;

MCSLock::MCSLock(uint64_t size) {
  _size   = size;
  _ticket = 0;
  _turn   = 0;
  // _flags = new ALIGNED[_size];
  // _flags[_ticket].flag = true;
}

MCSLock::~MCSLock() {
  // delete[] _flags;
}

void MCSLock::lock() { 
  uint64_t slot = __sync_fetch_and_add(&_ticket, 1);
  _ME = slot % _size;
  // while(!_flags[_ME].flag) {}
  // cout << _ME << " lock " << endl;
  while(_ME != _turn) {}
}

void MCSLock::unlock() {
  // cout << _ME << " unlock " << endl;
  // bool a = __sync_bool_compare_and_swap(&_flags[slot], true, false);
  // bool b = __sync_bool_compare_and_swap(&_flags[(slot + 1) % _size], false, true);
  // assert(a && b);

  // uint64_t slot = _ME;
  // _flags[slot].flag = false;
  // _flags[(slot + 1) % _size].flag = true;
  uint64_t slot = (_ME + 1) % _size;
  bool ret = __sync_bool_compare_and_swap(&_turn, _ME, slot);
  assert(ret);
}

}
