CC = g++ -std=c++11
OBJ = RandomAgent_main.o State.o Graph.o Node.o Edge.o
H1 = ../../alignment/Graph.h
H2 = ../../alignment/Edge.h
H3 = ../../alignment/Node.h
H4 = ../../alignment/State.h

all: RandomAgent_main

RandomAgent_main: $(OBJ)
	$(CC) $(OBJ) -o RandomAgent_main

RandomAgent_main.o: RandomAgent_main.cc RandomAgent.h BaseAgent.h $(H1) $(H2) $(H3) $(H4)
	$(CC) -c RandomAgent_main.cc

State.o: ../../alignment/State.cc $(H4) $(H2) $(H3)
	$(CC) -c -Wall ../../alignment/State.cc 

Graph.o: ../../alignment/Graph.cpp $(H1) $(H2) $(H3) $(H4)
	$(CC) -c -Wall ../../alignment/Graph.cpp

Edge.o: ../../alignment/Edge.cpp $(H2) $(H3)
	$(CC) -c -Wall ../../alignment/Edge.cpp

Node.o: ../../alignment/Node.cpp $(H3)
	$(CC) -c -Wall ../../alignment/Node.cpp

clean:
	rm -f *.o RandomAgent_main
