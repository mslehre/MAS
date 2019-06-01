include ../common.mk

CC = g++
OBJ = gameMain.o Button.o Graph.o Node.o Edge.o Gamemaster.o sequence.o State.o generator.o colorlist.o colormap.o GraphRenderer.o ArrowShape.o FuncArrowShape.o
HEADER1 = ../alignment/Graph.h
HEADER2 = ../alignment/Node.h
HEADER3 = ../alignment/Edge.h
HEADER4 = ../alignment/State.h
HEADER5 = ../alignment/DrawNode.h
HEADER6 = ../SequenceSimulation/sequence.h
HEADER7 = ../SequenceSimulation/generator.h
HEADER8 = ../visualization/colormap.h
HEADER9 = ../visualization/colorlist.h
HEADER10 = ../visualization/GraphRenderer.h
HEADER11 = ../visualization/ArrowShape.h
HEADER12 = ../visualization/FuncArrowShape.h
HEADER13 = ../visualization/Button.h
HEADER14 = Gamemaster.h

all: game_main

game_main: $(OBJ)
	$(CC) $(CXXFLAGS) $(OBJ) -o $@ -lsfml-graphics -lsfml-window -lsfml-system

gameMain.o: gameMain.cc $(HEADER10) $(HEADER13) $(HEADER14)
	$(CC) -c $(CXXFLAGS) $< -o $@

Graph.o: ../alignment/Graph.cc $(HEADER1) $(HEADER2) $(HEADER3)
	$(CC) -c $(CXXFLAGS) $< -o $@

Node.o: ../alignment/Node.cc $(HEADER2)
	$(CC) -c $(CXXFLAGS) $< -o $@

Edge.o: ../alignment/Edge.cc $(HEADER3)
	$(CC) -c $(CXXFLAGS) $< -o $@

State.o: ../alignment/State.cc $(HEADER4)
	$(CC) -c $(CXXFLAGS) $< -o $@

Button.o: ../visualization/Button.cc $(HEADER1) $(HEADER13)
	$(CC) -c $(CXXFLAGS) $< -o $@

sequence.o: ../SequenceSimulation/sequence.cc $(HEADER6)
	$(CC) -c $(CXXFLAGS) $< -o $@

generator.o: ../SequenceSimulation/generator.cc $(HEADER7)
	$(CC) -c $(CXXFLAGS) $< -o $@

colormap.o: ../visualization/colormap.cc $(HEADER9)
	$(CC) -c $(CXXFLAGS) $< -o $@

Gamemaster.o: Gamemaster.cc $(HEADER1) $(HEADER4) $(HEADER5) $(HEADER6) $(HEADER8) $(HEADER9) $(HEADER14)
	$(CC) -c $(CXXFLAGS) $< -o $@

colorlist.o: ../visualization/colorlist.cc $(HEADER8)
	$(CC) -c $(CXXFLAGS) $< -o $@

GraphRenderer.o: ../visualization/GraphRenderer.cc $(HEADER1) $(HEADER10) $(HEADER11) $(HEADER13)
	$(CC) -c $(CXXFLAGS) $< -o $@

ArrowShape.o: ../visualization/ArrowShape.cc $(HEADER11)
	$(CC) -c $(CXXFLAGS) $< -o $@

FuncArrowShape.o: ../visualization/FuncArrowShape.cc $(HEADER11) $(HEADER12)
	$(CC) -c $(CXXFLAGS) $< -o $@

clean:
	rm -f *.o game_main
