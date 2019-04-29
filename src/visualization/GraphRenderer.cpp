#include "GraphRenderer.h"

using namespace std;

GraphRenderer::GraphRenderer(){}

void GraphRenderer::drawRectangle(sf::RenderWindow& window, int i, int j, vector<int> col, string kmer,
 sf::Font font, uint size){
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

 

void GraphRenderer::drawLine(sf::RenderWindow& window, int i, int j, uint size){
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


	
	
void GraphRenderer::drawGraph(sf::RenderWindow& window, Graph& g, uint size){
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
	vector<Node>& nodeList=g.getNodeList();
	
	//vector to remember wether a node has been draw or not
	vector<bool> colored;
	
	//Initialise the color vector
	vector<bool> initialiseColored;
	for(uint i=0; i<nodeList.size(); i++){
		colored.push_back(false);
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
	//if the node has not already been visited, then draw its rectangle
		if(!colored.at(i)){
	//Calculate the color of the rectangle
			for(uint l=0; l<stringColor.size(); l++){
	//Compare the substring with every substring that already has an explicit color
				if(nodeList.at(i).kmer == stringColor.at(l)){
	//If the substring matches a substring, then use its color to draw the rectangle
					colorCounter = l;
					stopped=true;
				}
			}
	
			if(!stopped){
	//save the string of the new color
				stringColor.push_back(nodeList.at(i).kmer);
	//if it doesn't match any substring, then use a new color
				colorCounter = stringColor.size()-1;
			}

	//draw the rectangle and the line
			colored.at(i) = true;
			drawRectangle(window, nodeList.at(i).i, nodeList.at(i).j ,color.at(colorCounter), 
				nodeList.at(i).kmer, font, size);
			if(i!=nodeList.size()-1 && nodeList.at(i).i==nodeList.at(i+1).i){
			drawLine(window, nodeList.at(i).i, nodeList.at(i).j , size);
			}
			stopped = false;
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

Node& GraphRenderer::positionToNode(uint xpos, uint ypos, vector<Node>& nodeList, uint size){
	uint x = (xpos-size*0.2)/(size*1.8);
	uint y = (ypos-size*0.2)/((size/2)*1.8);
	Node& actualNode;
	for(auto &node : nodeList) {
		if (node.i == x && node.j == y){
			actualNode = node;
			break;
		}
	}
	return actualNode;
}


bool GraphRenderer::isPositionNode(uint xpos, uint ypos, uint size){
	uint x = (xpos-size*0.2)/(size*1.8);
	uint y = (ypos-size*0.2)/((size/2)*1.8);;
	if(xpos-x*size*1.8-size*0.2<size && ypos-y*(size/2)*1.8-size*0.2<size/2){
		return true;
	}
	else{
		return false;
	}
}

void GraphRenderer::highlightRectangle(Node& node, sf::Color color, sf::RenderWindow& window, uint size){
	sf::RectangleShape rectangle;
	rectangle.setSize(sf::Vector2f(size, size/2));
	rectangle.setFillColor(sf::Color::Transparent);
	rectangle.setOutlineColor(color);
	rectangle.setOutlineThickness(5);
	rectangle.setPosition(size*0.2+(size*1.8)*node.j, size*0.2+((size/2)*1.8)*node.i);
	window.draw(rectangle);
}

	

