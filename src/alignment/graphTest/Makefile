CC = g++
OBJ = main.o Graph.o Node.o
HEADER1 = ../Graph.h
HEADER2 = ../Node.h 
CFLAGS = -c -Wall -I../

main: $(OBJ) 
	$(CC) $(OBJ) -o $@

main.o: main.cpp $(HEADER1)
	$(CC) $(CFLAGS) $< -o $@

Graph.o: ../Graph.cpp $(HEADER1) $(HEADER2)
	$(CC) $(CFLAGS) $< -o $@

Node.o: ../Node.cpp $(HEADER2)
	$(CC) $(CFLAGS) $< -o $@

clean: 
	rm -rf *o main
