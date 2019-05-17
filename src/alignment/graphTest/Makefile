CC = g++
OBJ = graphtest.o Graph.o Node.o Edge.o DrawNode.o
HEADER1 = ../Graph.h
HEADER2 = ../Node.h
HEADER3 = ../Edge.h
HEADER4 = ../DrawNode.h
CFLAGS = -c -std=c++11 -Wall -I../
all: graphtest
graphtest: $(OBJ) 
	$(CC) $(OBJ) -o $@

graphtest.o: graphtest.cc $(HEADER1)
	$(CC) $(CFLAGS) $< -o $@

Graph.o: ../Graph.cc $(HEADER1) $(HEADER2) $(HEADER3)
	$(CC) $(CFLAGS) $< -o $@

Node.o: ../Node.cc $(HEADER2)
	$(CC) $(CFLAGS) $< -o $@

Edge.o: ../Edge.cc $(HEADER3)
	$(CC) $(CFLAGS) $< -o $@

DrawNode.o: ../DrawNode.cc $(HEADER4)
	$(CC) $(CFLAGS) $< -o $@

clean: 
	rm -rf *o graphtest
