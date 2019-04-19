all: main

main: main.o gui.o
	g++ -Wall main.o gui.o -o main -lsfml-graphics -lsfml-window -lsfml-system
main.o: main.cc gui.h
	g++ -Wall -std=c++11 -c main.cc
gui.o: gui.cc gui.h
	g++ -Wall -std=c++11 -c gui.cc
clean:
	rm *.o main
