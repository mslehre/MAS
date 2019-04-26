all: simulation_main

simulation_main: simulation_main.o sequence.o
	g++ -std=c++11 -Wall simulation_main.o sequence.o -o simulation_main
simulation_main.o: simulation_main.cc sequence.h
	g++ -std=c++11 -Wall -c simulation_main.cc
sequence.o: sequence.cc sequence.h
	g++ -std=c++11 -Wall -c sequence.cc
clean:
	rm -f simulation_main *.o

