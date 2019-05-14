CC = g++
OBJ = main.o Graph.o Node.o GraphRenderer.o Edge.o colormap.o colorlist.o ArrowShape.o FuncArrowShape.o
HEADER1 = ../../alignment/Graph.h
HEADER2 = ../../alignment/Node.h 
HEADER3 = ../GraphRenderer.h
HEADER4 = ../../alignment/Edge.h
HEADER5 = ../colormap.h
HEADER6 = ../colorlist.h
HEADER7 = ../ArrowShape.h
HEADER8 = ../FuncArrowShape.h
CFLAGS = -c -std=c++11 -Wall 

all: visualization

visualization: $(OBJ) 
	$(CC) $(OBJ) -o  $@ -lsfml-graphics -lsfml-window -lsfml-system

main.o: main.cc $(HEADER1)
	$(CC) $(CFLAGS) $< -o  $@

GraphRenderer.o: ../GraphRenderer.cc $(HEADER3) $(HEADER1) $(HEADER7)
	$(CC) $(CFLAGS) $< -o $@

Graph.o: ../../alignment/Graph.cc $(HEADER1) $(HEADER2) $(HEADER4)
	$(CC) $(CFLAGS) $< -o $@

Node.o: ../../alignment/Node.cc $(HEADER2)
	$(CC) $(CFLAGS) $< -o $@

Edge.o: ../../alignment/Edge.cc $(HEADER4)
	$(CC) $(CFLAGS) $< -o $@

colorlist.o: ../colorlist.cc $(HEADER6)
	$(CC) $(CFLAGS) $< -o $@

colormap.o: ../colormap.cc $(HEADER5)
	$(CC) $(CFLAGS) $< -o $@

ArrowShape.o: ../ArrowShape.cc $(HEADER7) 
	$(CC) $(CFLAGS) $< -o $@

FuncArrowShape.o: ../FuncArrowShape.cc $(HEADER7) $(HEADER8) 
	$(CC) $(CFLAGS) $< -o $@

clean: 
	rm -rf *o visualization	
