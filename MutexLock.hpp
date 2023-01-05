#ifndef __MUTEX_LOCK__
#define __MUTEX_LOCK__

#include <pthread.h>
#include "Lock.hpp"

namespace lock {

class MutexLock : public Lock {
 public:
  MutexLock() { pthread_mutex_init(&_m, NULL); }
  ~MutexLock() { pthread_mutex_destroy(&_m); }
  virtual void lock() { pthread_mutex_lock(&_m); }
  virtual void unlock() { pthread_mutex_unlock(&_m); }

 private:
  pthread_mutex_t _m;

  MutexLock(MutexLock &);
  MutexLock & operator=(MutexLock &);
};

}

#endif
