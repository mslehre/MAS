#include "GraphRenderer.h"
#include <cmath>
using namespace std;

//ignore this, this is just a help method, which get solved later
vector<string> giveKmers(vector<Node>& Sequences) {
    vector<string> allKmers; // The set of all different Kmers
    int index;
    for (uint i = 0; i<Sequences.size(); i++) {
        index = 0;
        for (uint j = 0; j<i; j++) {
            if(Sequences[i].kmer == Sequences[j].kmer){
                index = 1;
                break;            
            }
        }
        if(index == 0) {
            allKmers.push_back(Sequences[i].kmer);
        }
    }
    return allKmers;
}

GraphRenderer::GraphRenderer() { loaded = false;
}

void GraphRenderer::drawRectangle(sf::RenderWindow& window, int i, int j, sf::Color col, string kmer,
 sf::Font font, uint size){
    if (!loaded){
	    sf::RectangleShape rectangle;
	    rectangle.setSize(sf::Vector2f(size, size/2));
	    rectangle.setFillColor(col);
	    rectangle.setPosition(size*0.2+(size*1.8)*j, size*0.2+((size/2)*1.8)*i);
	    window.draw(rectangle);
        while(rectangles.size()!=i+1) {
            vector<sf::RectangleShape> fill;
            rectangles.push_back(fill);
        }
        rectangles[i].push_back(rectangle);
    } else {
        
        window.draw(rectangles[i][j]);
    }
	
	sf::Text text;
	//Load the font from file
	//Set the text for the kmers in the rectangle 
	if(!font.loadFromFile("Amiko-Regular.ttf")){
		std::cout <<"Can't find the font file" << std::endl;
	}
	// select the font
	text.setFont(font); 
	text.setColor(sf::Color::Black);
	text.setPosition(size*0.2+(size*1.8)*j+size*0.1, size*0.2+(size/2)*1.8*i+(size/2)*0.1);
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
    
    // get Graph information for the Kmerlist and Colorlist
	vector<Node>& nodeList=g.getNodeList();
    
    vector<string> Kmers = giveKmers(nodeList);
    // initialize the colorlist
    colorlist colorExample(Kmers.size());

    // initialize the colormap
    vector<sf::Color> colors = colorExample.giveList(); // vector of different colors
    colormap mapExample(Kmers, colors);


	//Visit every node in the nodelist
	    for(uint i = 0; i<nodeList.size(); i++){
		    drawRectangle(window, nodeList[i].i, nodeList[i].j, mapExample.Map(nodeList[i].kmer), nodeList[i].kmer, font, size);
		    if(i!=nodeList.size()-1 && nodeList.at(i).i==nodeList.at(i+1).i){
                drawLine(window, nodeList[i].i, nodeList[i].j , size);
		    }
	    }
    loaded = true;
}

Node GraphRenderer::positionToNode(uint xpos, uint ypos, vector<Node>& nodeList, uint size){
	uint x = (xpos-size*0.2)/(size*1.8);
	uint y = (ypos-size*0.2)/((size/2)*1.8);
	Node actualNode;
	for(auto &node : nodeList) {
		if (node.i == y && node.j == x){
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

void GraphRenderer::highlightRectangle(Node& node, Graph& g, sf::RenderWindow& window, sf::Color color, uint size){
	rectangles[node.i][node.j].setOutlineColor(color);
	rectangles[node.i][node.j].setOutlineThickness(5);
    drawGraph(window,g,size);
}

void GraphRenderer::removeRectangle(){
    rectangles.clear();
    loaded = false;
}

	

