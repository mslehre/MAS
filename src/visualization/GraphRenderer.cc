#include "GraphRenderer.h"

using namespace std;

//This method is used to make a list of Kmers, where all Kmers are just once in
vector<string> giveKmers(vector<Node>& nodeList) {
    vector<string> allKmers; // The set of all different Kmers
    bool elementOf;
    //go through all nodes
    for (uint i = 0; i<nodeList.size(); i++) {
        elementOf = false;
        //go through all nodes we discovered already to check if they are in the list
        for (uint j = 0; j < i; j++) {
            if(nodeList.at(i).kmer == nodeList.at(j).kmer){
                elementOf = true;
                break;            
            }
        }
        //push the nodes who aren't in yet
        if(!elementOf) {
            allKmers.push_back(nodeList.at(i).kmer);
        }
    }
    return allKmers;
}

//Method for troubleshooting bad arguments
void printHelp(){
    cout << "\t Call skript with:\t./visualization [fasta file] [k] \n" << endl;
    cout << "\t Example: ./visualization sequence.fa 3\n" << endl;
    cout << "\t fasta file: Must be a file with the ending .fa" << endl;
    cout << "\t\t fasta files are there to save the information of multiple sequences.\n" << endl;
    cout << "\t k: Must be an integer greater than zero." << endl;
    cout << "\t\t k is the length of the Kmers we observe.\n" << endl;
}

//Method for rendering the actual window view with its components
void GraphRenderer::render(sf::RenderWindow& window) {
    //update window view, if changed in class
    if (actualView.getCenter() != window.getView().getCenter())
        window.setView(actualView);
    //adjust window view, if size of window was changed
    if (window.getSize().x != window.getView().getSize().x || window.getSize().y != window.getView().getSize().y) {
        sf::Vector2f wSize(window.getSize().x, window.getSize().y);
        sf::Vector2f vSize(window.getView().getSize().x, window.getView().getSize().y);
        sf::Vector2f newCenter = window.getView().getCenter();
        sf::Vector2f temp = wSize - vSize;
        float vec = 0.5;
        temp = temp * vec;
        newCenter = newCenter + temp;
        window.setView(sf::View(newCenter, wSize));
    }
    //reset window
  	window.clear(sf::Color::White);
    drawShape(window);
    drawText(window);
}

//Method which catches all events of the window
void GraphRenderer::eventHandler(sf::Event event, sf::RenderWindow& window, vector<Node>& nodeList) {
    //Move the view of the window
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
    //Get hovercoords of the window
    sf::Vector2i posOfMouse1(event.mouseMove.x, event.mouseMove.y);
    auto movePos = window.mapPixelToCoords(posOfMouse1);
    //Now check what gets hovered
    if (event.type == sf::Event::EventType::MouseMoved) {
        //highlight the hovered Node
        if (!nodeHovered && isPositionNode(movePos)) {
            hoverNode(movePos);
        //remove the highlight of the Node
        } else if (nodeHovered && !isPositionNode(movePos)) {
            deHoverNode();
        }
        //highlight a hovered edge, if possible
        if (nodeClicked && !edgeHovered && isPositionEdge(movePos)) {
            hoverEdge(movePos);
        //remove this highlight
        } else if (nodeClicked && edgeHovered && !isPositionEdge(movePos)) {
            deHoverEdge();
        }
    }
    //Get clickcoords of the window
    sf::Vector2i posOfMouse2(event.mouseButton.x, event.mouseButton.y);
    auto clickPos = window.mapPixelToCoords(posOfMouse2);
    //Now check what gets clicked
    if (event.type == sf::Event::EventType::MouseButtonPressed) {
        //select the Node you hovered
        if (event.mouseButton.button == sf::Mouse::Left && nodeHovered && !nodeClicked) {
            clickNode();
            showEdges(nodeList, clickPos);
        //remove the selected Node
        } else if (event.mouseButton.button == sf::Mouse::Right && nodeClicked) {
            deClickNode(clickPos);
        }
        //select a Edge you hovered
        if (event.mouseButton.button == sf::Mouse::Left && nodeClicked && edgeHovered)
            selectEdge(clickPos);
    }

}

//Method which will set the move speed in terms of Computer speed with an upper Bound
void GraphRenderer::update(float delta) {
    if (delta > moveConstant)
        moveConstant = delta * 10000;
}

GraphRenderer::GraphRenderer() {
}

GraphRenderer::GraphRenderer(sf::RenderWindow& window, vector<Node>& nodeList, vector<Edge>& edgeList, int sizeConst) {
    maxNodesPerRow = 0;
    maxSequences = 0;
    for (uint i = 0; i < nodeList.size(); i++) {
        if (maxNodesPerRow < nodeList.at(i).j)
            maxNodesPerRow = nodeList.at(i).j;
        if (maxSequences < nodeList.at(i).i)
            maxSequences = nodeList.at(i).i;
    }
    direction.push_back(0);
    direction.push_back(0);
    sizeConstant = sizeConst;
    state place(edgeList);
    gameState = place;
    nodeHovered = false;
    nodeClicked = false;
    edgeHovered = false;
    defaultView = window.getDefaultView();
    actualView = defaultView;
    initShapes(nodeList);
    drawShape(window);
    drawText(window);
}

void GraphRenderer::moveWindow(int dir) {
    switch (dir) {
        case 0:
            if (direction.at(1) + moveConstant <= sizeConstant * 0.9 + (sizeConstant * 1.5) * maxSequences) {
                actualView.move(0, moveConstant);
                direction.at(1) += moveConstant;
            }
            break;
        case 1:
            if (direction.at(0) > 0) {
                actualView.move(- moveConstant, 0);
                direction.at(0) -= moveConstant;
            }            
            break;
        case 2:
            if (direction.at(0) + moveConstant <= sizeConstant * 1.4 + (sizeConstant * 1.8) * maxNodesPerRow) {
                actualView.move(moveConstant, 0);
                direction.at(0) += moveConstant;
            }
            break;
        case 3:
            if (direction.at(1) > 0) {
                actualView.move(0,- moveConstant);
                direction.at(1) -= moveConstant;
            }
            break;
        case 4:
            actualView = defaultView;
            selectedEdges.clear();
            for (uint i = 0; i < gameState.edges.size(); i++) {
                gameState.selectedSubset.at(i) = false;
                gameState.selectable.at(i) = true;
            }   
            direction.at(0) = 0;
            direction.at(1) = 0;
            break;
    }
}


void GraphRenderer::drawText(sf::RenderWindow& window) {
    int size_text = txt.size();  
    sf::Text text;
    sf::Font font;
	if (!font.loadFromFile("Amiko-Regular.ttf"))
		std::cout << "Can't find the font file" << std::endl;
    for (int i = 0; i < size_text; i++) {
        text.setFont(font);
	    text.setColor(txt[i].col);
	    text.setPosition(txt[i].pos[0], txt[i].pos[1]);
	    text.setString(txt[i].kmer);
	    text.setCharacterSize(txt[i].charSize);
        window.draw(text);
    }
}

void GraphRenderer::drawShape(sf::RenderWindow& window) {
    int size_Rect = rects.size();
    int size_seq;
    int size_Arrow = arrows.size();
    int size_tempArr = consistentEdges.size();
    int size_arrowList = selectedEdges.size();

    for (int i = 0; i < size_Arrow; i++) {
        window.draw(arrows.at(i).line);
        window.draw(arrows.at(i).triangle);
    }
    for (int i = 0; i < size_Rect; i++) {
        size_seq = rects.at(i).size();
        for (int j = 0; j < size_seq; j++)
            window.draw(rects.at(i).at(j));
    }
    for (int i = 0; i < size_tempArr; i++)
        consistentEdges.at(i).Draw(window);
    for (int i = 0; i < size_arrowList; i++)
        selectedEdges.at(i).Draw(window);
}


void GraphRenderer::initShapes(vector<Node>& nodeList) {
    
    //initialize the shift of the view
    direction.push_back(0);
    direction.push_back(0);

    //Get all nodes we need
    uint size_nodes = nodeList.size();

    //Initialize colormap
    vector<string> Kmers = giveKmers(nodeList);
    colorlist colorExample(Kmers.size());
    vector<sf::Color> colors = colorExample.giveList();
    colormap mapExample(Kmers, colors);

    //Placeholder for readablity OF THE NODES
    uint i;
    uint j;
    //Placeholder for the Text
    TextProps tx;
	tx.col = sf::Color::Black;
    //Placeholder for the Shapes
    SimpleArrow arr;

    sf::RectangleShape rect;
	rect.setSize(sf::Vector2f(sizeConstant, sizeConstant / 2));

    sf::CircleShape tri;
    tri.setRadius(sizeConstant * 0.1);
    tri.setPointCount(3);
    tri.setFillColor(sf::Color::Black);
    tri.setOutlineThickness(2.f);
    tri.setOutlineColor(sf::Color::Black);
    tri.setRotation(90.f);

    sf::RectangleShape line;
    line.setSize(sf::Vector2f(sizeConstant, 0));
	line.setOutlineColor(sf::Color::Black);
	line.setOutlineThickness(2);
	//calculate our Graph in visuals

	for (uint k = 0; k < size_nodes; k++){
        i = nodeList.at(k).i;
        j = nodeList.at(k).j;
	    rect.setFillColor(mapExample.Map(nodeList.at(k).kmer));
	    rect.setPosition(sizeConstant * 0.2 + (sizeConstant * 1.8) * j, sizeConstant * 0.2 + ((sizeConstant / 2) * 3) * i);
        while (rects.size() != i + 1) {
            vector<sf::RectangleShape> fill;
            rects.push_back(fill);
        }
        rects.at(i).push_back(rect);
	    tx.pos.push_back(sizeConstant * 0.2 + (sizeConstant * 1.8) * j + sizeConstant * 0.1);
        tx.pos.push_back(sizeConstant * 0.2 + (sizeConstant / 2) * 3 * i + (sizeConstant / 2) * 0.1);
	    tx.kmer = nodeList.at(k).kmer;
	    tx.charSize = sizeConstant * 0.25;
        txt.push_back(tx);
        tx.pos.clear();
		if (k != nodeList.size() - 1 && i == nodeList.at(k + 1).i) {
	        line.setPosition(sizeConstant * 1.2 + (sizeConstant * 1.8) * j, sizeConstant * 0.45 + (sizeConstant / 2) * 3 * i);
	        tri.setPosition(sizeConstant * 1.7 + (sizeConstant * 1.8) * j, sizeConstant * 0.35 + (sizeConstant / 2) * 3 * i);
            arr.line = line;
            arr.triangle = tri;
            arrows.push_back(arr);
		}
	}
}

void GraphRenderer::selectEdge(sf::Vector2f pos) {
    int ind = consistentEdges.at(hoveredEdgeIndex).getIndex();
    gameState.select(ind);
    FuncArrowShape fill(gameState.edges.at(ind), sizeConstant, sf::Color::Black, ind);
    selectedEdges.push_back(fill);
    consistentEdges.clear();
    nodeClicked = false;
    edgeHovered = false;
    deClickNode(pos);
}



Node* GraphRenderer::positionToNode(sf::Vector2f pos, vector<Node>& nodeList){
    uint x = (pos.x - sizeConstant * 0.2) / (sizeConstant * 1.8);
	uint y = (pos.y - sizeConstant * 0.2) / ((sizeConstant / 2) * 3);
	Node *actualNode;
	for (auto &node : nodeList) {
		if (node.i == y && node.j == x) {
			actualNode = &node;
			break;
		}
	}
	return actualNode;
}

void GraphRenderer::hoverNode(sf::Vector2f pos) {
    if (!nodeClicked) {        
        int j = (pos.x - sizeConstant * 0.2) / (sizeConstant * 1.8);
	    int i = (pos.y - sizeConstant * 0.2) / ((sizeConstant / 2) * 3);
        hoverPosition = sf::Vector2i(i, j);
        rects.at(i).at(j).setOutlineColor(sf::Color::Black);
        rects.at(i).at(j).setOutlineThickness(5);
    }
    nodeHovered = true;
}
void GraphRenderer::deHoverNode() {
    if (!nodeClicked) {
        rects.at(hoverPosition.x).at(hoverPosition.y).setOutlineColor(sf::Color::Transparent);
        rects.at(hoverPosition.x).at(hoverPosition.y).setOutlineThickness(0);
    }
    nodeHovered = false;
}

void GraphRenderer::deHoverEdge() {
    consistentEdges.at(hoveredEdgeIndex).deHoverFunc();
    edgeHovered = false;
}

void GraphRenderer::hoverEdge(sf::Vector2f pos) {
    for (uint i = 0; i < consistentEdges.size(); i++) {
        if (consistentEdges.at(i).getShape().getGlobalBounds().contains(pos)) {
            consistentEdges.at(i).hoverFunc();
            hoveredEdgeIndex = i;
            break;
        }
    }
    edgeHovered = true;
}

void GraphRenderer::clickNode() {
    colorOfHoveredNode = rects.at(hoverPosition.x).at(hoverPosition.y).getFillColor();
    rects.at(hoverPosition.x).at(hoverPosition.y).setFillColor(sf::Color(128, 128, 128));
    rects.at(hoverPosition.x).at(hoverPosition.y).setOutlineColor(sf::Color::Red);
    rects.at(hoverPosition.x).at(hoverPosition.y).setOutlineThickness(8);
    nodeClicked = true;
    
}

void GraphRenderer::deClickNode(sf::Vector2f pos) {
    rects.at(hoverPosition.x).at(hoverPosition.y).setFillColor(colorOfHoveredNode);
    rects.at(hoverPosition.x).at(hoverPosition.y).setOutlineColor(sf::Color::Transparent);
    rects.at(hoverPosition.x).at(hoverPosition.y).setOutlineThickness(0);
    consistentEdges.clear();
    nodeClicked = false;
    int j = (pos.x - sizeConstant * 0.2) / (sizeConstant * 1.8);
	int i = (pos.y - sizeConstant * 0.2) / ((sizeConstant / 2) * 3);
    hoverPosition = sf::Vector2i(i, j);
}

void GraphRenderer::showEdges(vector<Node>& nodeList, sf::Vector2f pos) {
    Node *recent = positionToNode(pos, nodeList);
    int size_Edges = gameState.edges.size();
    for (int i = 0; i < size_Edges; i++) {
        if (gameState.selectable.at(i) && recent->i == gameState.edges.at(i).first->i && recent->j == gameState.edges.at(i).first->j) {
            FuncArrowShape temp(gameState.edges[i], sizeConstant, sf::Color(200, 200, 200), i);
            consistentEdges.push_back(temp);
        }
    }
}


bool GraphRenderer::isPositionEdge(sf::Vector2f pos) {
    for (auto &arr : consistentEdges) {
        if (arr.getShape().getGlobalBounds().contains(pos))
            return true;
    }
    return false;
}


bool GraphRenderer::isPositionNode(sf::Vector2f pos) {
	uint x = (pos.x - sizeConstant * 0.2) / (sizeConstant * 1.8);
	uint y = (pos.y - sizeConstant * 0.2) / ((sizeConstant / 2) * 3);
    if(y < rects.size() && y >= 0 && x >= 0 && x < rects.at(y).size()) {
        bool s = rects.at(y).at(x).getGlobalBounds().contains(pos);
        return s;
    } else {
        return false;
    }
}
