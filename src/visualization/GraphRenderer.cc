#include "GraphRenderer.h"

using namespace std;

bool myfunction(float i, float j) { 
    return (i < j);
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
        temp *= (float)0.5;
        newCenter += temp;
        actualView = sf::View(newCenter, wSize);
        window.setView(actualView);
    }
    //reset window
    window.clear(sf::Color::White);
    for (auto &arr : selectedEdges)
        arr.setCoordsByPos(Nodes, sizeConstant, offset);
    setCoords(Nodes, nodeList);
    drawShape(window);
    drawText(window);
}

//Method which catches all events of the window
void GraphRenderer::eventHandler(const sf::Event event, sf::RenderWindow& window, vector<Node>& nodeList, 
                                 Gamemaster& gamemaster, const sf::Vector2f& mouse_pos) {
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
        if (!nodeHovered && !nodeClicked && isPositionNode(mouse_pos, gamemaster.GameNodes, nodeList)) {
            hoverNode(nodeList, gamemaster.GameNodes, mouse_pos);
        //remove the highlight of the Node
        } else if (nodeHovered && !isPositionNode(mouse_pos, gamemaster.GameNodes, nodeList)) {
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
            clickNode(nodeList, gamemaster.GameNodes, mouse_pos);
            showEdges(nodeList, gamemaster.GameNodes, mouse_pos, gamemaster.GameState);
        //remove the selected Node
        } else if (event.mouseButton.button == sf::Mouse::Right && nodeClicked) {
            deClickNode();
        }
        //select a Edge you hovered
        if (event.mouseButton.button == sf::Mouse::Left && nodeClicked && edgeHovered)
            selectEdge(nodeList, gamemaster);
    }
}

void GraphRenderer::moveWindowWithMouse(const sf::Vector2i& mouse_pixelPos) {
    sf::Vector2f size = actualView.getSize();
    float mouseMoveConstant = moveConstant / 3;
    double move = 0;
    const int edge = 50;
    unsigned int xPosdiff = size.x - mouse_pixelPos.x; 
    unsigned int yPosdiff = size.y - mouse_pixelPos.y; 
    
    if (xPosdiff > 0 && yPosdiff > 0 && mouse_pixelPos.x > 0 && mouse_pixelPos.y > 0) {        
        if (xPosdiff < edge && sizeConstant * (1.2 + 1.8 * boundary.at(1)) > direction.at(0) + size.x) { // right
            move = mouseMoveConstant / xPosdiff;
            actualView.move(move, 0);
            direction.at(0) += move;
        } else if (mouse_pixelPos.x < edge && sizeConstant * (0.2 + 1.8 * boundary.at(0)) < direction.at(0)) { // left
            move = mouseMoveConstant / mouse_pixelPos.x;
            actualView.move(- move, 0);
            direction.at(0) -= move;
        } else if (yPosdiff < edge && sizeConstant * (0.7 + 1.5 * boundary.at(3)) > direction.at(1) + size.y) { // down
            move = mouseMoveConstant / yPosdiff;
            actualView.move(0, move);
            direction.at(1) += move;
        } else if (mouse_pixelPos.y < edge && sizeConstant * (0.2 + 1.5 * boundary.at(2)) < direction.at(1)) { // up
            move = mouseMoveConstant / mouse_pixelPos.y;
            actualView.move(0, - move);
            direction.at(1) -= move;
        }
    }
}

void GraphRenderer::display_score(sf::RenderWindow& window, const Gamemaster& gamemaster) {
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

    std::string PlayerScore = "Your Score: " + std::to_string(gamemaster.GameState.score);
    std::string AgentScore = "Computer Score: " + std::to_string(gamemaster.AgentState.score);  
    sf::Text text(PlayerScore + "\n" + AgentScore, font, 45);
    text.setColor(sf::Color::Black);
    text.setPosition(x_pos + 150, y_pos);

    window.draw(rect);
    window.draw(text);
}

//Method which will set the move speed in terms of Computer speed with an upper Bound
void GraphRenderer::update(float delta) {
    moveConstant = delta * 10000;
    const double maxDelta = 2.5;
    if (animate && AnimationStep <= maxDelta) {
        AnimationStep += delta;
        float step = AnimationStep / maxDelta;
        AnimationSpeed = step * (3 + (step - 3) * step); // acceleration and slowing down
    } else {
        AnimationStep = 0;
        AnimationSpeed = 0;
        animate = false;
    }
}

vector<DrawNode> GraphRenderer::updateDrawNode(vector<Node>& nodeList) {
    vector<DrawNode> newNodes = old_nodes;
    vector<sf::Vector2i> nodeIndices;
    bool checked = true;
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
    return newNodes;
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
GraphRenderer::GraphRenderer(sf::RenderWindow& window, Gamemaster& gamemaster, float xoffset) {
    offset = xoffset;
    vector<Node> nodeList = gamemaster.GameGraph.getNodes();
    vector<Edge> edgeList = gamemaster.GameGraph.getEdges();
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
    animate = false; 
    defaultView = window.getDefaultView();
    actualView = defaultView;
    initShapes(gamemaster.GameNodes, nodeList);
    AnimationStep = 0;
    AnimationSpeed = 0;
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
    //Placeholder for readablity of the nodes
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
        if (gameState.selectable.at(i) && recent->i == gameState.edges.at(i).first->i 
                                       && recent->j == gameState.edges.at(i).first->j) {
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
void GraphRenderer::selectEdge(vector<Node>& nodeList, Gamemaster& gamemaster) {
    int ind = consistentEdges.at(hoveredEdgeIndex).getIndex();
    gamemaster.GameState.select(ind);
    gamemaster.GameState.calculate_score();
    std::pair <state*, unsigned int> stateAction = gamemaster.GameAgent.executePolicy(gamemaster.AgentState, gamemaster.GameAgent.policy);
    gamemaster.AgentState = stateAction.first;
    gamemaster.AgentState.calculate_score();
    Edge temp = gamemaster.GameState.edges.at(ind);
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
    Edge tempAgent = gamemaster.GameState.edges.at(stateAction.second);
    int startAgent = 0;
    int endAgent = 0;
    for (unsigned i = 0; i < nodeList.size(); i++) {
        if (tempAgent.first->i == nodeList.at(i).i && tempAgent.first->j == nodeList.at(i).j)
            startAgent = i;
        if (tempAgent.second->i == nodeList.at(i).i && tempAgent.second->j == nodeList.at(i).j) {
            endAgent = i;
            break;
        }
    }
    FuncArrowShape fill(gamemaster.GameNodes, sizeConstant, sf::Color::Black, start, end, ind, offset, false);
    FuncArrowShape fillAgent(gamemaster.GameNodes, sizeConstant, sf::Color::Red, startAgent, endAgent, stateAction.second, offset, true);
    //Save the selected edge in visuals
    selectedEdges.push_back(fill);
    selectedEdges.push_back(fillAgent);
    consistentEdges.clear();
    nodeClicked = false;
    edgeHovered = false;
    deClickNode();
    // calculate new node coordinate
    old_nodes = gamemaster.GameNodes;
    new_nodes = updateDrawNode(nodeList);
    animate = true; 
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
}

void GraphRenderer::animation(sf::RenderWindow& window, Gamemaster& gamemaster, vector<Node>& nodeList, 
                              Button& menuButton){        
    unsigned int equal = 0; // number of equal nodes in new_nodes and old_nodes 
    if (animate) {
        for (unsigned int i = 0; i < nodeList.size(); i++) {
            if (old_nodes.at(i).coordinate.x != new_nodes.at(i).coordinate.x) {
                gamemaster.GameNodes.at(i).coordinate.x = old_nodes.at(i).coordinate.x * (1 - AnimationSpeed)
                                                        + new_nodes.at(i).coordinate.x * AnimationSpeed;            
            } else {
                equal++;
            }
        }
        if (equal == nodeList.size()) { // all nodes are equal -> we don't need a animation
            AnimationStep = 0;
            AnimationSpeed = 0;
            animate = false;
        }
    
        window.clear(sf::Color::White);
        for (auto &arr : selectedEdges)
            arr.setCoordsByPos(gamemaster.GameNodes, sizeConstant, offset);
        setCoords(gamemaster.GameNodes, nodeList);
        window.setView(actualView);
        drawShape(window);
        drawText(window);
        display_score(window, gamemaster);
        window.draw(menuButton.get_Button_Sprite());
        window.display();
        updateBoundaries(new_nodes);
    } else {
        equal = 0;
    }
}

bool GraphRenderer::getAnimate(){
    return animate;
}
   
