include ../common.mk

all: State_test

State_test: State_test.o State.o Graph.o Node.o Edge.o
	g++ $(CXXFLAGS) State_test.o State.o Graph.o Node.o Edge.o -o State_test

State_test.o: State_test.cc State.h Graph.h Node.h Edge.h
	g++ $(CXXFLAGS) -c State_test.cc

State.o: State.cc State.h Edge.h Node.h Graph.h
	g++ $(CXXFLAGS) -c State.cc 

Graph.o: Graph.cpp Graph.h Edge.h Node.h
	g++ $(CXXFLAGS) -c Graph.cpp

Edge.o: Edge.cpp Edge.h Node.h
	g++ $(CXXFLAGS) -c Edge.cpp

Node.o: Node.cpp Node.h
	g++ $(CXXFLAGS) -c Node.cpp

clean:
	rm -rf *.o State_test
