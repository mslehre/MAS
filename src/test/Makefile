include ../common.mk

CC = g++
OBJ = MAS_tests.o State.o Node.o Edge.o Graph.o colorlist.o
LD = -lgtest -lgtest_main -pthread -lsfml-graphics -lsfml-window -lsfml-system
HEADER1 = ../alignment/State.h
HEADER2 = ../alignment/Node.h
HEADER3 = ../alignment/Edge.h
HEADER4 = ../alignment/Graph.h
HEADER6 = ../visualization/colorlist.h

all: MAS_tests; ./MAS_tests

MAS_tests: $(OBJ)
	$(CC) $(CXXFLAGS) $(OBJ) -o MAS_tests $(LD)

MAS_tests.o: MAS_tests.cc $(HEADER1) $(HEADER2) $(HEADER3) $(HEADER4) $(HEADER6) $(H)
	$(CC) $(CXXFLAGS) -c MAS_tests.cc $(LD)

State.o: ../alignment/State.cc $(HEADER2) $(HEADER3) $(HEADER4)
	$(CC) $(CXXFLAGS) -c $< -o $@

Node.o: ../alignment/Node.cc $(HEADER2)
	$(CC) $(CXXFLAGS) -c $< -o $@

Edge.o: ../alignment/Edge.cc $(HEADER3)
	$(CC) $(CXXFLAGS) -c $< -o $@

Graph.o: ../alignment/Graph.cc $(HEADER4)
	$(CC) $(CXXFLAGS) -c $< -o $@

colorlist.o: ../visualization/colorlist.cc $(HEADER6)
	$(CC) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o MAS_tests
