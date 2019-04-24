CC = g++
OBJ = colortest_main.o colorlist.o colormap.o Graph.o
HEADER1 = ../../alignment/Graph.h
HEADER2 = ../colormap.h
HEADER3 = ../colorlist.h
CFLAGS1 = -c -Wall -std=c++11
CFLAGS2 = -c -Wall -std=c++11

all: Colortest_main

Colortest_main: $(OBJ)
	$(CC) -Wall $(OBJ) -o $@ -lsfml-graphics -lsfml-window -lsfml-system
colortest_main.o: colortest_main.cc $(HEADER1) $(HEADER2) $(HEADER3)
	$(CC) -Wall -c -std=c++11 colortest_main.cc
colormap.o: ../colormap.cc $(HEADER1) $(HEADER2) $(HEADER3)
	$(CC) $(CFLAGS1) ../colormap.cc
colorlist.o: ../colorlist.cc $(HEADER1) $(HEADER2) $(HEADER3)
	$(CC) $(CFLAGS1) ../colorlist.cc
Graph.o: ../../alignment/Graph.cpp $(HEADER1) $(HEADER2) $(HEADER3)
	$(CC) $(CFLAGS2) ../../alignment/Graph.cpp
clean:
	rm -f *.o colortest_main
