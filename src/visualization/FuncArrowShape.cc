#include "FuncArrowShape.h"
#include <cmath>
using namespace std;

FuncArrowShape::FuncArrowShape() { 
}

FuncArrowShape::FuncArrowShape(Edge Arr, int size,sf::Color col) {
    int arr[4] = {Arr.first.i,Arr.first.j,Arr.second.i,Arr.second.j};
    sf::Vector2f start(size*0.2+(size*1.8)*arr[1]+(size/2),size*0.2+((size/2)*3)*arr[0]+(size/2));
    sf::Vector2f End(size*0.2+(size*1.8)*arr[3]+(size/2),size*0.2+((size/2)*3)*arr[2]);
    edge = Arr;
    hovCol = col;
    initArrow(start,End,col);
}

FuncArrowShape::FuncArrowShape(sf::Vector2f s, sf::Vector2f e, sf::Color col) {
    initArrow(s,e,col);
}

Edge FuncArrowShape::getEdge() {
    return edge;
}

void FuncArrowShape::hoverFunc() {
	line.setOutlineColor(sf::Color::Black);
    tri.setOutlineColor(sf::Color::Black);
}

void FuncArrowShape::deHoverFunc() {
    line.setOutlineColor(hovCol);
    tri.setOutlineColor(hovCol);
}

