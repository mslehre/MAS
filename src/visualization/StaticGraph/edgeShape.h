#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <iostream>
#include <algorithm>
#include <vector>
#include <array>
#include <string>
#include <cmath>
#include <utility>

using namespace std;

class edgeShape{
    public:
        edgeShape();
        edgeShape(pair<int, int> firstCoord, pair<int, int> secondCoord, sf::Color color);
        pair<int, int> firstCoord;         ///< 
       	pair<int, int> secondCoord;         ///< 
		unsigned int dist;  
		float angle;		
		sf::Color color; 
		void draw(sf::RenderWindow& window);
};

