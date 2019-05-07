all: State_test
	cd scoreTest; make all
	cd graphTest; make all 

State_test: State_test.o State.o Graph.o Node.o Edge.o
	g++ -std=c++11 State_test.o State.o Graph.o Node.o Edge.o -o State_test

State_test.o: State_test.cc State.h Graph.h Node.h Edge.h
	g++ -std=c++11 -c State_test.cc

State.o: State.cc State.h Edge.h Node.h Graph.h
	g++ -std=c++11 -c State.cc 

Graph.o: Graph.cpp Graph.h Edge.h Node.h
	g++ -std=c++11 -c Graph.cpp

Edge.o: Edge.cpp Edge.h Node.h
	g++ -std=c++11 -c Edge.cpp

Node.o: Node.cpp Node.h
	g++ -std=c++11 -c Node.cpp

clean:
	cd scoreTest; make clean
	cd graphTest; make clean
	rm -rf *.o State_test
