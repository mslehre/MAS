include ../common.mk

all: State_test

State_test: State_test.o State.o Graph.o Node.o Edge.o
	g++ $(CXXFLAGS) State_test.o State.o Graph.o Node.o Edge.o -o State_test

State_test.o: State_test.cc State.h Graph.h Node.h Edge.h
	g++ $(CXXFLAGS) -c State_test.cc

State.o: State.cc State.h Edge.h Node.h Graph.h
	g++ $(CXXFLAGS) -c State.cc 

Graph.o: Graph.cc Graph.h Edge.h Node.h
	g++ $(CXXFLAGS) -c Graph.cc

Edge.o: Edge.cc Edge.h Node.h
	g++ $(CXXFLAGS) -c Edge.cc

Node.o: Node.cc Node.h
	g++ $(CXXFLAGS) -c Node.cc

clean:
	rm -f *.o State_test
