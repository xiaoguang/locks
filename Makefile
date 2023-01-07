all:
	g++ -pthread Thread.hpp Thread.cpp Lock.hpp SpinLock.hpp TTASSpinLock.hpp TicketLock.hpp TicketLock.cpp MutexLock.hpp MCSLock.hpp MCSLock.cpp ArrayLock.hpp ArrayLock.cpp LockBenchmark.cpp runner.cpp -o TESTS
clean:
	rm -f TESTS
