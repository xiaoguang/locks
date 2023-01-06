#ifndef __LOCK_HPP__
#define __LOCK_HPP__

#include <iostream>
#include <cstdlib>

using std::cout;
using std::endl;

namespace lock {

class BaseLock {
 // interface pure virtual functions
 public:
  virtual void lock() = 0;
  virtual void unlock() = 0;
};

}

#endif
