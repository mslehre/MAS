CC = g++
OBJ = main.o Graph.o Node.o GraphRenderer.o Edge.o
HEADER1 = ../../alignment/Graph.h
HEADER2 = ../../alignment/Node.h 
HEADER3 = GraphRenderer.h
HEADER4 = ../../alignment/Edge.h
CFLAGS = -c -std=c++11 -Wall 

all: visualization
visualization: $(OBJ) 
	$(CC) $(OBJ) -o  $@ -lsfml-graphics -lsfml-window -lsfml-system

main.o: main.cpp $(HEADER1)
	$(CC) $(CFLAGS) $< -o  $@

GraphRenderer.o: GraphRenderer.cpp $(HEADER3) $(HEADER1)
	$(CC) $(CFLAGS) $< -o $@

Graph.o: ../../alignment/Graph.cpp $(HEADER1) $(HEADER2) $(HEADER4)
	$(CC) $(CFLAGS) $< -o $@

Node.o: ../../alignment/Node.cpp $(HEADER2)
	$(CC) $(CFLAGS) $< -o $@

Edge.o: ../../alignment/Edge.cpp $(HEADER4)
	$(CC) $(CFLAGS) $< -o $@

clean: 
	rm -rf *o visualization



