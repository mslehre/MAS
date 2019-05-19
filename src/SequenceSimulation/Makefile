include ../common.mk

all: simulation_main

simulation_main: simulation_main.o sequence.o generator.o
	g++ $(CXXFLAGS) simulation_main.o sequence.o generator.o -o simulation_main

simulation_main.o: simulation_main.cc sequence.h generator.h
	g++ $(CXXFLAGS) -c simulation_main.cc

sequence.o: sequence.cc sequence.h
	g++ $(CXXFLAGS) -c sequence.cc

generator.o: generator.cc generator.h
	g++ $(CXXFLAGS) -c generator.cc

clean:
	rm -f simulation_main *.o
