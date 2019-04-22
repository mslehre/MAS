
all: main

Program: main.o ColorMap.o Graph.o
	g++ main.o ColorMap.o Graph.o -o Program -lsfml-graphics -lsfml-window -lsfml-system
main.o: main.cc ColorMap.h Graph.h
	g++ -c -std=c++11 main.cc
ColorMap.o: ColorMap.cc ColorMap.h Graph.h
	g++ -c -std=c++11 ColorMap.cc
Graph.o: Graph.cpp Graph.h ColorMap.h
	g++ -c -std=c++11 Graph.cpp
clean:
	rm -f *.o main
