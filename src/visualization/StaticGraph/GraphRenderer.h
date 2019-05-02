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
#include <stdlib.h>

class GraphRenderer{
    private:        
        std::vector<std::vector<sf::RectangleShape>> rectangles;
        bool loaded;
	public:
		GraphRenderer();
		void drawRectangle(sf::RenderWindow& window, int i, int j, sf::Color col, string kmer,
 		sf::Font font, uint size);
		void drawLine(sf::RenderWindow& window, int i, int j, uint size);
		void drawGraph(sf::RenderWindow& window, Graph& g, uint size);
		Node positionToNode(uint xpos, uint ypos, vector<Node>& nodeList, uint size);
		bool isPositionNode(uint xpos, uint ypos, uint size);
		void highlightRectangle(Node& node, Graph& g, sf::RenderWindow& window, sf::Color color, uint size);
        void removeRectangle();
};
