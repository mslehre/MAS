#include "scrollbar.h"
#include <math.h>

using namespace std;

scrollbar::scrollbar(sf::RenderWindow& window, sf::Vector2f posOfWind, sf::Vector2f xxbound, sf::Vector2f yybound, float thicknesss){
    sf::Vector2f sizeOfView = window.getView().getSize();
    actualView = window.getView();

    xbound = xxbound;
    ybound = yybound;
    thickness = thicknesss;
    posOfWin = posOfWind;

    movable1 = false;
    movable2 = false;

    xScrollEl.setPosition(posOfWin.x, posOfWin.y + sizeOfView.y - thickness);
    xScrollEl.setFillColor(sf::Color(160, 160, 160));
    xScrollEl.setOutlineColor(sf::Color(128, 128, 128));
    xScrollEl.setOutlineThickness(1);
    xScrollEl.setSize(sf::Vector2f(sizeOfView.x, thickness));

    xScrollBar.setFillColor(sf::Color(100, 100, 100));
    xScrollBar.setOutlineColor(sf::Color(128, 128, 128));
    xScrollBar.setOutlineThickness(1);
    if (xbound.y - xbound.x > sizeOfView.x) {
        xScrollBar.setSize(sf::Vector2f((sizeOfView.x / (xbound.y - xbound.x)) * sizeOfView.x, thickness));
        xScrollBar.setOrigin(((sizeOfView.x / (xbound.y - xbound.x)) * sizeOfView.x) / 2, 0);
    } else {
        xScrollBar.setSize(sf::Vector2f(sizeOfView.x, thickness));
        xScrollBar.setOrigin(sizeOfView.x / 2, 0);
    }
    xScrollBar.setPosition(posOfWin.x + xScrollBar.getSize().x / 2, posOfWin.y + sizeOfView.y - thickness);

    yScrollEl.setPosition(posOfWin.x + sizeOfView.x - thickness, posOfWin.y);
    yScrollEl.setFillColor(sf::Color(160, 160, 160));
    yScrollEl.setOutlineColor(sf::Color(128, 128, 128));
    yScrollEl.setOutlineThickness(1);
    yScrollEl.setSize(sf::Vector2f(thickness, sizeOfView.y));

    yScrollBar.setFillColor(sf::Color(100, 100, 100));
    yScrollBar.setOutlineColor(sf::Color(128, 128, 128));
    yScrollBar.setOutlineThickness(1);
    if (ybound.y - ybound.x > sizeOfView.y) {
        yScrollBar.setSize(sf::Vector2f(thickness, sizeOfView.y / (ybound.y - ybound.x) * sizeOfView.y));
        yScrollBar.setOrigin(0, sizeOfView.y / (ybound.y - ybound.x) * sizeOfView.y / 2);
    } else {
        yScrollBar.setSize(sf::Vector2f(thickness, sizeOfView.y));
        yScrollBar.setOrigin(0, sizeOfView.y / 2);
    }
    yScrollBar.setPosition(posOfWin.x + sizeOfView.x - thickness, posOfWin.y + yScrollBar.getSize().y / 2);

    xQuot = ((posOfWin.x + xScrollBar.getSize().x / 2) - (posOfWin.x + xScrollBar.getSize().x / 2)) / ((posOfWin.x + actualView.getSize().x - xScrollBar.getSize().x / 2) - (posOfWin.x + xScrollBar.getSize().x / 2));
    xPos = xScrollBar.getSize().x / 2;
    yQuot = ((posOfWin.y + yScrollBar.getSize().y / 2) - (posOfWin.y + yScrollBar.getSize().y / 2)) / ((posOfWin.y + actualView.getSize().y - yScrollBar.getSize().y / 2) - (posOfWin.y + yScrollBar.getSize().y / 2));
    yPos = yScrollBar.getSize().y / 2;

}

void scrollbar::draw(sf::RenderWindow& window, sf::View& myView, vector<float>& direction){
    /*if (window.getView().getCenter() != actualView.getCenter()) { TODO: CHANGE
        sf::Vector2f offset = window.getView().getCenter() - actualView.getCenter();
        actualView = window.getView();
        posOfWin += offset;
        xScrollEl.setPosition(posOfWin.x, posOfWin.y + actualView.getSize().y - thickness);
        yScrollEl.setPosition(posOfWin.x + actualView.getSize().x - thickness, posOfWin.y);
        xScrollBar.setPosition(posOfWin.x + xPos, posOfWin.y + actualView.getSize().y - thickness);
        yScrollBar.setPosition(posOfWin.x + actualView.getSize().x - thickness, posOfWin.y + yPos);
    }*/

    float shift;
    float xoffset = 0;
    float yoffset = 0;

    auto mouse_position = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && xScrollBar.getGlobalBounds().contains(mouse_position)) {
        movable1 = true;
        movable2 = false;
    } else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && yScrollBar.getGlobalBounds().contains(mouse_position)) {
        movable1 = false;
        movable2 = true;
    }
    if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        movable1 = false;
        movable2 = false;
    }
    if (movable1) {
        if (posOfWin.x <= mouse_position.x - xScrollBar.getSize().x / 2 && mouse_position.x + xScrollBar.getSize().x / 2 <= posOfWin.x + actualView.getSize().x) {
            xScrollBar.setPosition(mouse_position.x, posOfWin.y + actualView.getSize().y - thickness);
            xQuot = ((mouse_position.x) - (posOfWin.x + xScrollBar.getSize().x / 2)) / ((posOfWin.x + actualView.getSize().x - xScrollBar.getSize().x / 2) - (posOfWin.x + xScrollBar.getSize().x / 2));
            xPos = mouse_position.x - posOfWin.x;
        } else if (mouse_position.x + xScrollBar.getSize().x / 2 >= posOfWin.x + actualView.getSize().x /*&& !((mouse_position.x - posOfWin.x) < actualView.getSize().x / 2)*/) {
            xScrollBar.setPosition(posOfWin.x + actualView.getSize().x - xScrollBar.getSize().x / 2, posOfWin.y + actualView.getSize().y - thickness);
            xQuot = ((posOfWin.x + actualView.getSize().x - xScrollBar.getSize().x / 2) - (posOfWin.x + xScrollBar.getSize().x / 2)) / ((posOfWin.x + actualView.getSize().x - xScrollBar.getSize().x / 2) - (posOfWin.x + xScrollBar.getSize().x / 2));
            xPos = actualView.getSize().x - xScrollBar.getSize().x / 2;
        } else {
            xScrollBar.setPosition(posOfWin.x + xScrollBar.getSize().x / 2, posOfWin.y + actualView.getSize().y - thickness);
            xQuot = ((posOfWin.x + xScrollBar.getSize().x / 2) - (posOfWin.x + xScrollBar.getSize().x / 2)) / ((posOfWin.x + actualView.getSize().x - xScrollBar.getSize().x / 2) - (posOfWin.x + xScrollBar.getSize().x / 2));
            xPos = xScrollBar.getSize().x / 2;
        }
        shift = xbound.x + ((xbound.y - xbound.x) * xQuot);
        xoffset = shift - posOfWin.x;
        actualView.move(xoffset, 0);
        posOfWin.x = shift;
        xScrollEl.setPosition(posOfWin.x, posOfWin.y + actualView.getSize().y - thickness);
        yScrollEl.setPosition(posOfWin.x + actualView.getSize().x - thickness, posOfWin.y);
        xScrollBar.setPosition(posOfWin.x + xPos, posOfWin.y + actualView.getSize().y - thickness);
        yScrollBar.setPosition(posOfWin.x + actualView.getSize().x - thickness, posOfWin.y + yPos);
    }
    if (movable2) {
        if (posOfWin.y <= mouse_position.y - yScrollBar.getSize().y / 2 && mouse_position.y + yScrollBar.getSize().y / 2 <= posOfWin.y + actualView.getSize().y) {
            yScrollBar.setPosition(posOfWin.x + actualView.getSize().x - thickness, mouse_position.y);
            yQuot = ((mouse_position.y) - (posOfWin.y + yScrollBar.getSize().y / 2)) / ((posOfWin.y + actualView.getSize().y - yScrollBar.getSize().y / 2) - (posOfWin.y + yScrollBar.getSize().y / 2));
            yPos = mouse_position.y - posOfWin.y;
        } else if (mouse_position.y + yScrollBar.getSize().y / 2 >= posOfWin.y + actualView.getSize().y) {
            yScrollBar.setPosition(posOfWin.x + actualView.getSize().x - thickness, posOfWin.y + actualView.getSize().y);
            yQuot = ((posOfWin.y + actualView.getSize().y - yScrollBar.getSize().y / 2) - (posOfWin.y + yScrollBar.getSize().y / 2)) / ((posOfWin.y + actualView.getSize().y - yScrollBar.getSize().y / 2) - (posOfWin.y + yScrollBar.getSize().y / 2));
            yPos = actualView.getSize().y - yScrollBar.getSize().y / 2;
        } else {
            yScrollBar.setPosition(posOfWin.x + actualView.getSize().x - thickness, posOfWin.y);
            yQuot = ((posOfWin.y + yScrollBar.getSize().y / 2) - (posOfWin.y + yScrollBar.getSize().y / 2)) / ((posOfWin.y + actualView.getSize().y - yScrollBar.getSize().y / 2) - (posOfWin.y + yScrollBar.getSize().y / 2));
            yPos = yScrollBar.getSize().y / 2;
        }
        shift = ybound.x + ((ybound.y - ybound.x) * yQuot);
        yoffset = shift - posOfWin.y;
        actualView.move(0, yoffset);
        posOfWin.y = shift;
        xScrollEl.setPosition(posOfWin.x, posOfWin.y + actualView.getSize().y - thickness);
        yScrollEl.setPosition(posOfWin.x + actualView.getSize().x - thickness, posOfWin.y);
        xScrollBar.setPosition(posOfWin.x + xPos, posOfWin.y + actualView.getSize().y - thickness);
        yScrollBar.setPosition(posOfWin.x + actualView.getSize().x - thickness, posOfWin.y + yPos);
    }
    myView.move(xoffset, yoffset);
    direction.at(0) += xoffset;
    direction.at(1) += yoffset;
    window.setView(myView);

    window.draw(yScrollEl);
    window.draw(xScrollEl);
    window.draw(yScrollBar);
    window.draw(xScrollBar);
}

