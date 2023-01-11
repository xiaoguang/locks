#include <cassert>
#include <time.h>
#include "LockBenchmark.cpp"
#include "Thread.hpp"

using lock::LockBenchmark;
using lock::makeThread;
using std::tr1::bind;

#define NUM_THREADS 6
#define NUM_SLOTS 6
#define NUM_RUNS 1 << 2
#define NUM_REENTRIES 1 << 18

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
    for(int i = 0; i < NUM_THREADS; i++)
      threads[i] = makeThread(bind(&LockBenchmark::correctness, &lb, NUM_REENTRIES));
    for(int i = 0; i < NUM_THREADS; i++)
      pthread_join(threads[i], NULL);
    clock_gettime(CLOCK_REALTIME, &stop);

    timeDiff(start, stop, diff);
    cout << lb.count() << endl;
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
    for(int i = 0; i < NUM_THREADS; i++)
      threads[i] = makeThread(bind(&LockBenchmark::correctness, &lb, NUM_REENTRIES));
    for(int i = 0; i < NUM_THREADS; i++)
      pthread_join(threads[i], NULL);
    clock_gettime(CLOCK_REALTIME, &stop);

    timeDiff(start, stop, diff);
    cout << lb.count() << endl;
    cout << diff.tv_sec << " : " << diff.tv_nsec << endl;
  }
  cout << endl;
}

void TEST2() {
  for(int k = 0; k < NUM_RUNS; k++) {
    ArrayLock l(NUM_SLOTS);
    LockBenchmark lb(&l);
    pthread_t threads[NUM_THREADS];
    struct timespec start, stop, diff;

    clock_gettime(CLOCK_REALTIME, &start);
    for(int i = 0; i < NUM_THREADS; i++)
      threads[i] = makeThread(bind(&LockBenchmark::correctness, &lb, NUM_REENTRIES));
    for(int i = 0; i < NUM_THREADS; i++)
      pthread_join(threads[i], NULL);
    clock_gettime(CLOCK_REALTIME, &stop);

    timeDiff(start, stop, diff);
    cout << lb.count() << endl;
    cout << diff.tv_sec << " : " << diff.tv_nsec << endl;
  }
  cout << endl;
}

void TEST3() {
  for(int k = 0; k < NUM_RUNS; k++) {
    AArrayLock l(NUM_SLOTS);
    LockBenchmark lb(&l);
    pthread_t threads[NUM_THREADS];
    struct timespec start, stop, diff;

    clock_gettime(CLOCK_REALTIME, &start);
    for(int i = 0; i < NUM_THREADS; i++)
      threads[i] = makeThread(bind(&LockBenchmark::correctness, &lb, NUM_REENTRIES));
    for(int i = 0; i < NUM_THREADS; i++)
      pthread_join(threads[i], NULL);
    clock_gettime(CLOCK_REALTIME, &stop);

    timeDiff(start, stop, diff);
    cout << lb.count() << endl;
    cout << diff.tv_sec << " : " << diff.tv_nsec << endl;
  }
  cout << endl;
}

void TEST4() {
  for(int k = 0; k < NUM_RUNS; k++) {
    VirtualQueueLock l;
    LockBenchmark lb(&l);
    pthread_t threads[NUM_THREADS];
    struct timespec start, stop, diff;

    clock_gettime(CLOCK_REALTIME, &start);
    for(int i = 0; i < NUM_THREADS; i++)
      threads[i] = makeThread(bind(&LockBenchmark::correctness, &lb, NUM_REENTRIES));
    for(int i = 0; i < NUM_THREADS; i++)
      pthread_join(threads[i], NULL);
    clock_gettime(CLOCK_REALTIME, &stop);

    timeDiff(start, stop, diff);
    cout << lb.count() << endl;
    cout << diff.tv_sec << " : " << diff.tv_nsec << endl;
  }
  cout << endl;
}

int main() {
  TEST0();
  TEST1();
  TEST2();
  TEST3();
  TEST4();
}
