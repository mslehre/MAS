#include "../GraphRenderer.h"

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
    window.setFramerateLimit(120);
	window.display();

	//Create a GraphRenderer
	GraphRenderer GrRend(window, nodeList, 100);
    
    while (window.isOpen()) {
        
        auto mouse_pos = sf::Mouse::getPosition(window); // local mouse position in the window
        auto global_mouse_pos = window.mapPixelToCoords(mouse_pos); // mouse position in world coordinates
        sf::Event event;
        while (window.pollEvent(event)) {
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
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && GrRend.hovered && !GrRend.clicked) {
            GrRend.clickKmer();
            GrRend.showEdges(nodeList, global_mouse_pos, window);
        } else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && GrRend.clicked) {
            GrRend.deClickKmer(window, global_mouse_pos);
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && GrRend.clicked && GrRend.st_hovered) {
            GrRend.addToGame(window, global_mouse_pos);
        }
        if (GrRend.clicked && !GrRend.st_hovered && GrRend.isPositionEdge(global_mouse_pos)) {
            GrRend.edgeHover(global_mouse_pos, window);
        } else if (GrRend.clicked && GrRend.st_hovered && !GrRend.isPositionEdge(global_mouse_pos)) {
            GrRend.deEdgeHover(window);
        }
        if (!GrRend.hovered && GrRend.isPositionNode(global_mouse_pos)) {
            GrRend.highlightHover(global_mouse_pos, window);
        } else if (GrRend.hovered && !GrRend.isPositionNode(global_mouse_pos)) {
            GrRend.deHighlightHover(window);
        }
    
        window.display();
    }
    return 0;
}


			
	
