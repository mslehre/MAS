#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <iostream>
#include <algorithm>
#include <array>
#include <string>
#include "Graph.h"
#include <stdlib.h>

class GraphRenderer{
	public:
		GraphRenderer();
		void drawRectangle(sf::RenderWindow& window, int i, int j, vector<int> col, string kmer,
 		sf::Font font, uint size);
		void drawLine(sf::RenderWindow& window, int i, int j, uint size);
		void drawGraph(sf::RenderWindow& window, Graph& g, uint size);
		Node& positionToNode(uint xpos, uint ypos, vector<Node>& nodeList, uint size);
		bool isPositionNode(uint xpos, uint ypos, uint size);
		void highlightRectangle(Node& node, sf::Color color, sf::RenderWindow& window, uint size);
};
