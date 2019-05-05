
#ifndef ArrowShape_H_
#define ArrowShape_H_

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
#include "../../alignment/Edge.h"

using namespace std;

const double PI = 3.14159265359;
double norm(sf::Vector2f vec);
double innerPr(sf::Vector2f vec1, sf::Vector2f vec2);

class ArrowShape {
    protected:
        sf::RectangleShape line;
        sf::CircleShape tri;
    public:
        ArrowShape();
        ArrowShape(sf::Vector2f s, sf::Vector2f e);
        void initArrow(sf::Vector2f start, sf::Vector2f end);
		void Draw(sf::RenderWindow& window);
};

#endif //ArrowShape_H_

