CC = g++
OBJ = ScoreTest.o State.o Node.o Edge.o Graph.o
HEADER1 = ../State.h
HEADER2 = ../Node.h
HEADER3 = ../Edge.h
HEADER4 = ../Graph.h
CFLAGS = -c -std=c++11 -Wall -I../
all: ScoreTest
ScoreTest: $(OBJ) 
	$(CC) $(OBJ) -o $@

ScoreTest.o: ScoreTest.cc $(HEADER1) $(HEADER2) $(HEADER3) $(HEADER4)
	$(CC) $(CFLAGS) $< -o $@

State.o: ../State.cc $(HEADER2) $(HEADER3) $(HEADER4)
	$(CC) $(CFLAGS) $< -o $@

Node.o: ../Node.cc $(HEADER2)
	$(CC) $(CFLAGS) $< -o $@

Edge.o: ../Edge.cc $(HEADER3)
	$(CC) $(CFLAGS) $< -o $@

Graph.o: ../Graph.cc $(HEADER4) 
	$(CC) $(CFLAGS) $< -o $@

clean: 
	rm -rf *o ScoreTest
