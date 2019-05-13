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
            if(nodeList.at(i).kmer == nodeList.at(j).kmer) {
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
    enum direction {Down, Left, Right, Up, Space};
    if (event.type == sf::Event::EventType::KeyPressed) {
        if (event.key.code == sf::Keyboard::Right)
            moveWindow(Right);
        if (event.key.code == sf::Keyboard::Left)
            moveWindow(Left);
        if (event.key.code == sf::Keyboard::Up)
            moveWindow(Up);
        if (event.key.code == sf::Keyboard::Down)
            moveWindow(Down);
        if (event.key.code == sf::Keyboard::Space)
            moveWindow(Space);
    }
    //Get hovercoords of the window
    sf::Vector2i posOfMouse1(event.mouseMove.x, event.mouseMove.y);
    auto movePos = window.mapPixelToCoords(posOfMouse1);
    //Now check what gets hovered
    if (event.type == sf::Event::EventType::MouseMoved) {
        //highlight the hovered Node
        if (!nodeHovered && !nodeClicked && isPositionNode(movePos)) {
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
            clickNode(clickPos);
            showEdges(nodeList, clickPos);
        //remove the selected Node
        } else if (event.mouseButton.button == sf::Mouse::Right && nodeClicked) {
            deClickNode();
        }
        //select a Edge you hovered
        if (event.mouseButton.button == sf::Mouse::Left && nodeClicked && edgeHovered)
            selectEdge();
    }
}

//Method which will set the move speed in terms of Computer speed with an upper Bound
void GraphRenderer::update(float delta) {
    if (delta > moveConstant)
        moveConstant = delta * 10000;
}

//Default Constructor
GraphRenderer::GraphRenderer() {
}

//Complete Constructor
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

//Method which will move the window in a choosed direction or resets it
void GraphRenderer::moveWindow(int dir) {
    switch (dir) {
        case 0: //to the down
            if (direction.at(1) + moveConstant <= sizeConstant * (0.9 + 1.5 * maxSequences)) {
                actualView.move(0, moveConstant);
                direction.at(1) += moveConstant;
            }
            break;
        case 1: //to the left
            if (direction.at(0) > 0) {
                actualView.move(- moveConstant, 0);
                direction.at(0) -= moveConstant;
            }
            break;
        case 2: //to the right
            if (direction.at(0) + moveConstant <= sizeConstant * (1.4 + 1.8 * maxNodesPerRow)) {
                actualView.move(moveConstant, 0);
                direction.at(0) += moveConstant;
            }
            break;
        case 3: //to the up
            if (direction.at(1) > 0) {
                actualView.move(0,- moveConstant);
                direction.at(1) -= moveConstant;
            }
            break;
        case 4: //resets all
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

//This Method draws the text
void GraphRenderer::drawText(sf::RenderWindow& window) {
    int size_text = txt.size();
    sf::Text text;
    sf::Font font;
    //load font out of file
    if (!font.loadFromFile("Amiko-Regular.ttf"))
        std::cout << "Can't find the font file" << std::endl;
    for (int i = 0; i < size_text; i++) {
        text.setFont(font);
        text.setFillColor(txt[i].col);
        text.setPosition(txt[i].pos[0], txt[i].pos[1]);
        text.setString(txt[i].kmer);
        text.setCharacterSize(txt[i].charSize);
        window.draw(text);
    }
}

//This Method draws all shapes
void GraphRenderer::drawShape(sf::RenderWindow& window) {
    int size_Rect = rects.size();
    int size_seq;
    int size_rowArrows = rowArrows.size();
    int size_tempArr = consistentEdges.size();
    int size_arrowList = selectedEdges.size();
    //iterate through vectors to draw all
    for (int i = 0; i < size_rowArrows; i++) {
        rowArrows.at(i).Draw(window);
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

//This method initialize the shapes by the properties of nodeList
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
    //initialize rectangle
    sf::RectangleShape rect;
    rect.setSize(sf::Vector2f(sizeConstant, sizeConstant / 2));
    //Iterate to declare all shapes we need in the beginning
    for (uint k = 0; k < size_nodes; k++){
        i = nodeList.at(k).i;
        j = nodeList.at(k).j;
        rect.setFillColor(mapExample.Map(nodeList.at(k).kmer));
        rect.setPosition(sizeConstant * (0.2 + 1.8 * j), sizeConstant * (0.2 + 1.5 * i));
        while (rects.size() != i + 1) {
            vector<sf::RectangleShape> fill;
            rects.push_back(fill);
        }
        rects.at(i).push_back(rect);
        tx.pos.push_back(sizeConstant * (0.3 + 1.8 * j));
        tx.pos.push_back(sizeConstant * (0.25 + 1.5 * i));
        tx.kmer = nodeList.at(k).kmer;
        tx.charSize = sizeConstant * 0.25;
        txt.push_back(tx);
        tx.pos.clear();
        if (k != nodeList.size() - 1 && i == nodeList.at(k + 1).i) {
            sf::Vector2f start(sizeConstant * (1.2 + 1.8 * j), sizeConstant * (0.45 + 1.5 * i));
            sf::Vector2f end(sizeConstant * (1.85 + 1.8 * j), sizeConstant * (0.45 + 1.5 * i));
            ArrowShape placeholder(start, end, sizeConstant, sf::Color::Black);
            rowArrows.push_back(placeholder);
        }
    }
}

//this method will highlight a node which we hover
void GraphRenderer::hoverNode(sf::Vector2f pos) {
    sf::Vector2i temp = positionToCoords(pos);
    hoverPosition = temp;
    rects.at(temp.y).at(temp.x).setOutlineColor(sf::Color::Black);
    rects.at(temp.y).at(temp.x).setOutlineThickness(5);
    nodeHovered = true;
}

//this method is removing the highlight of the hover function
void GraphRenderer::deHoverNode() {
    if (!nodeClicked) {
        rects.at(hoverPosition.y).at(hoverPosition.x).setOutlineColor(sf::Color::Transparent);
        rects.at(hoverPosition.y).at(hoverPosition.x).setOutlineThickness(0);
    }
    nodeHovered = false;
}

//this function catches the click on a node and select it
void GraphRenderer::clickNode(sf::Vector2f pos) {
    sf::Vector2i temp = positionToCoords(pos);
    clickPosition = temp;
    colorOfClickedNode = rects.at(clickPosition.y).at(clickPosition.x).getFillColor();
    rects.at(clickPosition.y).at(clickPosition.x).setFillColor(sf::Color(128, 128, 128));
    rects.at(clickPosition.y).at(clickPosition.x).setOutlineColor(sf::Color::Red);
    rects.at(clickPosition.y).at(clickPosition.x).setOutlineThickness(8);
    nodeClicked = true;
}

//this function remove the selected node
void GraphRenderer::deClickNode() {
    rects.at(clickPosition.y).at(clickPosition.x).setFillColor(colorOfClickedNode);
    rects.at(clickPosition.y).at(clickPosition.x).setOutlineColor(sf::Color::Transparent);
    rects.at(clickPosition.y).at(clickPosition.x).setOutlineThickness(0);
    consistentEdges.clear();
    nodeClicked = false;
}

//this method will highlight a edge, when we clicked a node and hover over a edge
void GraphRenderer::hoverEdge(sf::Vector2f pos) {
    for (uint i = 0; i < consistentEdges.size(); i++) {
        //is our mousepos in the edgefront?
        if (consistentEdges.at(i).getShape().getGlobalBounds().contains(pos)) {
            consistentEdges.at(i).hoverFunc();
            hoveredEdgeIndex = i;
            break;
        }
    }
    edgeHovered = true;
}

//This method is removing the edge highlight
void GraphRenderer::deHoverEdge() {
    consistentEdges.at(hoveredEdgeIndex).deHoverFunc();
    edgeHovered = false;
}

//This function shows the consistent edges
void GraphRenderer::showEdges(vector<Node>& nodeList, sf::Vector2f pos) {
    Node *recent = positionToNode(pos, nodeList);
    int size_Edges = gameState.edges.size();
    for (int i = 0; i < size_Edges; i++) {
        //just look at all edges that come from the selected node
        if (gameState.selectable.at(i) && recent->i == gameState.edges.at(i).first->i && recent->j == gameState.edges.at(i).first->j) {
            FuncArrowShape temp(gameState.edges[i], sizeConstant, sf::Color(200, 200, 200), i);
            consistentEdges.push_back(temp);
        }
    }
}

//This method select an edge which got hovered
void GraphRenderer::selectEdge() {
    int ind = consistentEdges.at(hoveredEdgeIndex).getIndex();
    //select via state
    gameState.select(ind);
    FuncArrowShape fill(gameState.edges.at(ind), sizeConstant, sf::Color::Black, ind);
    //Save the selected edge in visuals
    selectedEdges.push_back(fill);
    consistentEdges.clear();
    nodeClicked = false;
    edgeHovered = false;
    deClickNode();
}

//Method for calculating the nearest node pos of the argument pos
sf::Vector2i GraphRenderer::positionToCoords(sf::Vector2f pos) {
    int x = (pos.x - sizeConstant * 0.2) / (sizeConstant * 1.8);
    int y = (pos.y - sizeConstant * 0.2) / (sizeConstant * 1.5);
    return sf::Vector2i(x, y);
}

//This method calculates Nodes in terms of positions
Node* GraphRenderer::positionToNode(sf::Vector2f pos, vector<Node>& nodeList) {
    sf::Vector2i temp = positionToCoords(pos);
    Node *actualNode;
    for (auto &node : nodeList) {
        if ((int)node.i == temp.y && (int)node.j == temp.x) {
            actualNode = &node;
            break;
        }
    }
    return actualNode;
}

//This method is checking that an edge is in mouseposition
bool GraphRenderer::isPositionEdge(sf::Vector2f pos) {
    for (auto &arr : consistentEdges) {
        if (arr.getShape().getGlobalBounds().contains(pos))
            return true;
    }
    return false;
}

//This method is checking that an Node is in mouseposition
bool GraphRenderer::isPositionNode(sf::Vector2f pos) {
    sf::Vector2i temp = positionToCoords(pos);
    //just look at rectangle indices which we defined
    if(temp.y < (int)rects.size() && temp.y >= 0 && temp.x >= 0 && temp.x < (int)rects.at(temp.y).size()) {
        bool s = rects.at(temp.y).at(temp.x).getGlobalBounds().contains(pos);
        return s;
    } else {
        return false;
    }
}
