#include "FuncArrowShape.h"
#include <iostream>
using namespace std;

FuncArrowShape::FuncArrowShape() {
}

FuncArrowShape::FuncArrowShape(vector<DrawNode>& Nodes, int sizeConstant, sf::Color col, int start, int end,
                               int ind2, float offset, bool enem) {
    sf::Vector2f s(sizeConstant * (0.7 + 1.8 * Nodes.at(start).coordinate.x), sizeConstant * (0.7 + 1.5 * 
                   (Nodes.at(start).coordinate.y + offset)));
    sf::Vector2f e(sizeConstant * (0.7 + 1.8 * Nodes.at(end).coordinate.x), sizeConstant * (0.2 + 1.5 * 
                   (Nodes.at(end).coordinate.y + offset)));
    hovCol = col;
    sf::Vector2i temp(start, end);
    indexOfState = ind2;
    indexOfDrawNode = temp;
    setCoords(s, e);
    setProps(sizeConstant, col);
    enemy = enem;
}

FuncArrowShape::FuncArrowShape(sf::Vector2f s, sf::Vector2f e, int sizeConstant, sf::Color col) {
    setCoords(s, e);
    setProps(sizeConstant, col);
}

void FuncArrowShape::setCoordsByPos(vector<DrawNode>& Nodes, int sizeConstant, float offset) {
    sf::Vector2f s(sizeConstant * (0.7 + 1.8 * Nodes.at(indexOfDrawNode.x).coordinate.x), sizeConstant * 
                   (0.7 + 1.5 * (Nodes.at(indexOfDrawNode.x).coordinate.y + offset)));
    sf::Vector2f e(sizeConstant * (0.7 + 1.8 * Nodes.at(indexOfDrawNode.y).coordinate.x), sizeConstant * 
                   (0.2 + 1.5 * (Nodes.at(indexOfDrawNode.y).coordinate.y + offset)));
    setCoords(s, e);
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

sf::Vector2i FuncArrowShape::getIndexOfArrow() {
    return indexOfDrawNode;
}

bool FuncArrowShape::getEnemy() {
    return enemy;
}
