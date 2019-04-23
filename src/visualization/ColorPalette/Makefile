all: Colortest_main

Colortest_main: colortest_main.o ColorMap.o Graph.o
	g++ -Wall colortest_main.o ColorMap.o Graph.o -o Colortest_main -lsfml-graphics -lsfml-window -lsfml-system
colortest_main.o: colortest_main.cc ColorMap.h Graph.h
	g++ -Wall -c -std=c++11 colortest_main.cc
ColorMap.o: ColorMap.cc ColorMap.h Graph.h
	g++ -Wall -c -std=c++11 ColorMap.cc
Graph.o: Graph.cpp Graph.h ColorMap.h
	g++ -Wall -c -std=c++11 Graph.cpp
clean:
	rm -f *.o colortest_main
