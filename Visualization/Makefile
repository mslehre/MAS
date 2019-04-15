main: main.o Graph.o
	g++ main.o Graph.o -o main -lsfml-graphics -lsfml-window -lsfml-system
main.o: main.cpp Graph.h
	g++ -c -std=c++11 main.cpp
Graph.o: Graph.cpp Graph.h
	g++ -c -std=c++11 Graph.cpp
clean:
	rm *.o main
