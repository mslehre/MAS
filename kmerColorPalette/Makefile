main: main.o kmercolor.o
	g++ main.o kmercolor.o -o main -lsfml-graphics -lsfml-window -lsfml-system
main.o: main.cc kmercolor.h
	g++ -c -std=c++11 main.cc
kmercolor.o: kmercolor.cc kmercolor.h
	g++ -c -std=c++11 kmercolor.cc
clean:
	rm main *.o
