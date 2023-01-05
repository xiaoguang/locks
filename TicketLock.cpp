#include <cassert>
#include "TicketLock.hpp"

namespace lock {

__thread uint64_t TicketLock::_ME;

TicketLock::TicketLock() {
  _granted = 0;
  _ticket  = 0;
  _turn    = 0;
  _locked  = false;
}

TicketLock::~TicketLock() {}

void TicketLock::lock() { 
  _ME = __sync_fetch_and_add(&_ticket, 1);
  struct timespec timeWait;
  timeWait.tv_sec  = 0;
  struct sched_param param;
  param.sched_priority = 1;
  pthread_setschedparam(pthread_self(), SCHED_FIFO, &param);

  while(1) {
    if(_ME != _turn && _locked) {
      int wait = (_ticket - _granted) * NANO_SLEEP;
      timeWait.tv_nsec = (wait > 0) ? wait : 0;
      if(timeWait.tv_nsec == 0);
      else nanosleep(&timeWait, NULL);
    }
    if(_locked)
      continue;
    if(!__sync_bool_compare_and_swap(&_locked, false, true))
      continue;
    __sync_bool_compare_and_swap(&_turn, _turn, _ME);
    param.sched_priority = 99;
    pthread_setschedparam(pthread_self(), SCHED_FIFO, &param);
    break;
  }
}

void TicketLock::unlock() {
  __sync_bool_compare_and_swap(&_turn, _ME, (_ME + 1));
  __sync_fetch_and_add(&_granted, 1);
  __sync_bool_compare_and_swap(&_locked, true, false);
  struct sched_param param;
  param.sched_priority = 1;
  pthread_setschedparam(pthread_self(), SCHED_FIFO, &param);
}

}
