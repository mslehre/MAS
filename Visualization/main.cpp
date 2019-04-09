#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <iostream>
#include <algorithm>
#include <array>
#include <string>
#include "Graph.h"
using namespace std;


void drawGraph(sf::RenderWindow& window, Graph& g){
	int numStrings=g.getStringListSequence().size();	//Get the number of Strings from the Graph
	vector<int> numKmer=g.getNumberOfKmer();			//Get the number of Kmer per string
	vector<vector<string>> kmer=g.getSplitString();		//Get the strings
	sf::Font font; 	
	for(int i=0; i<numStrings; i++){
		for(int j=0; j<numKmer.at(i); j++){
			//Calculate the position of the rectangles
			sf::RectangleShape rectangle;
			rectangle.setSize(sf::Vector2f(100, 50));
			rectangle.setOutlineColor(sf::Color::Red);
			rectangle.setOutlineThickness(2);
			rectangle.setPosition(20+(180)*j, 20+(70)*i);
			window.draw(rectangle);

			if(j+1<numKmer.at(i)){
			//Calculate the lines between the rectangles
			sf::RectangleShape line;
			line.setSize(sf::Vector2f(100, 1));
			line.setOutlineColor(sf::Color::Red);
			line.setOutlineThickness(0.5);
			line.setPosition(120+(180)*j, 45+(70)*i);
			window.draw(line);

			//Calculate the triangles
			sf::CircleShape triangle;
			triangle.setRadius(10.f);
			triangle.setPointCount(3);
			triangle.setFillColor(sf::Color::Red);
			triangle.setOutlineThickness(2.f);
			triangle.setOutlineColor(sf::Color::Blue);
			triangle.setRotation(90.f);
			triangle.setPosition(170 +(180)*j, 35+(70)*i);
			window.draw(triangle);
			}

			//Set the text for the kmers in the rectangle 
			sf::Text text;
			//Load the font from file
			if(!font.loadFromFile("Amiko-Regular.ttf")){
				std::cout <<"Can't find the font file" << std::endl;
			}
			// select the font
			text.setFont(font); 
			text.setColor(sf::Color::Black);
			text.setPosition(20+(180)*j, 20+(70)*i);
			// set the string to display
			text.setString(kmer.at(i).at(j));
			// set the character size
			text.setCharacterSize(20);
			window.draw(text);
		}
	}
}

int main(int argc, char **argv){

	Graph g(2);									// example create object from class Graph with 3-mer 
	
	g.readingFastaFiles(argv[1]);				// reading fasta file

    sf::RenderWindow window(sf::VideoMode(1600, 1200), "MAS");

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::EventType::Closed)
                window.close();
        }
		window.clear(sf::Color::Blue);
		drawGraph(window,g);
		window.display();		
    }

    return 0;
}


			
	
