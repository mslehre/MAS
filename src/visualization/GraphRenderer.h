
#ifndef GraphRenderer_H_
#define GraphRenderer_H_

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <vector>
#include <string>
#include <stdlib.h>
#include <cmath>
#include "colorlist.h"
#include "colormap.h"
#include "../alignment/Graph.h"
#include "../alignment/Edge.h"
#include "../alignment/State.h"
#include "ArrowShape.h"
#include "FuncArrowShape.h"

void printHelp();

class GraphRenderer{
    struct SimpleArrow {
        sf::RectangleShape line;
        sf::CircleShape triangle;
    };
    struct TextProps {
        std::string kmer;
        sf::Color col;
        vector<int> pos;
        int charSize;
    };
    protected:
        std::vector<FuncArrowShape> consistentEdges;
        std::vector<FuncArrowShape> selectedEdges;
        std::vector<SimpleArrow> arrows;
        std::vector<std::vector<sf::RectangleShape>> rects;
        std::vector<TextProps> txt;
        sf::Vector2i hoverPosition;
        sf::Color colorOfHoveredNode;
        sf::View actualView;
        sf::View defaultView;
        int maxNodesPerRow;
        int maxSequences;
        int sizeConstant;
        float moveConstant;
        vector<float> direction;
        state gameState;
	public:
        bool nodeHovered;
        bool nodeClicked;
        bool edgeHovered;
        int hoveredEdgeIndex;

        GraphRenderer(sf::RenderWindow& window, vector<Node>& nodeList, vector<Edge>& edgeList, int sizeConst);
		GraphRenderer();
        
        void render(sf::RenderWindow& window);
        void eventHandler(sf::Event event, sf::RenderWindow& window, vector<Node>& nodeList);
        void update(float delta);

        void initShapes(vector<Node>& nodeList);
        void drawShape(sf::RenderWindow& window);
        void drawText(sf::RenderWindow& window);
        void moveWindow(int dir);
        void showEdges(vector<Node>& nodeList, sf::Vector2f pos);
        void selectEdge(sf::Vector2f pos);
        void hoverNode(sf::Vector2f pos);
        void deHoverNode();
        void hoverEdge(sf::Vector2f pos);
        void deHoverEdge();
        void clickNode();
        void deClickNode(sf::Vector2f pos);
		Node* positionToNode(sf::Vector2f pos, vector<Node>& nodeList);
        bool isPositionEdge(sf::Vector2f pos);
		bool isPositionNode(sf::Vector2f pos);
};

#endif //GraphRenderer_H_

