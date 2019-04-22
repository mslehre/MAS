.PHONY: docu clean

all: docu

# make HTML documentation and PDF manual with doxygen 
docu:
	doxygen doxygen.conf
	cd doxygen/latex; make pdf

clean:
	rm -r doxygen
