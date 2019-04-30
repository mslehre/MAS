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
	vector<array<unsigned int,2>>& numbOfKmers=g.getNumberOfKmers();

	//Open the window
    sf::RenderWindow window(sf::VideoMode(1600, 900), "MAS");

	uint maxLength=1;


	//Calculate the maximal number of nodes of every sequence
	for(auto &node : nodeList){	
			if(maxLength<node.adjNodes.size()){
				maxLength=node.adjNodes.size();	
			}
	}
	cout<<nodeList.size()<<endl;
	cout<<numbOfKmers.size()<<endl;
	
	//Calculate the size of the rectangles
	//numbOfKmers.size() is the number of sequences
	unsigned int possibleSize1 = 300/maxLength;
	unsigned int possibleSize2 = 1200/numbOfKmers.size();

	
	uint size;
	if(possibleSize1<possibleSize2){
		size = possibleSize1;
	}
	else{
		size = possibleSize2;
	}
	
	//uint size=100;

	//Create a GraphRenderer
	GraphRenderer graphRenderer;
	//Set the backcolor
	window.clear(sf::Color::Blue);

	//Initialise the acutal Node
	Node actualNode=nodeList.at(0);
	//Initialise the actual indices 
	int actual_i = -1;
	int actual_j = -1;
	
	//Initialise choosed
	bool choosed=false;

	//Draw the graph
	graphRenderer.drawGraph(window,g,size);
	window.display();
		
	
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
			}
		
		//If it's the first node that has been choosen, set the outline color red
			if(!choosed && (actual_i!=actualNode.i || actual_j!=actualNode.j)){
				graphRenderer.highlightRectangle(actualNode, sf::Color::Red, window, size);
				actual_i = actualNode.i;
				actual_j = actualNode.j;
				choosed = true;

		//Set for all nodes that can be choosen from the node above that has been picked the outline color white
				for(uint l=0; l<actualNode.adjNodes.size(); l++){
					graphRenderer.highlightRectangle(actualNode.adjNodes.at(l), sf::Color::White, window, size);
				}		
			}
		window.display();
			
										
        }		
    }
    return 0;
}


			
	
