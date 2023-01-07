all:
	g++ -pthread Thread.hpp Thread.cpp Lock.hpp SpinLock.hpp TTASSpinLock.hpp TicketLock.hpp TicketLock.cpp MutexLock.hpp AArrayLock.hpp AArrayLock.cpp ArrayLock.hpp ArrayLock.cpp LockBenchmark.cpp runner.cpp -o TESTS
clean:
	rm -f TESTS
