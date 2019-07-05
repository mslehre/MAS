#include "GraphRenderer.h"

using namespace std;

bool myfunction(float i, float j) { 
    return (i < j);
}

//Method for troubleshooting bad arguments
void printHelp() {
    cout << "\t Call program with:\t./visualization [fasta file] [k] \n" << endl;
    cout << "\t Example: ./visualization sequence.fa 3\n" << endl;
    cout << "\t fasta file: Must be a file with the ending .fa" << endl;
    cout << "\t\t fasta files are there to save the information of multiple sequences.\n" << endl;
    cout << "\t k: Must be an integer greater than zero." << endl;
    cout << "\t\t k is the length of the Kmers we observe.\n" << endl;
}

//Method for rendering the actual window view with its components
void GraphRenderer::render(sf::RenderWindow& window, Gamemaster& gamemaster, vector<Node>& nodeList) {
    //update window view, if changed in class
    if (actualView.getCenter() != window.getView().getCenter())
        window.setView(actualView);
    //adjust window view, if size of window was changed
    if (window.getSize().x != window.getView().getSize().x || window.getSize().y != window.getView().getSize().y) {
        sf::Vector2f wSize(window.getSize().x, window.getSize().y);
        sf::Vector2f vSize(window.getView().getSize().x, window.getView().getSize().y);
        sf::Vector2f newCenter = window.getView().getCenter();
        sf::Vector2f temp = wSize - vSize;
        temp *= (float)0.5;
        newCenter += temp;
        actualView = sf::View(newCenter, wSize);
        window.setView(actualView);
    }
    //reset window
    for (auto &arr : selectedEdges)
        arr.setCoordsByPos(gamemaster.GameNodes, sizeConstant, offset);
    setCoords(gamemaster.GameNodes, nodeList);
    drawShape(window, nodeList);
    drawText(window);
    display_score(window, gamemaster.GameState);
    scroll.draw(window, actualView, direction);
}

//Method which catches all events of the window
void GraphRenderer::eventHandler(const sf::Event event, sf::RenderWindow& window, vector<Node>& nodeList, 
                                 vector<DrawNode>& Nodes, state& gameState, const sf::Vector2f& mouse_pos) {
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

    //Now check what gets hovered
    if (event.type == sf::Event::EventType::MouseMoved) {
        //highlight the hovered Node
        if (!nodeHovered && !nodeClicked && isPositionNode(mouse_pos, Nodes, nodeList)) {
            hoverNode(nodeList, Nodes, mouse_pos);
        //remove the highlight of the Node
        } else if (nodeHovered && !isPositionNode(mouse_pos, Nodes, nodeList)) {
            deHoverNode();
        }
        //highlight a hovered edge, if possible
        if (nodeClicked && !edgeHovered && isPositionEdge(mouse_pos)) {
            hoverEdge(mouse_pos);
        //remove this highlight
        } else if (nodeClicked && edgeHovered && !isPositionEdge(mouse_pos)) {
            deHoverEdge();
        }
    }

    //Now check what gets clicked
    if (event.type == sf::Event::EventType::MouseButtonPressed) {
        //select the Node you hovered
        if (event.mouseButton.button == sf::Mouse::Left && nodeHovered && !nodeClicked) {
            clickNode(nodeList, Nodes, mouse_pos);
            showEdges(nodeList, Nodes, mouse_pos, gameState);
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
    rect.setFillColor(sf::Color(230, 230, 230));
    rect.setOutlineColor(sf::Color(100, 100, 100));
    rect.setOutlineThickness(2);
    rect.setPosition(x_pos, y_pos);
  
    sf::Font font;
    if (!font.loadFromFile("Amiko-Regular.ttf"))
        std::cout << "Can't find the font file" << std::endl;

    std::string PlayerScore = "Your Score: " + std::to_string(gameState.score);
    std::string AgentScore = "Computer Score: " + (std::string)"?"; // TODO: need a score from an Agent    
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

void GraphRenderer::updateDrawNode(sf::RenderWindow& window, vector<Node>& nodeList, vector<DrawNode>& Nodes, 
                                   const state& GameState, Button& menuButton) {
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
                arr.setCoordsByPos(Nodes, sizeConstant, offset);
            setCoords(Nodes, nodeList);
            window.setView(actualView);
            drawShape(window, nodeList);
            drawText(window);
            display_score(window, GameState);
            window.draw(menuButton.get_Button_Sprite());
            window.display();
        }
        updateBoundaries(newNodes);
        updateChunks(newNodes);
        scroll.setBounds(sf::Vector2f(0, sizeConstant * (1.5 + 1.8 * boundary.at(1))), sf::Vector2f(0, sizeConstant * (1 + 1.5 * boundary.at(3)) + 130));
    }
    Nodes = newNodes;
}

void GraphRenderer::updateChunks(const vector<DrawNode>& Nodes) {
    RendHelper.indOfNodes.clear();
    RendHelper.indOfArrows.clear();
    RendHelper.xBound = sf::Vector2i(boundary.at(0) - 6, boundary.at(1) + 6);
    RendHelper.yBound = sf::Vector2i(boundary.at(2) - 6, boundary.at(3) + 6);
    int l = 0;
    for (int i = RendHelper.yBound.x; i <= RendHelper.yBound.y; i++) {
        vector<int> temp;
        vector<int> tempArrows;
        bool lined = false;
        for (int j = RendHelper.xBound.x; j <= RendHelper.xBound.y; j++) {
            if (l < Nodes.size() && (lined || Nodes.at(l).coordinate.y == i)) {
                lined = true;
                if (l < Nodes.size() && j == Nodes.at(l).coordinate.x) {
                    tempArrows.push_back(l);
                    temp.push_back(l);
                    l++;
                } else if (l < Nodes.size() && j < Nodes.at(l).coordinate.x) {
                    int low = Nodes.at(l).coordinate.x - j;
                    for (int k = 0; k < low; k++) {
                        tempArrows.push_back(l);
                        temp.push_back(-1);
                        j++;
                    }
                    j -= 1;
                } else if (l >= Nodes.size() || j > Nodes.at(l).coordinate.x) {
                    int low = RendHelper.xBound.y - j;
                    for (int k = 0; k <= low; k++) {
                        tempArrows.push_back(l);
                        temp.push_back(-1);
                        j++;
                    }
                }
            } else {
                int low = RendHelper.xBound.y - j;
                for (int k = 0; k <= low; k++) {
                    tempArrows.push_back(0);
                    temp.push_back(-1);
                    j++;
                }
            }
        }
        RendHelper.indOfArrows.push_back(tempArrows);
        RendHelper.indOfNodes.push_back(temp);
    }
}

void GraphRenderer::updateBoundaries(const vector<DrawNode>& Nodes) {
    boundary.clear();
    vector<float> xvalues;
    vector<float> yvalues;
    for (auto &nodes : Nodes) {
        xvalues.push_back(nodes.coordinate.x);
        yvalues.push_back(nodes.coordinate.y);
    }
    sort(xvalues.begin(), xvalues.end(), myfunction);
    sort(yvalues.begin(), yvalues.end(), myfunction);
    boundary.push_back(xvalues.front());
    boundary.push_back(xvalues.back());
    boundary.push_back(yvalues.front());
    boundary.push_back(yvalues.back());
}

//Default Constructor
GraphRenderer::GraphRenderer() {
}

//Complete Constructor
GraphRenderer::GraphRenderer(sf::RenderWindow& window, Graph& gr, vector<DrawNode>& Nodes, float xoffset) {
    offset = xoffset;
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
    updateBoundaries(Nodes);
    updateChunks(Nodes);
    nodeHovered = false;
    nodeClicked = false;
    edgeHovered = false;
    defaultView = window.getDefaultView();
    actualView = defaultView;
    initShapes(Nodes, nodeList);
    scrollbar scr(window, sf::Vector2f(0, 0), sf::Vector2f(0, sizeConstant * (1.5 + 1.8 * boundary.at(1))), sf::Vector2f(0, sizeConstant * (1 + 1.5 * boundary.at(3)) + 130), 20);
    scroll = scr;
}

//Method which will move the window in a choosed direction or resets it
void GraphRenderer::moveWindow(int dir) {
    sf::Vector2f size = actualView.getSize();
    switch (dir) {
        case 0: //to the down
            if (sizeConstant * (0.7 + 1.5 * boundary.at(3)) > direction.at(1) + size.y) {
                actualView.move(0, moveConstant);
                direction.at(1) += moveConstant;
            }
            break;
        case 1: //to the left
            if (sizeConstant * (0.2 + 1.8 * boundary.at(0)) < direction.at(0)) {
                actualView.move(- moveConstant, 0);
                direction.at(0) -= moveConstant;
            }
            break;
        case 2: //to the right
            if (sizeConstant * (1.2 + 1.8 * boundary.at(1)) > direction.at(0) + size.x) {
                actualView.move(moveConstant, 0);
                direction.at(0) += moveConstant;
            }
            break;
        case 3: //to the up
            if (sizeConstant * (0.2 + 1.5 * boundary.at(2)) < direction.at(1)) {
                actualView.move(0,- moveConstant);
                direction.at(1) -= moveConstant;
            }
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
    sf::Text text;
    sf::Font font;
    //load font out of file
    if (!font.loadFromFile("Amiko-Regular.ttf"))
        std::cout << "Can't find the font file" << std::endl;
    
    int xoff = RendHelper.xBound.x;
    int yoff = RendHelper.yBound.x;
    sf::Vector2f upperLeft = positionToCoords(sf::Vector2f(direction.at(0), direction.at(1)));
    sf::Vector2f lowerRight = positionToCoords(sf::Vector2f(direction.at(0) + actualView.getSize().x, direction.at(1) + actualView.getSize().y));
    //iterate through vectors to draw all
    for (int i = upperLeft.y; i <= lowerRight.y; i++) {
        for (int j = upperLeft.x; j <= lowerRight.x; j++) {
            if (RendHelper.indOfNodes.at(i - yoff).at(j - xoff) != -1) {
                text.setFont(font);
                text.setColor(txt[RendHelper.indOfNodes.at(i - yoff).at(j - xoff)].col);
                text.setPosition(txt[RendHelper.indOfNodes.at(i - yoff).at(j - xoff)].pos[0], txt[RendHelper.indOfNodes.at(i - yoff).at(j - xoff)].pos[1]);
                text.setString(txt[RendHelper.indOfNodes.at(i - yoff).at(j - xoff)].kmer);
                text.setCharacterSize(txt[RendHelper.indOfNodes.at(i - yoff).at(j - xoff)].charSize);
                window.draw(text);
            }
        }
    }
}

//This method draws all shapes
void GraphRenderer::drawShape(sf::RenderWindow& window, const vector<Node>& nodeList) {
    unsigned int size_tempArr = consistentEdges.size();
    unsigned int size_arrowList = selectedEdges.size();
    sf::Vector2f upperLeft = positionToCoords(sf::Vector2f(direction.at(0), direction.at(1)));
    sf::Vector2f lowerRight = positionToCoords(sf::Vector2f(direction.at(0) + actualView.getSize().x, direction.at(1) + actualView.getSize().y));
    int xoff = RendHelper.xBound.x;
    int yoff = RendHelper.yBound.x;
    //iterate through vectors to draw all
    for (int i = upperLeft.y; i <= lowerRight.y; i++) {
        for (int j = upperLeft.x; j <= lowerRight.x; j++) {
            if (RendHelper.indOfNodes.at(i - yoff).at(j - xoff) != -1) {
                unsigned x = nodeList.at(RendHelper.indOfNodes.at(i - yoff).at(j - xoff)).j;
                unsigned y = nodeList.at(RendHelper.indOfNodes.at(i - yoff).at(j - xoff)).i;
                window.draw(rects.at(y).at(x));
            }
            if (j == lowerRight.x)
                rowArrows.at(RendHelper.indOfArrows.at(i - yoff).at(j - xoff + 1)).Draw(window);
            rowArrows.at(RendHelper.indOfArrows.at(i - yoff).at(j - xoff)).Draw(window);
        }
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
    unsigned i2;
    unsigned j2;
    double j3;
    //Iterate to declare all shapes we need in the beginning
    for (unsigned k = 0; k < size_nodes; k++){
        i = Nodes.at(k).coordinate.y + offset;
        j = Nodes.at(k).coordinate.x;
        i2 = nodeList.at(k).i;
        j2 = nodeList.at(k).j;
        if (j2 == 0) {
            ArrowShape placeholder(sf::Vector2f(0, 0), sf::Vector2f(0, 0), sizeConstant, sf::Color::Transparent);
            rowArrows.push_back(placeholder);
        }
        rects.at(i2).at(j2).setPosition(sizeConstant * (0.2 + 1.8 * j), sizeConstant * (0.2 + 1.5 * i));
        txt.at(k).pos.at(0) = sizeConstant * (0.3 + 1.8 * j);
        txt.at(k).pos.at(1) = sizeConstant * (0.25 + 1.5 * i);
        if (k != Nodes.size() - 1 && i2 == nodeList.at(k + 1).i) {
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
    unsigned i2;
    unsigned j2;
    //Placeholder for the Text
    TextProps tx;
    tx.col = sf::Color::Black;
    //initialize rectangle
    sf::RectangleShape rect;
    rect.setSize(sf::Vector2f(sizeConstant, sizeConstant / 2));
    //Iterate to declare all shapes we need in the beginning
    for (unsigned k = 0; k < size_nodes; k++){
        i = Nodes.at(k).coordinate.y + offset;
        j = Nodes.at(k).coordinate.x;
        i2 = nodeList.at(k).i;
        j2 = nodeList.at(k).j;
        if (j2 == 0) {
            ArrowShape placeholder(sf::Vector2f(0, 0), sf::Vector2f(0, 0), sizeConstant, sf::Color::Transparent);
            rowArrows.push_back(placeholder);
        }
        rect.setFillColor(Nodes.at(k).col);
        rect.setPosition(sizeConstant * (0.2 + 1.8 * j), sizeConstant * (0.2 + 1.5 * i));
        while (rects.size() != i2 + 1) {
            vector<sf::RectangleShape> fill;
            rects.push_back(fill);
        }
        rects.at(i2).push_back(rect);
        tx.pos.push_back(sizeConstant * (0.3 + 1.8 * j));
        tx.pos.push_back(sizeConstant * (0.25 + 1.5 * i));
        tx.kmer = nodeList.at(k).kmer;
        tx.charSize = sizeConstant * 0.25;
        txt.push_back(tx);
        tx.pos.clear();
        if (k != Nodes.size() - 1 && i2 == nodeList.at(k + 1).i) {
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
            FuncArrowShape tempArr(Nodes, sizeConstant, sf::Color(200, 200, 200), start, end, i, offset);
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
    FuncArrowShape fill(Nodes, sizeConstant, sf::Color::Black, start, end, ind, offset);
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
    int y = floor(((pos.y - sizeConstant * 1.5 * offset) - sizeConstant * 0.2) / (sizeConstant * 1.5));
    return sf::Vector2f(x, y);
}

//This method calculates Nodes in terms of positions
Node* GraphRenderer::positionToNode(sf::Vector2f pos, vector<Node>& nodeList, vector<DrawNode>& Nodes) {
    sf::Vector2f temp = positionToCoords(pos);
    Node *actualNode = nullptr;
    for (unsigned i = 0; i < nodeList.size(); i++) {
        if (nodeList.at(i).i == temp.y && (int)Nodes.at(i).coordinate.x == temp.x) {
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
