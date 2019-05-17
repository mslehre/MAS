#include "FuncArrowShape.h"
using namespace std;

FuncArrowShape::FuncArrowShape() {
}

FuncArrowShape::FuncArrowShape(Edge Arr, int sizeConstant, sf::Color col, int ind) {
    uint arr[4] = {Arr.first->i, Arr.first->j, Arr.second->i, Arr.second->j};
    sf::Vector2f start(sizeConstant * (0.7 + 1.8 * arr[1]), sizeConstant * (0.7 + 1.5 * arr[0]));
    sf::Vector2f End(sizeConstant * (0.7 + 1.8 * arr[3]), sizeConstant * (0.2 + 1.5 * arr[2]));
    hovCol = col;
    indexOfState = ind;
    initArrow(start, End, sizeConstant, col);
}

FuncArrowShape::FuncArrowShape(sf::Vector2f s, sf::Vector2f e, int sizeConstant, sf::Color col) {
    initArrow(s, e, sizeConstant, col);
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
    return indexOfState;
}
