main: main.o kmercolor.o Graph.o
	g++ main.o kmercolor.o Graph.o -o main -lsfml-graphics -lsfml-window -lsfml-system
main.o: main.cc kmercolor.h Graph.h
	g++ -c -std=c++11 main.cc
kmercolor.o: kmercolor.cc kmercolor.h Graph.h
	g++ -c -std=c++11 kmercolor.cc
Graph.o: Graph.cpp Graph.h kmercolor.h
	g++ -c -std=c++11 Graph.cpp
clean:
	rm *.o main
