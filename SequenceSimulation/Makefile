all: main

main: main.o sequence.o
	g++ -std=c++11 main.o sequence.o -o main
main.o: main.cc sequence.h
	g++ -std=c++11 -c main.cc
sequence.o: sequence.cc sequence.h
	g++ -std=c++11 -c sequence.cc
clean:
	rm main *.o

