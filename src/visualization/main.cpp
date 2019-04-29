#include "GraphRenderer.h"

using namespace std;

int main(int argc, char **argv){

	// example create object from class Graph
	Graph g;									
	
	// read fasta file
	g.readFastaFiles(argv[1],atoi(argv[2]));				
	
	//Get the nodelist
	vector<vector<Node>>& nodeList=g.getNodeList();

	//Get the edgelist
	vector<vector<vector<Node>>>& listOfEdges=g.getEdgeList();

	//Open the window
    sf::RenderWindow window(sf::VideoMode(1600, 900), "MAS");

	uint maxLength=0;


	//Calculate the maximal number of kmers of every sequence
	/*for(uint i=0; i<listOfEdges.size(); i++){	
		for(uint j=0; j<listOfEdges.at(i).size();j++){
			if(maxLength<listOfEdges.at(i).at(j).size()){
				maxLength=listOfEdges.at(i).at(j).size();
			}
		}
	}
	//Calculate the size of the rectangles
	uint possibleSize1 = 400/maxLength;
	uint possibleSize2 = 1200/nodeList.size();*/
	uint size=100;
	
	if(possibleSize1<possibleSize2){
		size = possibleSize1;
	}
	else{
		size = possibleSize2;
	}

	//Create a GraphRenderer
	GraphRenderer graphRenderer;
	//Set the backcolor
	window.clear(sf::Color::Blue);

	//Initialise the acutal Node
	Node& actualNode=nodeList.at(0).at(0);
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
	cout<<"first"<<endl;
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
				for(uint l=0; l<listOfEdges.at(actual_i).at(actual_j).size(); l++){
					graphRenderer.highlightRectangle(listOfEdges.at(actual_i).at(actual_j).at(l),
						sf::Color::White, window, size);
				}
				
	
					
			}
		window.display();
			
										
        }
		
			
    }
		

    return 0;
}


			
	
