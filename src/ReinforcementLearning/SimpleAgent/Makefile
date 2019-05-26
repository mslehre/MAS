include ../../common.mk
CC = g++ -std=c++11
OBJ = RandomAgent_main.o State.o Graph.o Node.o Edge.o
H1 = ../../alignment/Graph.h
H2 = ../../alignment/Edge.h
H3 = ../../alignment/Node.h
H4 = ../../alignment/State.h

all: RandomAgent_main

RandomAgent_main: $(OBJ)
	g++ $(CXXFLAGS) $(OBJ) -o RandomAgent_main

RandomAgent_main.o: RandomAgent_main.cc Agent.h Policy.h RandomPolicy.h $(H1) $(H2) $(H3) $(H4)

State.o: ../../alignment/State.cc $(H4) $(H2) $(H3)
	g++ $(CXXFLAGS) -c -Wall ../../alignment/State.cc 

Graph.o: ../../alignment/Graph.cc $(H1) $(H2) $(H3) $(H4)
	g++ $(CXXFLAGS) -c -Wall ../../alignment/Graph.cc

Edge.o: ../../alignment/Edge.cc $(H2) $(H3)
	g++ $(CXXFLAGS) -c -Wall ../../alignment/Edge.cc

Node.o: ../../alignment/Node.cc $(H3)
	g++ $(CXXFLAGS) -c -Wall ../../alignment/Node.cc

clean:
	rm -f *.o RandomAgent_main

