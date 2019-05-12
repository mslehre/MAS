CC = g++
OBJ = colortest_main.o colorlist.o colormap.o Graph.o Edge.o Node.o
HEADER1 = ../../alignment/Graph.h
HEADER2 = ../colormap.h
HEADER3 = ../colorlist.h
HEADER4 = ../../alignment/Edge.h
HEADER5 = ../../alignment/Node.h
CFLAGS = -c -Wall -std=c++11

all: Colortest_main

Colortest_main: $(OBJ)
	$(CC) -Wall $(OBJ) -o $@ -lsfml-graphics -lsfml-window -lsfml-system
colortest_main.o: colortest_main.cc $(HEADER1) $(HEADER2) $(HEADER3)
	$(CC) -Wall -c -std=c++11 colortest_main.cc
colormap.o: ../colormap.cc $(HEADER1) $(HEADER2) $(HEADER3)
	$(CC) $(CFLAGS) ../colormap.cc
colorlist.o: ../colorlist.cc $(HEADER1) $(HEADER2) $(HEADER3)
	$(CC) $(CFLAGS) ../colorlist.cc
Graph.o: ../../alignment/Graph.cc $(HEADER1) $(HEADER2) $(HEADER3) $(HEADER4) $(HEADER5)
	$(CC) $(CFLAGS) ../../alignment/Graph.cc
Edge.o: ../../alignment/Edge.cc $(HEADER1) $(HEADER2) $(HEADER3) $(HEADER4) $(HEADER5)
	$(CC) $(CFLAGS) ../../alignment/Edge.cc
Node.o: ../../alignment/Node.cc $(HEADER1) $(HEADER2) $(HEADER3) $(HEADER4) $(HEADER5)
	$(CC) $(CFLAGS) ../../alignment/Node.cc
clean:
	rm -f *.o colortest_main
