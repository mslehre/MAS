include ../../common.mk

CC = g++
OBJ = GUI_main.o Button.o Graph.o Node.o Edge.o
HEADER1 = ../../alignment/Graph.h
HEADER2 = ../../alignment/Node.h 
HEADER3 = ../../alignment/Edge.h
HEADER4 = Button.h 

all: GUI_main

GUI_main: $(OBJ)
	$(CC) $(CXXFLAGS) $(OBJ) -o $@ -lsfml-graphics -lsfml-window -lsfml-system

GUI_main.o: GUI_main.cc $(HEADER4)
	$(CC) -c $(CXXFLAGS) $< -o $@

Graph.o: ../../alignment/Graph.cc $(HEADER1) $(HEADER2) $(HEADER3)
	$(CC) -c $(CXXFLAGS) $< -o $@

Node.o: ../../alignment/Node.cc $(HEADER2)
	$(CC) -c $(CXXFLAGS) $< -o $@

Edge.o: ../../alignment/Edge.cc $(HEADER3)
	$(CC) -c $(CXXFLAGS) $< -o $@

Button.o: Button.cc $(HEADER1) $(HEADER4)
	$(CC) -c $(CXXFLAGS) $< -o $@

clean:
	rm -f *.o GUI_main
