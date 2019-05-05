
#ifndef FuncArrowShape_H_
#define FuncArrowShape_H_

#include "ArrowShape.h"
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

class FuncArrowShape : public ArrowShape {
    protected:
        Edge edge;
        bool clicked;
        bool hovered;
    public:        
        FuncArrowShape();
        FuncArrowShape(sf::Vector2f s, sf::Vector2f e);
        FuncArrowShape(Edge Arr, int size);
        Edge getEdge();
};

#endif //FuncArrowShape_H_
