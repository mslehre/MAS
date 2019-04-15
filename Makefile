.PHONY: docu clean

all: docu

# make HTML documentation and PDF manual with doxygen 
docu:
	cd doxytest; doxygen doxygen.conf
	cd doxytest/doxygen/latex; make pdf
	cd doxytest; make

clean:
	rm -r doxytest/doxygen
