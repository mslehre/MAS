#include "edgeShape.h"

using namespace std;

edgeShape::edgeShape() { 
}

edgeShape::edgeShape(pair<int, int> firstCoord, pair<int, int> secondCoord, sf::Color color) {
    this->firstCoord = firstCoord;
    this->secondCoord = secondCoord;
	this->color = color;
	this->dist = sqrt(pow(firstCoord.first-secondCoord.first, 2) + pow(firstCoord.second-secondCoord.second, 2));
	this->angle = (acos((secondCoord.first-firstCoord.first)/dist));
}

void edgeShape::draw(sf::RenderWindow& window){

	sf::RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f(dist,3));
    rectangle.setFillColor(color);
    rectangle.setPosition(firstCoord.first, firstCoord.second);
	rectangle.setRotation(angle);
    window.draw(rectangle);
}

