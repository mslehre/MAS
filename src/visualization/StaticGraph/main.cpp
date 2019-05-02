#include "GraphRenderer.h"

using namespace std;

int main(int argc, char **argv){

	// example create object from class Graph
	Graph g;									
	
	// read fasta file
	g.readFastaFiles(argv[1],atoi(argv[2]));				
	
	//Get the nodelist
	vector<Node>& nodeList=g.getNodeList();

	//
	vector<int>& numbOfKmers=g.getNumberOfKmers();

	//Create a GraphRenderer
	GraphRenderer graphRenderer;

	//Open the window
    sf::RenderWindow window(sf::VideoMode(1600, 900), "MAS");
	//Set the backcolor
	window.clear(sf::Color::White);

	uint maxLength=1;

	//Calculate the maximal number of nodes of every sequence
	for(auto &node : nodeList){	
			if(maxLength<node.adjNodes.size()){
				maxLength=node.adjNodes.size();	
		}
	}
	cout<<nodeList.size()<<endl;
	cout<<numbOfKmers.size()<<endl;
	    
	uint size;
	Node actualNode;
	//Initialise the actual indices 
	int actual_i = -1;
	int actual_j = -1;
	//Calculate the size of the rectangles
    if (numbOfKmers.size()!=0) {
	    //numbOfKmers.size() is the number of sequences
	    unsigned int possibleSize1 = 300/maxLength;
	    unsigned int possibleSize2 = 1200/numbOfKmers.size();

	    if(possibleSize1<possibleSize2){
		    size = possibleSize1;
	    }
	    else{
		    size = possibleSize2;
	    }

	    //Initialise the acutal Node
	    actualNode=nodeList.at(0);
	    
	    //Draw the graph
	    graphRenderer.drawGraph(window,g,size);
    } else {
        actualNode = g.nodeListAll[0][0];
        size = 10;
    }
    
	//Initialise choosed
    bool choosed=false;
	window.display();
    sf::View view;
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
			
		//Save the position of a left mouse click
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
			sf::Vector2i globalPosition = sf::Mouse::getPosition(window);
			
		//If the click has been in the window and on a rectangle
			if(globalPosition.x<=1600 && 0<=globalPosition.x && globalPosition.y<=900 
				&& 0<=globalPosition.y && graphRenderer.isPositionNode(globalPosition.x, globalPosition.y, size)){
		//Calculate the node on which has been clicked
				actualNode = graphRenderer.positionToNode(globalPosition.x, globalPosition.y, nodeList, size);
		        
		    //If it's the first node that has been choosen, set the outline color red
			    if(!choosed && (actual_i!=actualNode.i || actual_j!=actualNode.j) && actualNode.i!=numbOfKmers.size()-1){
				    graphRenderer.highlightRectangle(actualNode, g, window, sf::Color::Red, size);
				    actual_i = actualNode.i;
				    actual_j = actualNode.j;
				    choosed = true;

		    //Set for all nodes that can be choosen from the node above that has been picked the outline color white
				    for(uint l=0; l<actualNode.adjNodes.size(); l++){
					    graphRenderer.highlightRectangle(actualNode.adjNodes.at(l), g, window, sf::Color::Black, size);
				    }		
			    }	
			}		
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Right)){
            if(choosed) {
                    graphRenderer.removeRectangle();
                    window.clear(sf::Color::White);
	                graphRenderer.drawGraph(window,g,size);
                    choosed = false;
            }
        }
        
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            window.setView(window.getDefaultView());
	        window.clear(sf::Color::White);
	        graphRenderer.drawGraph(window,g,size);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            sf::View now = window.getView();
            now.move(0,10);
            window.setView(now);
	        window.clear(sf::Color::White);
	        graphRenderer.drawGraph(window,g,size);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            sf::View now = window.getView();
            now.move(-10,0);
            window.setView(now);
	        window.clear(sf::Color::White);
	        graphRenderer.drawGraph(window,g,size);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            sf::View now = window.getView();
            now.move(10,0);
            window.setView(now);
	        window.clear(sf::Color::White);
	        graphRenderer.drawGraph(window,g,size);
        }        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            sf::View now = window.getView();
            now.move(0,-10);
            window.setView(now);
	        window.clear(sf::Color::White);
	        graphRenderer.drawGraph(window,g,size);
        }
    
        window.display();
    }
    return 0;
}


			
	
