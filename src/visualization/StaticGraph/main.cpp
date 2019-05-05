#include "GraphRenderer.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
using namespace std;



int main(int argc, char **argv){

	// Get Graph Infos
	Graph g;
	g.readFastaFiles(argv[1],atoi(argv[2]));
	vector<Node>& nodeList=g.getNodeList();
    vector<int>& numbOfKmers=g.getNumberOfKmers();
    
	//Open the window with white Background
    sf::RenderWindow window(sf::VideoMode(1600, 900), "MAS");
	window.clear(sf::Color::White);    
	window.display();

	//Create a GraphRenderer
	GraphRenderer GrRend(window, nodeList, 100);
    
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
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
	        GrRend.moveWindow(4,window);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
	        GrRend.moveWindow(0,window);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
	        GrRend.moveWindow(1,window);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
	        GrRend.moveWindow(2,window);
        }        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
	        GrRend.moveWindow(3,window);
        }
    
        window.display();
    }
    return 0;
}


			
	
