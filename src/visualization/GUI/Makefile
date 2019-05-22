include ../../common.mk

CC = g++
OBJ = GUI_main.o Button.o Graph.o Node.o Edge.o Gamemaster.o sequence.o State.o generator.o colorlist.o colormap.o GraphRenderer.o ArrowShape.o FuncArrowShape.o
HEADER1 = ../../alignment/Graph.h
HEADER2 = ../../alignment/Node.h 
HEADER3 = ../../alignment/Edge.h
HEADER4 = Button.h 
HEADER5 = ../../alignment/State.h
HEADER6 = ../../alignment/DrawNode.h
HEADER7 = ../../SequenceSimulation/sequence.h
HEADER8 = Gamemaster.h 
HEADER9 = ../colormap.h
HEADER10 = ../colorlist.h
HEADER11 = ../../SequenceSimulation/generator.h
HEADER12 = ../GraphRenderer.h
HEADER13 = ../ArrowShape.h
HEADER14 = ../FuncArrowShape.h

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

State.o: ../../alignment/State.cc $(HEADER5)
	$(CC) -c $(CXXFLAGS) $< -o $@

generator.o: ../../SequenceSimulation/generator.cc $(HEADER11)
	$(CC) -c $(CXXFLAGS) $< -o $@

sequence.o: ../../SequenceSimulation/sequence.cc $(HEADER7)
	$(CC) -c $(CXXFLAGS) $< -o $@

Gamemaster.o: Gamemaster.cc $(HEADER1) $(HEADER5) $(HEADER6) $(HEADER7) $(HEADER8) $(HEADER9) $(HEADER10)
	$(CC) -c $(CXXFLAGS) $< -o $@

colorlist.o: ../colorlist.cc $(HEADER9)
	$(CC) -c $(CXXFLAGS) $< -o $@

colormap.o: ../colormap.cc $(HEADER10)
	$(CC) -c $(CXXFLAGS) $< -o $@

GraphRenderer.o: ../GraphRenderer.cc $(HEADER12) $(HEADER1) $(HEADER13)
	$(CC) -c $(CXXFLAGS) $< -o $@

FuncArrowShape.o: ../FuncArrowShape.cc $(HEADER13) $(HEADER14)
	$(CC) -c $(CXXFLAGS) $< -o $@

clean:
	rm -f *.o GUI_main
