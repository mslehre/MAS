#include "GraphRenderer.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "ArrowShape.h"
#include <cmath>
using namespace std;

//ignore this, this is just a help method, which get solved later
vector<string> giveKmers(vector<Node>& Sequences) {
    vector<string> allKmers; // The set of all different Kmers
    int index;
    for (uint i = 0; i<Sequences.size(); i++) {
        index = 0;
        for (uint j = 0; j<i; j++) {
            if(Sequences.at(i).kmer == Sequences.at(j).kmer){
                index = 1;
                break;            
            }
        }
        if(index == 0) {
            allKmers.push_back(Sequences.at(i).kmer);
        }
    }
    return allKmers;
}

GraphRenderer::GraphRenderer() {
}

GraphRenderer::GraphRenderer(sf::RenderWindow& window, vector<Node>& nodeList, int s) {
    size = s;
    initShapes(nodeList);
    drawShape(window);
    drawText(window);
}

void GraphRenderer::moveWindow(int dir, sf::RenderWindow& window) {
    bild = window.getView();
    switch (dir) {
        case 0:
            bild.move(0,10);
            window.setView(bild);
	        window.clear(sf::Color::White);
            direction.at(1) += 10;
            break;
        case 1:
            bild.move(-10,0);
            window.setView(bild);
	        window.clear(sf::Color::White);
            direction.at(0) += -10;
            break;
        case 2:
            bild.move(10,0);
            window.setView(bild);
	        window.clear(sf::Color::White);
            direction.at(0) += 10;
            break;
        case 3:    
            bild.move(0,-10);
            window.setView(bild);
	        window.clear(sf::Color::White);
            direction.at(1) += -10;
            break;
        case 4:
            bild = window.getDefaultView();
            window.setView(bild);
	        window.clear(sf::Color::White);
            direction.at(0) = 0;
            direction.at(1) = 0;
            break;
    }
    drawShape(window);
    drawText(window);
}

void GraphRenderer::drawText(sf::RenderWindow& window) {
    int size_text = txt.size();  
    sf::Text text;
    sf::Font font;
	if(!font.loadFromFile("Amiko-Regular.ttf")){
		std::cout <<"Can't find the font file" << std::endl;
    }
    for (int i = 0; i < size_text; i++) {
        text.setFont(font);
	    text.setColor(txt[i].col);
	    text.setPosition(txt[i].pos[0],txt[i].pos[1]);
	    text.setString(txt[i].kmer);
	    text.setCharacterSize(txt[i].charSize);
        window.draw(text);
    }
}

void GraphRenderer::drawShape(sf::RenderWindow& window) {
    cout << "LADEN!" << endl;
    int size_Rect = rects.size();
    int size_Arrow = arrows.size();
    int size_Arrow2 = arrows2.size();

    cout << "LADEN!" << endl;
    for (int i = 0; i < size_Arrow; i++) {
        window.draw(arrows.at(i).line);
        window.draw(arrows.at(i).triangle);
    }
    for (int i = 0; i < size_Arrow2; i++) {
        arrows2.at(i).Draw(window);
    }
    for (int i = 0; i < size_Rect; i++) {
        window.draw(rects.at(i));
    }
}


void GraphRenderer::initShapes(vector<Node>& nodeList) {
    
    //initialize the shift of the view
    direction.push_back(0);
    direction.push_back(0);

    //Get k
    int k = nodeList.at(2).kmer.size();
    //Get all nodes we need
    int size_nodes = nodeList.size(); 
    int size_adjnodes;
    Edge place;

    //Initialize colormap
    vector<string> Kmers = giveKmers(nodeList);
    colorlist colorExample(Kmers.size());
    vector<sf::Color> colors = colorExample.giveList();
    colormap mapExample(Kmers, colors);

    //Placeholder for readablity OF THE NODES
    int i;
    int j;
    //Placeholder for the Text
    TextProps tx;
	tx.col = sf::Color::Black;
    //Placeholder for the Shapes
    SimpleArrow arr;

    sf::RectangleShape rect;
	rect.setSize(sf::Vector2f(size, size/2));

    sf::CircleShape tri;
    tri.setRadius(size*0.1);
    tri.setPointCount(3);
    tri.setFillColor(sf::Color::Cyan);
    tri.setOutlineThickness(2.f);
    tri.setOutlineColor(sf::Color::Black);
    tri.setRotation(90.f);

    sf::RectangleShape line;
    line.setSize(sf::Vector2f(size, 0));
	line.setOutlineColor(sf::Color::Black);
	line.setOutlineThickness(2);
	//calculate our Graph in visuals

	for(int k = 0; k<size_nodes; k++){
        i = nodeList.at(k).i;
        j = nodeList.at(k).j;
	    rect.setFillColor(mapExample.Map(nodeList.at(k).kmer));
	    rect.setPosition(size*0.2+(size*1.8)*j, size*0.2+((size/2)*5)*i);
        rects.push_back(rect);
	    tx.pos.push_back(size*0.2+(size*1.8)*j+size*0.1);
        tx.pos.push_back(size*0.2+(size/2)*5*i+(size/2)*0.1);
	    tx.kmer = nodeList.at(k).kmer;
	    tx.charSize = size*0.25;
        txt.push_back(tx);
        tx.pos.clear();
		if(k!=nodeList.size()-1 && i==nodeList.at(k+1).i){
	        line.setPosition(size*1.2+(size*1.8)*j, size*0.45+(size/2)*5*i);
	        tri.setPosition(size*1.7 +(size*1.8)*j, size*0.35+(size/2)*5*i);
            arr.line = line;
            arr.triangle = tri;
            arrows.push_back(arr);
		}
        size_adjnodes = nodeList.at(k).adjNodes.size();
        for(int l = 0; l < size_adjnodes; l++){
            place.first = nodeList.at(k);
            place.second = nodeList.at(k).adjNodes.at(l);
            if (place.first.i == place.second.i - 1) {
                ArrowShape hold(place, size);
                arrows2.push_back(hold);
            }
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
