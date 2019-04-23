all: GUI_main

GUI_main: GUI_main.o gui.o
	g++ -Wall GUI_main.o gui.o -o GUI_main -lsfml-graphics -lsfml-window -lsfml-system
GUI_main.o: GUI_main.cc gui.h
	g++ -Wall -std=c++11 -c GUI_main.cc
gui.o: gui.cc gui.h
	g++ -Wall -std=c++11 -c gui.cc
clean:
	rm *.o GUI_main
