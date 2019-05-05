#include "FuncArrowShape.h"
#include <cmath>
using namespace std;

FuncArrowShape::FuncArrowShape() { 
}

FuncArrowShape::FuncArrowShape(Edge Arr, int size) {
    int arr[4] = {Arr.first.i,Arr.first.j,Arr.second.i,Arr.second.j};
    sf::Vector2f start(size*0.2+(size*1.8)*arr[1]+(size/2),size*0.2+((size/2)*3)*arr[0]+(size/2));
    sf::Vector2f End(size*0.2+(size*1.8)*arr[3]+(size/2),size*0.2+((size/2)*3)*arr[2]);
    edge = Arr;
    initArrow(start,End);
}

FuncArrowShape::FuncArrowShape(sf::Vector2f s, sf::Vector2f e) {
    initArrow(s,e);
}

