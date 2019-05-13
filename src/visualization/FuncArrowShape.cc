#include "FuncArrowShape.h"
using namespace std;

FuncArrowShape::FuncArrowShape() {
}

FuncArrowShape::FuncArrowShape(Edge Arr, int size, sf::Color col, int ind) {
    uint arr[4] = {Arr.first->i, Arr.first->j, Arr.second->i, Arr.second->j};
    sf::Vector2f start(size * 0.2 + (size * 1.8) * arr[1] + (size / 2), size * 0.2 + ((size / 2) * 3) * arr[0] + (size / 2));
    sf::Vector2f End(size * 0.2 + (size * 1.8) * arr[3] + (size / 2), size * 0.2 + ((size / 2) * 3) * arr[2]);
    hovCol = col;
    index = ind;
    initArrow(start, End, size, col);
}

FuncArrowShape::FuncArrowShape(sf::Vector2f s, sf::Vector2f e, int size, sf::Color col) {
    initArrow(s, e, size, col);
}

void FuncArrowShape::hoverFunc() {
    line.setOutlineColor(sf::Color::Black);
    tri.setOutlineColor(sf::Color::Black);
}

void FuncArrowShape::deHoverFunc() {
    line.setOutlineColor(hovCol);
    tri.setOutlineColor(hovCol);
}

int FuncArrowShape::getIndex() {
    return index;
}
