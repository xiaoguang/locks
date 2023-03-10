all:
	g++ -std=c++11 -latomic -pthread TicksClock.hpp TicksClock.cpp Config.hpp Stats.hpp Thread.hpp Thread.cpp Lock.hpp SpinLock.hpp TTASSpinLock.hpp TicketLock.hpp TicketLock.cpp MutexLock.hpp AArrayLock.hpp AArrayLock.cpp ArrayLock.hpp ArrayLock.cpp LockBenchmark.cpp VirtualQueueLock.hpp VirtualQueueLock.cpp MCSQueueLock.hpp MCSQueueLock.cpp runner.cpp -o TESTS
clean:
	rm -f TESTS
