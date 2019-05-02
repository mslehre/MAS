#include "GraphRenderer.h"
#include <cmath>
using namespace std;

//ignore this, this is just a help method, which get solved later
vector<string> giveKmers(vector<string>& Sequences, int k) {
    vector<int> SequenceSizes; // A tupel of integers, where the i integer n stands for n Kmers in Sequencs i
    // initialization of the SequenceSizes
    for (unsigned int i = 0; i < Sequences.size(); i++)
        SequenceSizes.push_back((int)floor((Sequences[i].size()) / k));
    vector<string> allKmers; // The set of all different Kmers
    bool matched = false; // a boolean for the "Is this Kmer already in my set?"-Chec
    int index; // a integer, which is index for the k-mers per sequence
    /*
     * here we go over the i Sequence and look at the index's Kmer and 
     * push it into our set, when it is not already in.
     */
    for (unsigned int i = 0; i < Sequences.size(); i++) {
        index = 0;
        while (index < SequenceSizes[i]) {
            // comparing all k-mers in our set with the picked one
            for (unsigned int j = 0; j < allKmers.size(); j++) {
                if (allKmers[j] == Sequences[i].substr(index * k, k)) {
                    matched = true;
                    break;
                }
            }
            // pushing a new Kmer
            if (!matched)
                allKmers.push_back(Sequences[i].substr(index * k, k));
            matched = false;
            index += 1;
        }
    }
    return allKmers;
}

GraphRenderer::GraphRenderer(){}

void GraphRenderer::drawRectangle(sf::RenderWindow& window, int i, int j, sf::Color col, string kmer,
 sf::Font font, uint size){
	
	sf::RectangleShape rectangle;
	rectangle.setSize(sf::Vector2f(size, size/2));
	rectangle.setFillColor(col);
	rectangle.setPosition(size*0.2+(size*1.8)*j, size*0.2+((size/2)*1.8)*i);
	window.draw(rectangle);
    if(rectangles.size()!=i+1) {
        vector<sf::RectangleShape> fill;
        rectangles.push_back(fill);
	cout <<"hello2" <<endl;
    }
    //rectangles[i].push_back(rectangle);
	
	
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
	
	sf::Font font;
    
    // get Graph information for the Kmerlist and Colorlist
    int k = g.getK(); // integer with size of Kmer
    vector<string> Sequences = g.getStringListSequence(); // vector with strings which stand for Sequences

    // calculation of the different Kmers
    vector<string> Kmers = giveKmers(Sequences, k); // vector of strings which stand for Kmers

    // initialize the colorlist
    colorlist colorExample(Kmers.size());

    // initialize the colormap
    vector<sf::Color> colors = colorExample.giveList(); // vector of different colors
    colormap mapExample(Kmers, colors);

	//get the edges and nodes 
	vector<Node>& nodeList=g.getNodeList();	
	//Visit every node in the nodelist	
	cout <<nodeList.size() <<endl;
	for(uint index = 0; index<nodeList.size(); index++){
			cout <<"hello" <<endl;
		    drawRectangle(window, nodeList.at(index).i, nodeList.at(index).j, mapExample.Map(nodeList.at(index).kmer), 
			    nodeList.at(index).kmer, font, size);
		    if(index != nodeList.size()-1 && nodeList.at(index).i == nodeList.at(index+1).i){
		    drawLine(window, nodeList.at(index).i, nodeList.at(index).j , size);
		    }
	}
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

void GraphRenderer::highlightRectangle(Node& node, sf::Color color, sf::RenderWindow& window, uint size){
	rectangles.at(node.i).at(node.j).setOutlineColor(color);
	rectangles.at(node.i).at(node.j).setOutlineThickness(5);
	rectangles.at(node.i).at(node.j).setFillColor(sf::Color::Transparent);
    /*sf::RectangleShape rectangle;
	rectangle.setSize(sf::Vector2f(size, size/2));
	rectangle.setFillColor(sf::Color::Transparent);
	rectangle.setOutlineColor(color);
	rectangle.setOutlineThickness(5);
	rectangle.setPosition(size*0.2+(size*1.8)*node.j, size*0.2+((size/2)*1.8)*node.i);*/
	window.draw(rectangles.at(node.i).at(node.j));
}
