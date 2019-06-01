#include "GraphRenderer.h"

using namespace std;

//This method is used to make a list of Kmers, where all Kmers are just once in
vector<string> giveKmers(vector<Node>& nodeList) {
    vector<string> allKmers; // The set of all different Kmers
    bool elementOf;
    //go through all nodes
    for (unsigned i = 0; i < nodeList.size(); i++) {
        elementOf = false;
        //go through all nodes we discovered already to check if they are in the list
        for (unsigned j = 0; j < i; j++) {
            if(nodeList.at(i).kmer == nodeList.at(j).kmer) {
                elementOf = true;
                break;
            }
        }
        //push the nodes who aren't in yet
        if(!elementOf)
            allKmers.push_back(nodeList.at(i).kmer);
    }
    return allKmers;
}

//Method for troubleshooting bad arguments
void printHelp(){
    cout << "\t Call program with:\t./visualization [fasta file] [k] \n" << endl;
    cout << "\t Example: ./visualization sequence.fa 3\n" << endl;
    cout << "\t fasta file: Must be a file with the ending .fa" << endl;
    cout << "\t\t fasta files are there to save the information of multiple sequences.\n" << endl;
    cout << "\t k: Must be an integer greater than zero." << endl;
    cout << "\t\t k is the length of the Kmers we observe.\n" << endl;
}

//Method for rendering the actual window view with its components
void GraphRenderer::render(sf::RenderWindow& window, vector<DrawNode>& Nodes, vector<Node>& nodeList) {
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
        actualView = sf::View(newCenter, wSize);
        window.setView(actualView);
    }
    //reset window
    window.clear(sf::Color::White);
    for (auto &arr : selectedEdges)
        arr.setCoordsByPos(Nodes, sizeConstant);
    setCoords(Nodes, nodeList);
    drawShape(window);
    drawText(window);
}

//Method which catches all events of the window
void GraphRenderer::eventHandler(sf::Event event, sf::RenderWindow& window, vector<Node>& nodeList, vector<DrawNode>& Nodes, state& gameState) {
    window.setView(actualView);
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
        if (!nodeHovered && !nodeClicked && isPositionNode(movePos, Nodes, nodeList)) {
            hoverNode(nodeList, Nodes, movePos);
        //remove the highlight of the Node
        } else if (nodeHovered && !isPositionNode(movePos, Nodes, nodeList)) {
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
            clickNode(nodeList, Nodes, clickPos);
            showEdges(nodeList, Nodes, clickPos, gameState);
        //remove the selected Node
        } else if (event.mouseButton.button == sf::Mouse::Right && nodeClicked) {
            deClickNode();
        }
        //select a Edge you hovered
        if (event.mouseButton.button == sf::Mouse::Left && nodeClicked && edgeHovered)
            selectEdge(nodeList, Nodes, gameState);
    }
}

void GraphRenderer::display_score(sf::RenderWindow& window, const state& gameState) {
    int x_pos = window.getView().getCenter().x - (window.getSize().x / 2);
    int y_pos = window.getView().getCenter().y - (window.getSize().y / 2);

    sf::RectangleShape rect(sf::Vector2f(window.getSize().x, 130));
    rect.setPosition(x_pos, y_pos);
  
    sf::Font font;
    if (!font.loadFromFile("Amiko-Regular.ttf"))
        std::cout << "Can't find the font file" << std::endl;

    std::string PlayerScore = "Your Score: " + std::to_string(gameState.score);
    std::string AgentScore = "Computer Score: " + std::to_string(gameState.score); // TODO: need a score from an Agent    
    sf::Text text(PlayerScore + "\n" + AgentScore, font, 45);
    text.setColor(sf::Color::Black);
    text.setPosition(x_pos + 150, y_pos);

    window.draw(rect);
    window.draw(text);
}

//Method which will set the move speed in terms of Computer speed with an upper Bound
void GraphRenderer::update(float delta) {
    moveConstant = delta * 10000;
}

void GraphRenderer::updateDrawNode(sf::RenderWindow& window, vector<Node>& nodeList, vector<DrawNode>& Nodes) {
    vector<DrawNode> newNodes = Nodes;
    vector<sf::Vector2i> nodeIndices;
    bool checked = true;
    bool computed = false;
    for (unsigned i = 0; i < selectedEdges.size(); i++) {
        nodeIndices.push_back(selectedEdges.at(i).getIndexOfArrow());
    }
    for (unsigned i = 0; i < nodeIndices.size(); i++) {
        int s = nodeIndices.at(i).x;
        int e = nodeIndices.at(i).y;
        if (newNodes.at(e).coordinate.x != newNodes.at(s).coordinate.x)
            checked = false;
    }
    unsigned index;
    float diff;
    while (!checked) {
        computed = true;
        for (unsigned i = 0; i < nodeIndices.size(); i++) {
            int s = nodeIndices.at(i).x;
            int e = nodeIndices.at(i).y;
            if (newNodes.at(s).coordinate.x > newNodes.at(e).coordinate.x) {
                index = e;
                diff = (newNodes.at(s).coordinate.x - newNodes.at(e).coordinate.x);
                while (index != newNodes.size() && newNodes.at(e).coordinate.y == newNodes.at(index).coordinate.y) {
                    newNodes.at(index).coordinate.x += diff;
                    index++;
                }
            }
            if (newNodes.at(s).coordinate.x < newNodes.at(e).coordinate.x) {
                index = s;
                diff = (newNodes.at(e).coordinate.x - newNodes.at(s).coordinate.x);
                while (index != newNodes.size() && newNodes.at(s).coordinate.y == newNodes.at(index).coordinate.y) {
                    newNodes.at(index).coordinate.x += diff;
                    index++;
                }
            }
        }
        checked = true;
        for (unsigned i = 0; i < nodeIndices.size(); i++) {
            int s = nodeIndices.at(i).x;
            int e = nodeIndices.at(i).y;
            if (newNodes.at(e).coordinate.x != newNodes.at(s).coordinate.x)
                checked = false;
        }
    }
    if (computed) {
        vector<double> ranges;
        for (unsigned i = 0; i < newNodes.size(); i++) {
            ranges.push_back((newNodes.at(i).coordinate.x - Nodes.at(i).coordinate.x) * 0.01);
        }
        for (unsigned j = 0; j < 100; j++) {
            for (unsigned i = 0; i < newNodes.size(); i++) {
                Nodes.at(i).coordinate.x += ranges.at(i);
            }
            window.clear(sf::Color::White);
            for (auto &arr : selectedEdges)
                arr.setCoordsByPos(Nodes, sizeConstant);
            setCoords(Nodes, nodeList);
            window.setView(actualView);
            drawShape(window);
            drawText(window);
            window.display();
        }
    }
    Nodes = newNodes;
}

//Default Constructor
GraphRenderer::GraphRenderer() {
}

//Complete Constructor
GraphRenderer::GraphRenderer(sf::RenderWindow& window, Graph& gr, vector<DrawNode>& Nodes) {
    vector<Node> nodeList = gr.getNodes();
    vector<Edge> edgeList = gr.getEdges();
    maxNodesPerRow = 0;
    maxSequences = 0;
    for (unsigned i = 0; i < nodeList.size(); i++) {
        if (maxNodesPerRow < nodeList.at(i).j)
            maxNodesPerRow = nodeList.at(i).j;
        if (maxSequences < nodeList.at(i).i)
            maxSequences = nodeList.at(i).i;
    }
    if (maxNodesPerRow > 50 && maxSequences > 5) {
        sizeConstant = 50 + 80.0 * (1.0 / ((maxNodesPerRow / 50.0) * (maxSequences / 5)));
    } else {
        sizeConstant = 130;
    }
    direction.push_back(0);
    direction.push_back(0);
    nodeHovered = false;
    nodeClicked = false;
    edgeHovered = false;
    defaultView = window.getDefaultView();
    actualView = defaultView;
    initShapes(Nodes, nodeList);
}

//Method which will move the window in a choosed direction or resets it
void GraphRenderer::moveWindow(int dir) {
    switch (dir) {
        case 0: //to the down
            //if (direction.at(1) + moveConstant <= sizeConstant * (0.9 + 1.5 * maxSequences)) {
                actualView.move(0, moveConstant);
                direction.at(1) += moveConstant;
            //}
            break;
        case 1: //to the left
            //if (direction.at(0) > 0) {
                actualView.move(- moveConstant, 0);
                direction.at(0) -= moveConstant;
            //}
            break;
        case 2: //to the right
            //if (direction.at(0) + moveConstant <= sizeConstant * (1.4 + 1.8 * maxNodesPerRow)) {
                actualView.move(moveConstant, 0);
                direction.at(0) += moveConstant;
            //}
            break;
        case 3: //to the up
            //if (direction.at(1) > 0) {
                actualView.move(0,- moveConstant);
                direction.at(1) -= moveConstant;
            //}
            break;
        case 4: //resets all
            actualView = defaultView;
            //selectedEdges.clear();
            //gameState.reset();
            direction.at(0) = 0;
            direction.at(1) = 0;
            break;
    }
}

//This method draws the text
void GraphRenderer::drawText(sf::RenderWindow& window) {
    unsigned int size_text = txt.size();
    sf::Text text;
    sf::Font font;
    //load font out of file
    if (!font.loadFromFile("Amiko-Regular.ttf"))
        std::cout << "Can't find the font file" << std::endl;
    for (unsigned int i = 0; i < size_text; i++) {
        text.setFont(font);
        text.setColor(txt[i].col);
        text.setPosition(txt[i].pos[0], txt[i].pos[1]);
        text.setString(txt[i].kmer);
        text.setCharacterSize(txt[i].charSize);
        window.draw(text);
    }
}

//This method draws all shapes
void GraphRenderer::drawShape(sf::RenderWindow& window) {
    unsigned int size_Rect = rects.size();
    unsigned int size_seq;
    unsigned int size_rowArrows = rowArrows.size();
    unsigned int size_tempArr = consistentEdges.size();
    unsigned int size_arrowList = selectedEdges.size();
    //iterate through vectors to draw all
    for (unsigned int i = 0; i < size_rowArrows; i++) {
        rowArrows.at(i).Draw(window);
    }
    for (unsigned int i = 0; i < size_Rect; i++) {
        size_seq = rects.at(i).size();
        for (unsigned int j = 0; j < size_seq; j++)
            window.draw(rects.at(i).at(j));
    }
    for (unsigned int i = 0; i < size_tempArr; i++)
        consistentEdges.at(i).Draw(window);
    for (unsigned int i = 0; i < size_arrowList; i++)
        selectedEdges.at(i).Draw(window);
}

void GraphRenderer::setCoords(const vector<DrawNode>& Nodes, const vector<Node>& nodeList) {
    //Get all nodes we need
    rowArrows.clear();
    unsigned size_nodes = Nodes.size();
    //Placeholder for readablity OF THE NODES
    double i;
    double j;
    int j2;
    int i2;
    double j3;
    //Iterate to declare all shapes we need in the beginning
    for (unsigned k = 0; k < size_nodes; k++){
        i = Nodes.at(k).coordinate.y;
        j = Nodes.at(k).coordinate.x;
        i2 = nodeList.at(k).i;
        j2 = nodeList.at(k).j;
        rects.at(i2).at(j2).setPosition(sizeConstant * (0.2 + 1.8 * j), sizeConstant * (0.2 + 1.5 * i));
        txt.at(k).pos.at(0) = sizeConstant * (0.3 + 1.8 * j);
        txt.at(k).pos.at(1) = sizeConstant * (0.25 + 1.5 * i);
        if (k != Nodes.size() - 1 && i == Nodes.at(k + 1).coordinate.y) {
            j3 = Nodes.at(k + 1).coordinate.x;
            sf::Vector2f start(sizeConstant * (1.2 + 1.8 * j), sizeConstant * (0.45 + 1.5 * i));
            sf::Vector2f end(sizeConstant * (0.05 + 1.8 * j3), sizeConstant * (0.45 + 1.5 * i));
            ArrowShape placeholder(start, end, sizeConstant, sf::Color::Black);
            rowArrows.push_back(placeholder);
        }
    }
}

//This method initialize the shapes by the properties of nodeList
void GraphRenderer::initShapes(const vector<DrawNode>& Nodes, const vector<Node>& nodeList) {
    //Get all nodes we need
    unsigned size_nodes = Nodes.size();
    //Placeholder for readablity OF THE NODES
    double i;
    double j;
    //Placeholder for the Text
    TextProps tx;
    tx.col = sf::Color::Black;
    //initialize rectangle
    sf::RectangleShape rect;
    rect.setSize(sf::Vector2f(sizeConstant, sizeConstant / 2));
    //Iterate to declare all shapes we need in the beginning
    for (unsigned k = 0; k < size_nodes; k++){
        i = Nodes.at(k).coordinate.y;
        j = Nodes.at(k).coordinate.x;
        rect.setFillColor(Nodes.at(k).col);
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
        if (k != Nodes.size() - 1 && i == Nodes.at(k + 1).coordinate.y) {
            sf::Vector2f start(sizeConstant * (1.2 + 1.8 * j), sizeConstant * (0.45 + 1.5 * i));
            sf::Vector2f end(sizeConstant * (1.85 + 1.8 * j), sizeConstant * (0.45 + 1.5 * i));
            ArrowShape placeholder(start, end, sizeConstant, sf::Color::Black);
            rowArrows.push_back(placeholder);
        }
    }
}

//this method will highlight a node which we hover
void GraphRenderer::hoverNode(vector<Node>& nodeList, vector<DrawNode>& Nodes, sf::Vector2f pos) {
    Node *recent = positionToNode(pos, nodeList, Nodes);
    hoverPosition = sf::Vector2i(recent->j, recent->i);
    rects.at(hoverPosition.y).at(hoverPosition.x).setOutlineColor(sf::Color::Black);
    rects.at(hoverPosition.y).at(hoverPosition.x).setOutlineThickness(5);
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
void GraphRenderer::clickNode(vector<Node>& nodeList, vector<DrawNode>& Nodes, sf::Vector2f pos) {
    Node *recent = positionToNode(pos, nodeList, Nodes);
    clickPosition = sf::Vector2i(recent->j, recent->i);
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
    for (unsigned i = 0; i < consistentEdges.size(); i++) {
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
void GraphRenderer::showEdges(vector<Node>& nodeList, vector<DrawNode>& Nodes, sf::Vector2f pos, state& gameState) {
    Node *recent = positionToNode(pos, nodeList, Nodes);
    int size_Edges = gameState.edges.size();
    for (int i = 0; i < size_Edges; i++) {
        //just look at all edges that come from the selected node
        if (gameState.selectable.at(i) && recent->i == gameState.edges.at(i).first->i && recent->j == gameState.edges.at(i).first->j) {
            Edge temp = gameState.edges.at(i);
            int start = 0;
            int end = 0;
            for (unsigned j = 0; j < nodeList.size(); j++) {
                if (temp.first->i == nodeList.at(j).i && temp.first->j == nodeList.at(j).j)
                    start = j;
                if (temp.second->i == nodeList.at(j).i && temp.second->j == nodeList.at(j).j) {
                    end = j;
                    break;
                }
            }
            FuncArrowShape tempArr(Nodes, sizeConstant, sf::Color(200, 200, 200), start, end, i);
            consistentEdges.push_back(tempArr);
        }
    }
}

//This method select an edge which got hovered
void GraphRenderer::selectEdge(vector<Node>& nodeList, vector<DrawNode>& Nodes, state& gameState) {
    int ind = consistentEdges.at(hoveredEdgeIndex).getIndex();
    gameState.select(ind);
    gameState.calculate_score();
    Edge temp = gameState.edges.at(ind);
    //select via state
    int start = 0;
    int end = 0;
    for (unsigned i = 0; i < nodeList.size(); i++) {
        if (temp.first->i == nodeList.at(i).i && temp.first->j == nodeList.at(i).j)
            start = i;
        if (temp.second->i == nodeList.at(i).i && temp.second->j == nodeList.at(i).j) {
            end = i;
            break;
        }
    }
    FuncArrowShape fill(Nodes, sizeConstant, sf::Color::Black, start, end, ind);
    //Save the selected edge in visuals
    selectedEdges.push_back(fill);
    consistentEdges.clear();
    nodeClicked = false;
    edgeHovered = false;
    deClickNode();
}

//Method for calculating the nearest node pos of the argument pos
sf::Vector2f GraphRenderer::positionToCoords(sf::Vector2f pos) {
    int x = floor((pos.x - sizeConstant * 0.2) / (sizeConstant * 1.8));
    int y = floor((pos.y - sizeConstant * 0.2) / (sizeConstant * 1.5));
    return sf::Vector2f(x, y);
}

//This method calculates Nodes in terms of positions
Node* GraphRenderer::positionToNode(sf::Vector2f pos, vector<Node>& nodeList, vector<DrawNode>& Nodes) {
    sf::Vector2f temp = positionToCoords(pos);
    Node *actualNode = nullptr;
    for (unsigned i = 0; i < nodeList.size(); i++) {
        if ((int)Nodes.at(i).coordinate.y == temp.y && (int)Nodes.at(i).coordinate.x == temp.x) {
            actualNode = &nodeList.at(i);
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
bool GraphRenderer::isPositionNode(sf::Vector2f pos, vector<DrawNode>& Nodes, vector<Node>& nodeList) {
    sf::Vector2f temp = positionToCoords(pos);
    //just look at rectangle indices which we defined
    for (unsigned i = 0; i < Nodes.size(); i++) {
        if (Nodes.at(i).coordinate.y == temp.y && Nodes.at(i).coordinate.x == temp.x) {
            bool s = rects.at(nodeList.at(i).i).at(nodeList.at(i).j).getGlobalBounds().contains(pos);
            return s;
        }
    }
    return false;
} //&& temp.x >= positionToCoords(rects.at(temp.y).at(0).getOrigin()).x && temp.x < positionToCoords(rects.at(temp.y).back().getOrigin()).x)
