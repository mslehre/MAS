CC = g++
OBJ = graphtest.o Graph.o Node.o Edge.o
HEADER1 = ../Graph.h
HEADER2 = ../Node.h
HEADER3 = ../Edge.h
CFLAGS = -c -std=c++11 -Wall -I../
all: graphtest
graphtest: $(OBJ) 
	$(CC) $(OBJ) -o $@

graphtest.o: graphtest.cpp $(HEADER1)
	$(CC) $(CFLAGS) $< -o $@

Graph.o: ../Graph.cpp $(HEADER1) $(HEADER2) $(HEADER3)
	$(CC) $(CFLAGS) $< -o $@

Node.o: ../Node.cpp $(HEADER2)
	$(CC) $(CFLAGS) $< -o $@

Edge.o: ../Edge.cpp $(HEADER3)
	$(CC) $(CFLAGS) $< -o $@

clean: 
	rm -rf *o graphtest
