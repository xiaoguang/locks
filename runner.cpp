#include <cassert>
#include <time.h>
#include "LockBenchmark.cpp"
#include "Thread.hpp"

using lock::LockBenchmark;
using lock::makeThread;
using std::tr1::bind;

#define NUM_THREADS 1 << 5

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


void TEST1() {
  // MutexLock l;
  // SpinLock l;
  // TTASSpinLock l;
  // MCSLock l(NUM_THREADS);
  TicketLock l;
  LockBenchmark lb(&l);
  pthread_t threads[NUM_THREADS];

  struct timespec start, stop, diff;
  clock_gettime(CLOCK_REALTIME, &start);

  for(int i = 0; i < NUM_THREADS; i++)
    threads[i] = makeThread(bind(&LockBenchmark::correctness, &lb, 1 << 15));
  for(int i = 0; i < NUM_THREADS; i++)
    pthread_join(threads[i], NULL);

  clock_gettime(CLOCK_REALTIME, &stop);

  timeDiff(start, stop, diff);
  cout << NUM_THREADS << endl;
  cout << lb.count() << endl;
  cout << diff.tv_sec << " : " << diff.tv_nsec << endl;
}

int main() {
  TEST1();
}
