.PHONY: docu clean

all: docu
	cd src; make all

# make HTML documentation and PDF manual with doxygen 
docu:
	doxygen doxygen.conf
	cd doxygen/latex; make pdf

clean:
	rm -rf doxygen
	cd src; make clean
