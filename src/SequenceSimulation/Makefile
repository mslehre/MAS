all: simulation_main

simulation_main: simulation_main.o sequence.o generator.o
	g++ -std=c++11 -Wall simulation_main.o sequence.o generator.o -o simulation_main

simulation_main.o: simulation_main.cc sequence.h generator.h
	g++ -std=c++11 -Wall -c simulation_main.cc

sequence.o: sequence.cc sequence.h
	g++ -std=c++11 -Wall -c sequence.cc

generator.o: generator.cc generator.h
	g++ -std=c++11 -Wall -c generator.cc

clean:
	rm -f simulation_main *.o
