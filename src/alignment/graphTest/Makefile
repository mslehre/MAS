main: main.o Graph.o
	g++ main.o Graph.o -o main
main.o: main.cpp Graph.h
	g++ -c main.cpp
Graph.o: Graph.cpp Graph.h
	g++ -c Graph.cpp
clean:
	rm *.o main
