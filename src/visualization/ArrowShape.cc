#include "ArrowShape.h"
using namespace std;

double norm(sf::Vector2f vec) {
    return sqrt(pow(vec.x, 2) + pow(vec.y, 2));
}

double innerPr(sf::Vector2f vec1, sf::Vector2f vec2) {
    return vec1.x * vec2.x + vec1.y * vec2.y;
}

ArrowShape::ArrowShape() {
}

ArrowShape::ArrowShape(sf::Vector2f s, sf::Vector2f e, int sizeConstant, sf::Color col) {
    initArrow(s, e, sizeConstant, col);
}

// the main initialization of the arrows
void ArrowShape::initArrow(sf::Vector2f start, sf::Vector2f end, int sizeConstant, sf::Color col) {
    sf::Vector2f diagVec = end - start;
    float scalar1 = 0.001;
    float scalar2 = 0.999;
    sf::Vector2f softStart = end - (diagVec*scalar2);
    sf::Vector2f softEnd = end - (diagVec*scalar1);
    sf::Vector2f movement(0, 5);
    diagVec = softEnd - softStart;
    sf::Vector2f right(1, 0);
    double norm_diag = norm(diagVec);
    double angle_diag = (360 / (2 * PI)) * acos(innerPr(right, diagVec) / (norm_diag * norm(right)));
    line.setSize(sf::Vector2f(norm_diag, 0));
    line.setOutlineColor(col);
    line.setOutlineThickness(sizeConstant / 50);
    line.setPosition(softStart);
    line.setRotation(angle_diag);
    tri.setRadius(sizeConstant / 10);
    tri.setPointCount(3);
    tri.setOrigin(sizeConstant / 10, sizeConstant / 10);
    tri.setFillColor(col);
    tri.setOutlineThickness(2.f);
    tri.setOutlineColor(col);
    tri.setPosition(softEnd);
    tri.setRotation(angle_diag + 90);
}

void ArrowShape::Draw(sf::RenderWindow& window) {
    window.draw(line);
    window.draw(tri);
}

sf::CircleShape ArrowShape::getShape() {
    return tri;
}

