main: main.o State.o
	g++ -std=c++11 main.o State.o -o main

main.o: main.cc State.h Graph.h
	g++ -std=c++11 -c main.cc

State.o: State.cc State.h
	g++ -std=c++11 -c State.cc 

Graph.o: Graph.cpp Graph.h
    g++ -std=c++11 -c Graph.cpp

clean:
	rm State.o main.o main
