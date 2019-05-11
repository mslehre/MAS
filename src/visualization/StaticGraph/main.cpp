#include "../GraphRenderer.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
using namespace std;



int main(int argc, char **argv){

	// Get Graph Infos
	Graph g;
	g.readFastaFiles(argv[1],atoi(argv[2]));

    //Vektor mit Nodes die matches besitzen
	vector<Node>& nodeList=g.getNodes();
    vector<Edge>& edgeList=g.getEdges();

    //Auskommentiert weil Baum
    //vector<int>& numbOfKmers=g.getNumberOfKmers();
    
	//Open the window with white Background
    sf::RenderWindow window(sf::VideoMode(1600, 900), "MAS");
	window.clear(sf::Color::White);    
    window.setFramerateLimit(120);
	window.display();

	//Create a GraphRenderer
	GraphRenderer GrRend(window, nodeList, edgeList, 100);
    //create clock
    sf::Clock clock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::EventType::Closed)
                window.close();
            
            GrRend.eventHandler(event,window,nodeList);
		}
        GrRend.render(window);
        window.display();
        sf::Time elapsed = clock.restart();
        GrRend.update(elapsed.asSeconds());
    }
    return 0;
}


			
	
