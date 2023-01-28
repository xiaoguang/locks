#include <cassert>
#include <time.h>
#include "LockBenchmark.cpp"
#include "Thread.hpp"
#include <queue>
#include <string>
#include <cassert>

using lock::LockBenchmark;
using lock::makeThread;
using std::tr1::bind;
using std::queue;
using std::string;

void timeDiff(
  const struct timespec & start,
  const struct timespec & stop,
  struct timespec & diff
) {
  if(stop.tv_nsec > start.tv_nsec) {
    diff.tv_sec = stop.tv_sec - start.tv_sec;
    diff.tv_nsec = stop.tv_nsec - start.tv_nsec;
  }
  else {
    diff.tv_sec = stop.tv_sec - start.tv_sec - 1;
    diff.tv_nsec = stop.tv_nsec - start.tv_nsec + 1000000000;
  }
}

struct TestDetails {
  TestDetails(string name, lock::BaseLock* lock, bool metrics) {
    _name = name;
    _lock = lock;
    _metrics = metrics;
  }

  ~TestDetails() { delete _lock; }

  string _name;
  lock::BaseLock* _lock;
  bool _metrics;
};

uint64_t expected = (uint64_t)WORK_LOAD * NUM_THREADS * (uint64_t)NUM_REENTRIES;

void TESTS(queue<TestDetails*>& target, bool metrics) {
  {
    SpinLock* l = new SpinLock();
    TestDetails* t = new TestDetails("spin_lock", l, metrics);
    target.push(t);
  }

  {
    TTASSpinLock* l = new TTASSpinLock();
    TestDetails* t = new TestDetails("test_tas_spin_lock", l, metrics);
    target.push(t);
  }

  {
    MutexLock* l = new MutexLock();
    TestDetails* t = new TestDetails("mutex_lock", l, metrics);
    target.push(t);
  }

  {
    TicketLock* l = new TicketLock();
    TestDetails* t = new TestDetails("ticket_lock", l, metrics);
    target.push(t);
  }

  {
    ArrayLock* l = new ArrayLock(NUM_SLOTS);
    TestDetails* t = new TestDetails("array_lock", l, metrics);
    target.push(t);
  }

  {
    AArrayLock* l = new AArrayLock(NUM_SLOTS);
    TestDetails* t = new TestDetails("aligned_array_lock", l, metrics);
    target.push(t);
  }

  {
    VirtualQueueLock* l = new VirtualQueueLock;
    TestDetails* t = new TestDetails("virtual_queue_lock", l, metrics);
    target.push(t);
  }

  {
    MCSQueueLock* l = new MCSQueueLock;
    TestDetails* t = new TestDetails("mcs_queue_lock", l, metrics);
    target.push(t);
  }
}

void runTests(queue<TestDetails*>& target) {
  while (!target.empty()) {
    TestDetails* details = target.front();

    for(int k = 0; k < NUM_RUNS; k++) {
      lock::BaseLock* l = details->_lock;
      LockBenchmark lb(l);
      pthread_t threads[NUM_THREADS];
      struct timespec start, stop, diff;
      clock_gettime(CLOCK_REALTIME, &start);

      for(int i = 0; i < NUM_THREADS; i++) {
        threads[i] = makeThread(
          bind(&LockBenchmark::correctness, &lb, NUM_REENTRIES, WORK_LOAD, details->_metrics)
        );
      }

      for(int i = 0; i < NUM_THREADS; i++)
        pthread_join(threads[i], NULL);

      clock_gettime(CLOCK_REALTIME, &stop);
      timeDiff(start, stop, diff);
      cout << "Lock Name    : " << details->_name << endl;
      cout << "Correctness  : " << lb.count() << endl;
      cout << "Expected     : " << expected << endl;
      assert(lb.count() == expected);

      if(details->_metrics) {
        cout << "total  costs : " << lb.totalTicks() << endl;
        cout << "work   costs : " << lb.workTicks() << endl;
        cout << "lock   costs : " << lb.lockTicks() << endl;
        cout << "unlock costs : " << lb.unlockTicks() << endl;
      }

      cout << "Time Elapse  : " << diff.tv_sec << "." << diff.tv_nsec << endl;
      cout << endl;
    }
    cout << endl;

    delete details;
    target.pop();
  }
}

int main() {
  queue<TestDetails*> correctness;
  queue<TestDetails*> metrics;
  TESTS(correctness, false);
  TESTS(metrics, true);
  runTests(correctness);
  runTests(metrics);
}
