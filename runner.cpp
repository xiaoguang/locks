#include <cassert>
#include <time.h>
#include "LockBenchmark.cpp"
#include "Thread.hpp"
#include <queue>
#include <string>

using lock::LockBenchmark;
using lock::makeThread;
using std::tr1::bind;
using std::queue;
using std::string;

struct TestDetails {
  string _lockName;
  lock::BaseLock* _lock;
  int _numberOfThreads;
  pthread_t* _threads;
};

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

void TEST0() {
  for(int k = 0; k < NUM_RUNS; k++) {
    TicketLock l;
    LockBenchmark lb(&l);
    pthread_t threads[NUM_THREADS];
    struct timespec start, stop, diff;
    clock_gettime(CLOCK_REALTIME, &start);
    TicksClock::Ticks before = TicksClock::getTicks();

    for(int i = 0; i < NUM_THREADS; i++)
      threads[i] = makeThread(bind(&LockBenchmark::correctness, &lb, NUM_REENTRIES));
    for(int i = 0; i < NUM_THREADS; i++)
      pthread_join(threads[i], NULL);
    clock_gettime(CLOCK_REALTIME, &stop);

    TicksClock::Ticks duration = TicksClock::getTicks() - before;
    timeDiff(start, stop, diff);
    cout << "Correctness  : " << lb.count() << endl;
    cout << "total  costs : " << duration << endl;
    cout << "work   costs : " << lb.workTicks() << endl;
    cout << "lock   costs : " << lb.lockTicks() << endl;
    cout << "unlock costs : " << lb.unlockTicks() << endl;
    cout << diff.tv_sec << " : " << diff.tv_nsec << endl;
  }
  cout << endl;
}

void TEST1() {
  for(int k = 0; k < NUM_RUNS; k++) {
    MutexLock l;
    LockBenchmark lb(&l);
    pthread_t threads[NUM_THREADS];
    struct timespec start, stop, diff;
    clock_gettime(CLOCK_REALTIME, &start);
    TicksClock::Ticks before = TicksClock::getTicks();

    for(int i = 0; i < NUM_THREADS; i++)
      threads[i] = makeThread(bind(&LockBenchmark::correctness, &lb, NUM_REENTRIES));
    for(int i = 0; i < NUM_THREADS; i++)
      pthread_join(threads[i], NULL);
    clock_gettime(CLOCK_REALTIME, &stop);

    TicksClock::Ticks duration = TicksClock::getTicks() - before;
    timeDiff(start, stop, diff);
    cout << "Correctness  : " << lb.count() << endl;
    cout << "total  costs : " << duration << endl;
    cout << "work   costs : " << lb.workTicks() << endl;
    cout << "lock   costs : " << lb.lockTicks() << endl;
    cout << "unlock costs : " << lb.unlockTicks() << endl;
    cout << diff.tv_sec << " : " << diff.tv_nsec << endl;
  }
  cout << endl;
}

void TEST2() {
  for(int k = 0; k < NUM_RUNS; k++) {
    ArrayLock l(NUM_SLOTS);
    LockBenchmark lb(&l);
    pthread_t threads[NUM_THREADS];
    TicksClock::Ticks before = TicksClock::getTicks();

    for(int i = 0; i < NUM_THREADS; i++)
      threads[i] = makeThread(bind(&LockBenchmark::correctness, &lb, NUM_REENTRIES));
    for(int i = 0; i < NUM_THREADS; i++)
      pthread_join(threads[i], NULL);

    TicksClock::Ticks duration = TicksClock::getTicks() - before;
    cout << "Correctness  : " << lb.count() << endl;
    cout << "total  costs : " << duration << endl;
    cout << "work   costs : " << lb.workTicks() << endl;
    cout << "lock   costs : " << lb.lockTicks() << endl;
    cout << "unlock costs : " << lb.unlockTicks() << endl;
  }
  cout << endl;
}

void TEST3() {
  for(int k = 0; k < NUM_RUNS; k++) {
    AArrayLock l(NUM_SLOTS);
    LockBenchmark lb(&l);
    pthread_t threads[NUM_THREADS];
    TicksClock::Ticks before = TicksClock::getTicks();

    for(int i = 0; i < NUM_THREADS; i++)
      threads[i] = makeThread(bind(&LockBenchmark::correctness, &lb, NUM_REENTRIES));
    for(int i = 0; i < NUM_THREADS; i++)
      pthread_join(threads[i], NULL);

    TicksClock::Ticks duration = TicksClock::getTicks() - before;
    cout << "Correctness  : " << lb.count() << endl;
    cout << "total  costs : " << duration << endl;
    cout << "work   costs : " << lb.workTicks() << endl;
    cout << "lock   costs : " << lb.lockTicks() << endl;
    cout << "unlock costs : " << lb.unlockTicks() << endl;
  }
  cout << endl;
}

void TEST4() {
  for(int k = 0; k < NUM_RUNS; k++) {
    VirtualQueueLock l;
    LockBenchmark lb(&l);
    pthread_t threads[NUM_THREADS];
    TicksClock::Ticks before = TicksClock::getTicks();

    for(int i = 0; i < NUM_THREADS; i++)
      threads[i] = makeThread(bind(&LockBenchmark::correctness, &lb, NUM_REENTRIES));
    for(int i = 0; i < NUM_THREADS; i++)
      pthread_join(threads[i], NULL);

    TicksClock::Ticks duration = TicksClock::getTicks() - before;
    cout << "Correctness  : " << lb.count() << endl;
    cout << "total  costs : " << duration << endl;
    cout << "work   costs : " << lb.workTicks() << endl;
    cout << "lock   costs : " << lb.lockTicks() << endl;
    cout << "unlock costs : " << lb.unlockTicks() << endl;
  }
  cout << endl;
}

void TEST5() {
  for(int k = 0; k < NUM_RUNS; k++) {
    MCSQueueLock l;
    LockBenchmark lb(&l);
    pthread_t threads[NUM_THREADS];
    TicksClock::Ticks before = TicksClock::getTicks();

    for(int i = 0; i < NUM_THREADS; i++)
      threads[i] = makeThread(bind(&LockBenchmark::correctness, &lb, NUM_REENTRIES));
    for(int i = 0; i < NUM_THREADS; i++)
      pthread_join(threads[i], NULL);

    TicksClock::Ticks duration = TicksClock::getTicks() - before;
    cout << "Correctness  : " << lb.count() << endl;
    cout << "total  costs : " << duration << endl;
    cout << "work   costs : " << lb.workTicks() << endl;
    cout << "lock   costs : " << lb.lockTicks() << endl;
    cout << "unlock costs : " << lb.unlockTicks() << endl;
  }
  cout << endl;
}

int main() {
  TEST0();
  TEST1();
  TEST2();
  TEST3();
  TEST4();
  TEST5();
}
