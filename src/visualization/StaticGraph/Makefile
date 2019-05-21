include ../../common.mk
CC = g++
OBJ = main.o Graph.o Node.o GraphRenderer.o Edge.o State.o colormap.o colorlist.o ArrowShape.o FuncArrowShape.o DrawNode.o
HEADER1 = ../../alignment/Graph.h
HEADER2 = ../../alignment/Node.h 
HEADER3 = ../GraphRenderer.h
HEADER4 = ../../alignment/Edge.h
HEADER5 = ../colormap.h
HEADER6 = ../colorlist.h
HEADER7 = ../ArrowShape.h
HEADER8 = ../FuncArrowShape.h
HEADER9 = ../../alignment/State.h
HEADER10 = ../../alignment/DrawNode.h

all: visualization

visualization: $(OBJ)
	$(CC) $(CXXFLAGS) $(OBJ) -o  $@ -lsfml-graphics -lsfml-window -lsfml-system

main.o: main.cc $(HEADER1)
	$(CC) -c $(CXXFLAGS) $< -o  $@

GraphRenderer.o: ../GraphRenderer.cc $(HEADER3) $(HEADER1) $(HEADER7)
	$(CC) -c $(CXXFLAGS) $< -o $@

Graph.o: ../../alignment/Graph.cc $(HEADER1) $(HEADER2) $(HEADER4)
	$(CC) -c $(CXXFLAGS) $< -o $@

Node.o: ../../alignment/Node.cc $(HEADER2)
	$(CC) -c $(CXXFLAGS) $< -o $@

Edge.o: ../../alignment/Edge.cc $(HEADER4)
	$(CC) -c $(CXXFLAGS) $< -o $@

State.o: ../../alignment/State.cc $(HEADER9)
	$(CC) -c $(CXXFLAGS) $< -o $@

colorlist.o: ../colorlist.cc $(HEADER6)
	$(CC) -c $(CXXFLAGS) $< -o $@

colormap.o: ../colormap.cc $(HEADER5)
	$(CC) -c $(CXXFLAGS) $< -o $@

ArrowShape.o: ../ArrowShape.cc $(HEADER7)
	$(CC) -c $(CXXFLAGS) $< -o $@

FuncArrowShape.o: ../FuncArrowShape.cc $(HEADER7) $(HEADER8)
	$(CC) -c $(CXXFLAGS) $< -o $@

DrawNode.o: ../../alignment/DrawNode.cc $(HEADER10)
	$(CC) -c $(CXXFLAGS) $< -o $@

clean:
	rm -rf *o visualization
