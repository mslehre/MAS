CC = g++
OBJ = main.o Graph.o Node.o GraphRenderer.o
HEADER1 = Graph.h
HEADER2 = Node.h 
HEADER3 = GraphRenderer.h
CFLAGS = -c -std=c++11 -Wall 
all: visualization
visualization: $(OBJ) 
	$(CC) $(OBJ) -o  $@ -lsfml-graphics -lsfml-window -lsfml-system

main.o: ../main.cpp $(HEADER1)
	$(CC) $(CFLAGS) $< -o  $@

GraphRenderer.o: GraphRenderer.cpp $(HEADER3) $(HEADER1)
	$(CC) $(CFLAGS) $< -o $@

Graph.o: Graph.cpp $(HEADER1) $(HEADER2)
	$(CC) $(CFLAGS) $< -o $@

Node.o: Node.cpp $(HEADER2)
	$(CC) $(CFLAGS) $< -o $@

clean: 
	rm -rf *o visualization



