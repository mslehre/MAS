#include "ArrowShape.h"
#include <cmath>
using namespace std;

double PI = 3.14159265359;

double norm(sf::Vector2f vec) {
    return sqrt(pow(vec.x, 2) + pow(vec.y, 2));
}
double innerPr(sf::Vector2f vec1, sf::Vector2f vec2) {
    return vec1.x*vec2.x + vec1.y*vec2.y;
}

ArrowShape::ArrowShape() { 
}

ArrowShape::ArrowShape(Edge Arr, int size) {
    int arr[4] = {Arr.first.i,Arr.first.j,Arr.second.i,Arr.second.j};
    sf::Vector2f start(size*0.2+(size*1.8)*arr[1]+(size/2),size*0.2+((size/2)*5)*arr[0]+(size/2));
    sf::Vector2f End(size*0.2+(size*1.8)*arr[3]+(size/2),size*0.2+((size/2)*5)*arr[2]);
    initArrow(start,End);

}

ArrowShape::ArrowShape(sf::Vector2f s, sf::Vector2f e) {
    initArrow(s,e);
}

void ArrowShape::initArrow(sf::Vector2f start, sf::Vector2f end) {
    sf::Vector2f diagVec = end - start;
    sf::Vector2f right(1,0);
    double norm_diag = norm(diagVec);
    double angle_diag = (360/(2*PI))*acos(innerPr(right,diagVec)/(norm_diag*norm(right)));
    cout << angle_diag << ", " << norm_diag << endl;
    sf::RectangleShape fill;
    /*    
    this->firstCoord = firstCoord;
    this->secondCoord = secondCoord;
	this->color = color;
	this->dist = sqrt(pow(firstCoord.first-secondCoord.first, 2) + pow(firstCoord.second-secondCoord.second, 2));
	this->angle = (acos((secondCoord.first-firstCoord.first)/dist));
    */
    line.setSize(sf::Vector2f(norm_diag, 0));
	line.setOutlineColor(sf::Color::Black);
	line.setOutlineThickness(2);
    line.setPosition(start);
    line.setRotation(angle_diag);
}

void ArrowShape::Draw(sf::RenderWindow& window){
    window.draw(line);
}

