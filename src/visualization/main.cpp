#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <iostream>
#include <algorithm>
#include <array>
#include <string>
#include "Graph.h"
#include <stdlib.h>


using namespace std;

void drawRectangle(sf::RenderWindow& window, int i, int j, vector<int> col, string kmer, sf::Font font, uint size){
	sf::RectangleShape rectangle;
	rectangle.setSize(sf::Vector2f(size, size/2));
	rectangle.setFillColor(sf::Color(col.at(0), col.at(1), col.at(2)));
	rectangle.setPosition(size*0.2+(size*1.8)*j, size*0.2+((size/2)*1.8)*i);
	window.draw(rectangle);

	
	//Set the text for the kmers in the rectangle 
	sf::Text text;
	//Load the font from file
	if(!font.loadFromFile("Amiko-Regular.ttf")){
		std::cout <<"Can't find the font file" << std::endl;
	}
	// select the font
	text.setFont(font); 
	text.setColor(sf::Color::Black);
	text.setPosition(size*0.2+(size*1.8)*j, size*0.2+(size/2)*1.8*i);
	// set the string to display
	text.setString(kmer);
			
	// set the character size
	text.setCharacterSize(size*0.25);
	window.draw(text);	
}

 

void drawLine(sf::RenderWindow& window, int i, int j, uint size){
	sf::RectangleShape line;
	line.setSize(sf::Vector2f(size, 1));
	line.setOutlineColor(sf::Color::Red);
	line.setOutlineThickness(0.5);
	line.setPosition(size*1.2+(size*1.8)*j, size*0.45+(size/2)*1.8*i);
	window.draw(line);

	sf::CircleShape triangle;
	triangle.setRadius(size*0.1);
	triangle.setPointCount(3);
	triangle.setFillColor(sf::Color::Red);
	triangle.setOutlineThickness(2.f);
	triangle.setOutlineColor(sf::Color::Blue);
	triangle.setRotation(90.f);
	triangle.setPosition(size*1.7 +(size*1.8)*j, size*0.35+(size/2)*1.8*i);
	window.draw(triangle);
}


	
	
void drawGraph(sf::RenderWindow& window, Graph& g, uint size){
	//create a vector of possible fillcolor (later I will get this from Lucas)
	sf::Font font;
	vector<vector<int>> color;
	vector<int> fillColor;
	fillColor.push_back(255);
	fillColor.push_back(0);
	fillColor.push_back(0);
	color.push_back(fillColor);
	fillColor.push_back(0);
	fillColor.push_back(255);
	fillColor.push_back(0);
	color.push_back(fillColor);
	fillColor.clear();
	fillColor.push_back(0);
	fillColor.push_back(0);
	fillColor.push_back(255);
	color.push_back(fillColor);
	fillColor.clear();
	fillColor.push_back(0);
	fillColor.push_back(128);
	fillColor.push_back(255);
	color.push_back(fillColor);
	fillColor.clear();
	fillColor.push_back(128);
	fillColor.push_back(0);
	fillColor.push_back(255);
	color.push_back(fillColor);
	fillColor.clear();
	fillColor.push_back(255);
	fillColor.push_back(128);
	fillColor.push_back(0);
	color.push_back(fillColor);
	fillColor.clear();
	fillColor.push_back(255);
	fillColor.push_back(0);
	fillColor.push_back(128);
	color.push_back(fillColor);
	fillColor.clear();
	fillColor.push_back(0);
	fillColor.push_back(255);
	fillColor.push_back(128);
	color.push_back(fillColor);
	fillColor.clear();
	fillColor.push_back(128);
	fillColor.push_back(255);
	fillColor.push_back(0);
	color.push_back(fillColor);
	fillColor.clear();

	//get the edges and nodes 
	vector<vector<vector<Node>>>& listOfEdges=g.getEdgeList();
	vector<vector<Node>>& nodeList=g.getNodeList();
	
	//vector to remember wether a node has been draw or not
	vector<vector<bool>> colored;
	//Vector to remember which color has been used for which substring
	vector<string> stringColor;
	
	

	//Initialise the color vector
	vector<bool> initialiseColored;
	for(uint i=0; i<nodeList.size(); i++){
		for(uint j=0; j<nodeList.at(i).size(); j++){
			initialiseColored.push_back(false);
		}
		colored.push_back(initialiseColored);
		initialiseColored.clear();
	}

	
	int index;
	//A variable to save wether we stopped during a search process or not
	bool stopped = false;
	//A variable to save the number of the different colors that have been used 
	int colorCounter;
	//To avoid problems with the first color
	stringColor.push_back("empty");

	//Visit every node in the nodelist	
	for(uint i = 0; i<nodeList.size(); i++){
		for(uint j = 0; j<nodeList.at(i).size(); j++){
	//if the node has not already been visited, then draw its rectangle
			if(!colored.at(i).at(j)){
	//Calculate the color of the rectangle
			for(uint l=0; l<stringColor.size(); l++){
	//Compare the substring with every substring that already has an explicit color
				if(nodeList.at(i).at(j).kmer == stringColor.at(l)){
	//If the substring matches a substring, then use its color to draw the rectangle
					colorCounter = l;
					stopped=true;
				}
			}
	
			if(!stopped){
	//save the string of the new color
				stringColor.push_back(nodeList.at(i).at(j).kmer);
	//if it doesn't match any substring, then use a new color
				colorCounter = stringColor.size()-1;
			}

	//draw the rectangle and the line
			colored.at(i).at(j) = true;
			drawRectangle(window, i,j,color.at(colorCounter), nodeList.at(i).at(j).kmer, font, size);
			if(j+1<nodeList.at(i).size()){
			drawLine(window, i, j, size);
			}
			stopped=false;
		}

	//Visit every adjacent node and color with the same color
	//Here it will also be possible to draw the edges 
			/*if(i+1<nodeList.size()){
			for(uint h=0; h<listOfEdges.at(i).at(j).size(); h++){
				index = listOfEdges.at(i).at(j).at(h).j;
				cout <<i<< ", "<<j<< ", "<<index<<endl;
				colored.at(i+1).at(index)=true;
				drawRectangle(window, i+1,index,color.at(colorCounter), nodeList.at(i).at(j).kmer, font);
				if(j+1<nodeList.at(i+1).size()){
				drawLine(window, i+1,index);
				}
			}
		
		}*/
	}	
	}
}

Node& positionToNode(uint xpos, uint ypos, vector<vector<Node>>& nodeList, uint size){
	uint x = (xpos-size*0.2)/(size*1.8);
	uint y = (ypos-size*0.2)/((size/2)*1.8);
	Node& actualNode=nodeList.at(y).at(x);
	return actualNode;
}


bool isPositionNode(uint xpos, uint ypos, uint size){
	uint x = (xpos-size*0.2)/(size*1.8);
	uint y = (ypos-size*0.2)/((size/2)*1.8);;
	if(xpos-x*size*1.8-size*0.2<size && ypos-y*(size/2)*1.8-size*0.2<size/2){
		return true;
	}
	else{
		return false;
	}
}


void highlightRectangle(Node node, sf::Color color, sf::RenderWindow& window, uint size){
	sf::RectangleShape rectangle;
	rectangle.setSize(sf::Vector2f(size, size/2));
	rectangle.setFillColor(sf::Color::Transparent);
	rectangle.setOutlineColor(color);
	rectangle.setOutlineThickness(5);
	rectangle.setPosition(size*0.2+(size*1.8)*node.j, size*0.2+((size/2)*1.8)*node.i);
	window.draw(rectangle);
}

	


int main(int argc, char **argv){

	// example create object from class Graph
	Graph g;									
	
	// read fasta file
	g.readFastaFiles(argv[1],atoi(argv[2]));				
	
	//Get the nodelist
	vector<vector<Node>>& nodeList=g.getNodeList();
	//Get the edgelist
	vector<vector<vector<Node>>>& listOfEdges=g.getEdgeList();
    sf::RenderWindow window(sf::VideoMode(1600, 900), "MAS");
	sf::View view;
	uint maxLength=0;
	for(uint i=0; i<listOfEdges.size(); i++){	
		for(uint j=0; j<listOfEdges.at(i).size();j++){
			if(maxLength<listOfEdges.at(i).at(j).size()){
				maxLength=listOfEdges.at(i).at(j).size();
			}
		}
	}
	uint possibleSize1 = 400/maxLength;
	uint possibleSize2 = 1200/nodeList.size();
	uint size;

	if(possibleSize1<possibleSize2){
		size = possibleSize1;
	}
	else{
		size = possibleSize2;
	}
		cout <<size<<endl;
	//uint size=50;


	
	//Set the backcolor
	window.clear(sf::Color::Blue);
	//Draw the graph
	drawGraph(window,g,size);
	window.display();
	//Initialise the acutal Node
	Node& actualNode=nodeList.at(0).at(0);
	//Initialise the actual indices 
	int actual_i = -1;
	int actual_j = -1;

	bool choosed=false;
	 


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
	
			//Save the position of a left mouse click
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
				sf::Vector2i globalPosition = sf::Mouse::getPosition(window);
			
			//If the click has been in the window and on a rectangle
				if(globalPosition.x<=1600 && 0<=globalPosition.x && globalPosition.y<=900 
					&& 0<=globalPosition.y && isPositionNode(globalPosition.x, globalPosition.y, size)){
			//Calculate the node on which has been clicked
					actualNode = positionToNode(globalPosition.x, globalPosition.y, nodeList, size);
				}
		
			//If it's the first node that has been choosen, set the outline color red
				if(!choosed && (actual_i!=actualNode.i || actual_j!=actualNode.j)){
					highlightRectangle(actualNode, sf::Color::Red, window, size);
					actual_i = actualNode.i;
					actual_j = actualNode.j;
					choosed = true;

			//Set for all nodes that can be choosen from the node above that has been picked the outline color white
					for(uint l=0; l<listOfEdges.at(actual_i).at(actual_j).size(); l++){
						highlightRectangle(listOfEdges.at(actual_i).at(actual_j).at(l), sf::Color::White, window, size);
					}
					window.display();	
					
				}
					
			}
		window.display();	
										
        }
		
			
    }
		

    return 0;
}


			
	
