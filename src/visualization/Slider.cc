#include "Slider.h"
#include <math.h>

using namespace std;

Slider::Slider(unsigned int x_pos, unsigned int y_pos, unsigned int min, unsigned int max, unsigned int& variable, 
               string name){
    this->x_pos = x_pos;
    this->y_pos = y_pos;
    this->min = min;
    this->max = max;
    this->movable = false;
    this->name = name;

    if (variable >= min && variable <= max) {
        value = variable;
    } else {
        value = ceil((min + max) / 2);
        variable = value;
    }

    axis_height = 20;
    axis_width = 600;
    slider_width = 20;

    if (!font.loadFromFile("Amiko-Regular.ttf"))
        std::cout << "Can't find the font file" << std::endl;

    text.setFont(font);
    text.setColor(sf::Color::Black);

    axis.setPosition(x_pos, y_pos);
    axis.setFillColor(sf::Color(100, 100, 100));
    axis.setOutlineColor(sf::Color::Black);
    axis.setOutlineThickness(1);
    axis.setSize(sf::Vector2f(axis_width, axis_height));

    slider_bar.setPosition(x_pos + (axis_width / (max - min)) * (value - min), y_pos);
    slider_bar.setFillColor(sf::Color(200, 200, 200));
    slider_bar.setOutlineColor(sf::Color::Black);
    slider_bar.setOutlineThickness(1);
    slider_bar.setSize(sf::Vector2f(slider_width, axis_height * 3)); // The slider height is in the ratio 1:3 to the axis_height
    slider_bar.setOrigin(slider_width / 2, axis_height);
}

void Slider::draw(sf::RenderWindow& window, unsigned int& variable){
    auto mouse_position = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && slider_bar.getGlobalBounds().contains(mouse_position))
        movable = true;
    if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
        movable = false;
    if (movable) {
        if (x_pos <= mouse_position.x && mouse_position.x <= x_pos + axis_width) {
            slider_bar.setPosition(mouse_position.x, y_pos);
            value = min + ((slider_bar.getPosition().x - x_pos) / axis_width * (max - min));
        } else if (mouse_position.x >= x_pos + axis_width) {
            slider_bar.setPosition(x_pos + axis_width, y_pos);
            value = max;
        } else {
            slider_bar.setPosition(x_pos, y_pos);
            value = min;
        }
        variable = value;
    }

    window.draw(axis);
    window.draw(slider_bar);
    window.draw(drawText(to_string(min), x_pos - 10, y_pos + axis_height * 2,  20));
    window.draw(drawText(to_string(max), x_pos + axis_width - 10, y_pos + axis_height * 2,  20));
    window.draw(drawText(to_string(value), x_pos + axis_width / 2, y_pos + axis_height + 15,  25));
    window.draw(drawText(name, x_pos + axis_width / 2, y_pos - axis_height * 2.5,  25));
}

sf::Text Slider::drawText(std::string s, int x_pos, int y_pos, unsigned int size){
    text.setString(s);	
    text.setPosition(x_pos, y_pos);
    text.setCharacterSize(size);
    return text;
}
