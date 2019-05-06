all:main
	cd scoreTest; make all
	cd graphTest; make all 

main: main.o State.o Graph.o Node.o Edge.o
	g++ -std=c++11 main.o State.o Graph.o Node.o Edge.o -o main

main.o: main.cc State.h Graph.h Node.h Edge.h
	g++ -std=c++11 -c main.cc

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
	rm -rf *.o main
