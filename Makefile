all:
	g++ -pthread Thread.hpp Thread.cpp Lock.hpp TicketLock.hpp TicketLock.cpp runner.cpp -o TESTS
clean:
	rm -f TESTS
