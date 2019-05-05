
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
#include "../colorlist.h"
#include "../colormap.h"
#include "../../alignment/Graph.h"
#include "../../alignment/Edge.h"
#include <stdlib.h>
#include "ArrowShape.h"

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
        std::vector<SimpleArrow> arrows;
        std::vector<sf::RectangleShape> rects;
        std::vector<TextProps> txt;
        std::vector<ArrowShape> arrows2;
        int size;
        sf::View bild;
	public:
        void initShapes(vector<Node>& nodeList);
        void drawShape(sf::RenderWindow& window);
        void drawText(sf::RenderWindow& window);
        void moveWindow(int dir, sf::RenderWindow& window);
        vector<int> direction;
        GraphRenderer(sf::RenderWindow& window, vector<Node>& nodeList, int s);
		GraphRenderer();
		Node positionToNode(uint xpos, uint ypos, vector<Node>& nodeList, uint size);
		bool isPositionNode(uint xpos, uint ypos, uint size);
};

#endif //_H_

