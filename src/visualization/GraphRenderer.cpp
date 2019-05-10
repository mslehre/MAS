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


void GraphRenderer::render(sf::RenderWindow& window) {
    if (actualView.getCenter() != window.getView().getCenter()) {
        window.setView(actualView);
    }
	window.clear(sf::Color::White);
    drawShape(window);
    drawText(window);
}

void GraphRenderer::update(float delta) {
    if (delta > moveSize) {
        moveSize = delta*10000;
    }
}

void GraphRenderer::eventHandler(sf::Event event, sf::RenderWindow& window, vector<Node>& nodeList) {
    if (event.type == sf::Event::EventType::KeyPressed) {
        if (event.key.code == sf::Keyboard::Right)
	        moveWindow(2);
        if (event.key.code == sf::Keyboard::Left)
            moveWindow(1);
        if (event.key.code == sf::Keyboard::Up)
            moveWindow(3);
        if (event.key.code == sf::Keyboard::Down)
            moveWindow(0);
        if (event.key.code == sf::Keyboard::Space)
            moveWindow(4);
    }

    sf::Vector2i Pix1(event.mouseMove.x,event.mouseMove.y);
    auto movePos = window.mapPixelToCoords(Pix1);

    if (event.type == sf::Event::EventType::MouseMoved) {
        if(!hovered && isPositionNode(movePos)) {
            highlightHover(movePos);
        } else if (hovered && !isPositionNode(movePos)) {
            deHighlightHover();
        }
        if (clicked && !st_hovered && isPositionEdge(movePos)) {
            edgeHover(movePos);
        } else if (clicked && st_hovered && !isPositionEdge(movePos)) {
            deEdgeHover();
        }
    }
    
    sf::Vector2i Pix2(event.mouseButton.x,event.mouseButton.y);
    auto clickPos = window.mapPixelToCoords(Pix2);

    if (event.type == sf::Event::EventType::MouseButtonPressed) {
        
        if (event.mouseButton.button == sf::Mouse::Left && hovered && !clicked) {
            clickKmer();
            showEdges(nodeList, clickPos);
        } else if (event.mouseButton.button == sf::Mouse::Right && clicked) {
            deClickKmer(clickPos);
        }
        if (event.mouseButton.button == sf::Mouse::Left && clicked && st_hovered)
            addToGame(clickPos);
    }

}

GraphRenderer::GraphRenderer() {
}

GraphRenderer::GraphRenderer(sf::RenderWindow& window, vector<Node>& nodeList, int s) {
    size = s;
    hovered = false;
    clicked = false;
    st_hovered = false;
    defaultView = window.getDefaultView();
    actualView = defaultView;
    initShapes(nodeList);
    drawShape(window);
    drawText(window);
}

void GraphRenderer::moveWindow(int dir) {
    switch (dir) {
        case 0:
            actualView.move(0,moveSize);
            break;
        case 1:
            actualView.move(-moveSize,0);
            break;
        case 2:
            actualView.move(moveSize,0);
            break;
        case 3:    
            actualView.move(0,-moveSize);
            break;
        case 4:
            actualView = defaultView;
            arrowList.clear();
            break;
    }
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
    int size_Rect = rects.size();
    int size_seq;
    int size_Arrow = arrows.size();
    int size_tempArr = tempArr.size();
    int size_arrowList = arrowList.size();

    for (int i = 0; i < size_Arrow; i++) {
        window.draw(arrows.at(i).line);
        window.draw(arrows.at(i).triangle);
    }
    for (int i = 0; i < size_Rect; i++) {
        size_seq = rects.at(i).size();
        for (int j = 0; j < size_seq; j++) {
            window.draw(rects.at(i).at(j));
        }
    }
    for (int i = 0; i < size_tempArr; i++) {
        tempArr.at(i).Draw(window);
    }
    
    for (int i = 0; i < size_arrowList; i++) {
        arrowList.at(i).Draw(window);
    }
}


void GraphRenderer::initShapes(vector<Node>& nodeList) {
    
    //initialize the shift of the view
    direction.push_back(0);
    direction.push_back(0);

    //Get k
    int k = nodeList.at(0).kmer.size();
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
    tri.setFillColor(sf::Color::Black);
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
	    rect.setPosition(size*0.2+(size*1.8)*j, size*0.2+((size/2)*3)*i);
        while(rects.size()!=i+1) {
            vector<sf::RectangleShape> fill;
            rects.push_back(fill);
        }
        rects.at(i).push_back(rect);
	    tx.pos.push_back(size*0.2+(size*1.8)*j+size*0.1);
        tx.pos.push_back(size*0.2+(size/2)*3*i+(size/2)*0.1);
	    tx.kmer = nodeList.at(k).kmer;
	    tx.charSize = size*0.25;
        txt.push_back(tx);
        tx.pos.clear();
		if(k!=nodeList.size()-1 && i==nodeList.at(k+1).i){
	        line.setPosition(size*1.2+(size*1.8)*j, size*0.45+(size/2)*3*i);
	        tri.setPosition(size*1.7 +(size*1.8)*j, size*0.35+(size/2)*3*i);
            arr.line = line;
            arr.triangle = tri;
            arrows.push_back(arr);
		}
	}
}

void GraphRenderer::addToGame(sf::Vector2f pos) {
    Edge temp = tempArr.at(index).getEdge();
    FuncArrowShape fill(temp, size, sf::Color::Black);
    arrowList.push_back(fill);
    tempArr.clear();
    clicked = false;
    st_hovered = false;
    deClickKmer(pos);
}



Node* GraphRenderer::positionToNode(sf::Vector2f pos, vector<Node>& nodeList){
    uint x = (pos.x-size*0.2)/(size*1.8);
	uint y = (pos.y-size*0.2)/((size/2)*3);
	Node *actualNode;
	for(auto &node : nodeList) {
		if (node.i == y && node.j == x){
			actualNode = &node;
			break;
		}
	}
	return actualNode;
}

void GraphRenderer::highlightHover(sf::Vector2f pos) {
    if (!clicked) {        
        int j = (pos.x-size*0.2)/(size*1.8);
	    int i = (pos.y-size*0.2)/((size/2)*3);
        highlight = sf::Vector2i(i,j);
        rects.at(i).at(j).setOutlineColor(sf::Color::Black);
        rects.at(i).at(j).setOutlineThickness(5);
    }
    hovered = true;
}
void GraphRenderer::deHighlightHover() {
    if (!clicked) {
        rects.at(highlight.x).at(highlight.y).setOutlineColor(sf::Color::Transparent);
        rects.at(highlight.x).at(highlight.y).setOutlineThickness(0);
    }
    hovered = false;
}

void GraphRenderer::deEdgeHover() {
    tempArr.at(index).deHoverFunc();
    st_hovered = false;
}

void GraphRenderer::edgeHover(sf::Vector2f pos) {
    for(int i = 0; i<tempArr.size(); i++) {
        if (tempArr.at(i).getShape().getGlobalBounds().contains(pos)) {
            tempArr.at(i).hoverFunc();
            index = i;
            break;
        }
    }
    st_hovered = true;
}

void GraphRenderer::clickKmer() {
    highlightCol = rects.at(highlight.x).at(highlight.y).getFillColor();
    rects.at(highlight.x).at(highlight.y).setFillColor(sf::Color(128,128,128));
    rects.at(highlight.x).at(highlight.y).setOutlineColor(sf::Color::Red);
    rects.at(highlight.x).at(highlight.y).setOutlineThickness(8);
    clicked = true;
    
}

void GraphRenderer::deClickKmer(sf::Vector2f pos) {
    rects.at(highlight.x).at(highlight.y).setFillColor(highlightCol);
    rects.at(highlight.x).at(highlight.y).setOutlineColor(sf::Color::Transparent);
    rects.at(highlight.x).at(highlight.y).setOutlineThickness(0);
    tempArr.clear();
    clicked = false;
    int j = (pos.x-size*0.2)/(size*1.8);
	int i = (pos.y-size*0.2)/((size/2)*3);
    highlight = sf::Vector2i(i,j);
}

void GraphRenderer::showEdges(vector<Node>& nodeList, sf::Vector2f pos) {
    Node *recent = positionToNode(pos, nodeList);
    int size_Edges = recent->adjNodes.size();
    Edge ph;
    ph.first = recent;
    for (int i = 0; i<size_Edges; i++) {
        ph.second = recent->adjNodes.at(i);
        FuncArrowShape temp(ph, size, sf::Color(200,200,200));
        if(isArrowValid(ph)) {
            tempArr.push_back(temp);
        }
    }
}


bool GraphRenderer::isArrowValid(Edge temp) { //ERSETZEN DURCH ETWAS IM STATE
    Edge ph;
    for(auto &arr : arrowList) {
        ph = arr.getEdge();
        if (ph.first->i == temp.first->i) { //gleiche Zeile
            if (ph.second->j == temp.second->j || ph.first->j == temp.first->j) { //gleiches Ziel
                return false;
            } else if (ph.first->j < temp.first->j) { //Sich kreuzende Ziele
                if (ph.second->j > temp.second->j)
                    return false;
            } else if (ph.first->j > temp.first->j) {
                if (ph.second->j < temp.second->j)
                    return false;
            }
        }
    }
    return true;
}


bool GraphRenderer::isPositionEdge(sf::Vector2f pos) { //PASST
    for(auto &arr : tempArr) {
        if (arr.getShape().getGlobalBounds().contains(pos))
            return true;
    }
}


bool GraphRenderer::isPositionNode(sf::Vector2f pos){ //PASST
	int x = (pos.x-size*0.2)/(size*1.8);
	int y = (pos.y-size*0.2)/((size/2)*3);
    if(y<rects.size() && y>=0 && x>=0 && x<rects.at(y).size()) {
        bool s = rects.at(y).at(x).getGlobalBounds().contains(pos);
        return s;
    } else {
        return false;
    }
}
