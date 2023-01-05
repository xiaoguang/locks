#ifndef __TICKET_LOCK_HPP__
#define __TICKET_LOCK_HPP__

#include <type_traits>
#include <time.h>
#include "Lock.hpp"

#define NANO_SLEEP 10

namespace lock {

class TicketLock : public Lock {

 public:
  static __thread uint64_t _ME;

  TicketLock();
  ~TicketLock();

  virtual void lock();

  virtual void unlock();

 private:
  uint64_t _granted;
  uint64_t _ticket;
  uint64_t _turn;
  bool _locked;
  TicketLock(TicketLock &);
  TicketLock & operator=(TicketLock &);

};

}

#endif
