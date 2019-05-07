include ../common.mk

all: main

main: main.o State.o Graph.o Node.o Edge.o
	g++ $(CXXFLAGS) main.o State.o Graph.o Node.o Edge.o -o main

main.o: main.cc State.h Graph.h Node.h Edge.h
	g++ $(CXXFLAGS) -c main.cc

State.o: State.cc State.h Edge.h Node.h
	g++ $(CXXFLAGS) -c State.cc 

Graph.o: Graph.cpp Graph.h Edge.h Node.h
	g++ $(CXXFLAGS) -c Graph.cpp

Edge.o: Edge.cpp Edge.h Node.h
	g++ $(CXXFLAGS) -c Edge.cpp

Node.o: Node.cpp Node.h
	g++ $(CXXFLAGS) -c Node.cpp

clean:
	rm -f *.o main
