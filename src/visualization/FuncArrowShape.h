
#ifndef FuncArrowShape_H_
#define FuncArrowShape_H_

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <vector>
#include <cmath>
#include "ArrowShape.h"
#include "../alignment/Edge.h"

using namespace std;

class FuncArrowShape : public ArrowShape {
    protected:
        sf::Color hovCol;
        int index;
    public:
        FuncArrowShape();
        FuncArrowShape(sf::Vector2f s, sf::Vector2f e, int size, sf::Color col);
        FuncArrowShape(Edge Arr, int size, sf::Color col, int ind);
        int getIndex();
        void hoverFunc();
        void deHoverFunc();
};

#endif //FuncArrowShape_H_
