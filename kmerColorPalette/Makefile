main: main.o kmercolor.o
	g++  main.o kmercolor.o -o main
main.o: main.cc kmercolor.h
	g++ -c main.cc
kmercolor.o: kmercolor.cc kmercolor.h
	g++ -c kmercolor.cc
clean:
	rm main *.o
