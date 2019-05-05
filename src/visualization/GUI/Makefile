all: GUI_main

GUI_main: GUI_main.o button.o
	g++ -Wall GUI_main.o button.o -o GUI_main -lsfml-graphics -lsfml-window -lsfml-system

GUI_main.o: GUI_main.cc button.h
	g++ -Wall -std=c++11 -c GUI_main.cc

button.o: button.cc button.h
	g++ -Wall -std=c++11 -c button.cc

clean:
	rm -f *.o GUI_main
