
#ifndef GraphRenderer_H_
#define GraphRenderer_H_

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <iostream>
#include <algorithm>
#include <vector>
#include <array>
#include <string>
#include "colorlist.h"
#include "colormap.h"
#include "../alignment/Graph.h"
#include "../alignment/Edge.h"
#include <stdlib.h>
#include "ArrowShape.h"
#include "FuncArrowShape.h"
#include "../alignment/State.h"

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
    private:
        std::vector<FuncArrowShape> tempArr;
        std::vector<FuncArrowShape> arrowList;
        std::vector<SimpleArrow> arrows;
        std::vector<std::vector<sf::RectangleShape>> rects;
        std::vector<TextProps> txt;
        int index;
        sf::Vector2i highlight;
        sf::Color highlightCol;
        sf::View actualView;
        sf::View defaultView;
        int size;
        float moveSize;
        state *gameState;
	public:
        bool hovered;
        bool clicked;
        bool st_hovered;
        vector<int> direction;

        GraphRenderer(sf::RenderWindow& window, vector<Node>& nodeList, vector<Edge>& edgeList, int s);
		GraphRenderer();
        
        void render(sf::RenderWindow& window);
        void eventHandler(sf::Event event, sf::RenderWindow& window, vector<Node>& nodeList);
        void update(float delta);

        void initShapes(vector<Node>& nodeList);
        void drawShape(sf::RenderWindow& window);
        void drawText(sf::RenderWindow& window);
        void moveWindow(int dir);
        void addToGame(sf::Vector2f pos);
        void highlightHover(sf::Vector2f pos);
        void deHighlightHover();
        void edgeHover(sf::Vector2f pos);
        void deEdgeHover();
        void clickKmer();
        void deClickKmer(sf::Vector2f pos);
        void showEdges(vector<Node>& nodeList, sf::Vector2f pos);
		Node* positionToNode(sf::Vector2f pos, vector<Node>& nodeList);
        bool isPositionEdge(sf::Vector2f pos);
		bool isPositionNode(sf::Vector2f pos);
};

#endif //GraphRenderer_H_

