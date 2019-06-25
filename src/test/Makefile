include ../common.mk
OBJ = MAS_tests.o
LD = -lgtest -lgtest_main -pthread

all: MAS_tests; ./MAS_tests

MAS_tests: $(OBJ)
	g++ $(CXXFLAGS) $(OBJ) -o MAS_tests $(LD)

MAS_tests.o: MAS_tests.cc $(H)
	g++ $(CXXFLAGS) -c MAS_tests.cc $(LD)

clean:
	rm -f *.o MAS_tests
