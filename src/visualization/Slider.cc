#include "Slider.h"

using namespace std;

Slider::Slider(unsigned int x_pos, unsigned int y_pos, unsigned int min, unsigned int max, unsigned int& variable, string name){
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
    axis.setOrigin(0, axis_height / 2);

    slider.setPosition(x_pos + (axis_width / (max - min)) * (value - min), y_pos);
    slider.setFillColor(sf::Color(200, 200, 200));
    slider.setOutlineColor(sf::Color::Black);
    slider.setOutlineThickness(1);
    slider.setSize(sf::Vector2f(slider_width, axis_height * 3));
    slider.setOrigin(slider_width / 2, axis_height * 1.5);
}

void Slider::draw(sf::RenderWindow& window, unsigned int& number){
    auto mouse_position = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && slider.getGlobalBounds().contains(mouse_position))
        movable = true;
    if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
        movable = false;
    if (movable && x_pos <= mouse_position.x && mouse_position.x <= x_pos + axis_width) {
        slider.setPosition(mouse_position.x, y_pos);
        value = ceil(min + ((slider.getPosition().x - x_pos) / axis_width * (max - min)));
        number = value;
    }

    window.draw(axis);
    window.draw(slider);
    window.draw(drawText(to_string(min), x_pos - 10, y_pos + axis_height + 8,  20));
    window.draw(drawText(to_string(max), x_pos + axis_width - 10, y_pos + axis_height + 8,  20));
    window.draw(drawText(to_string(value), x_pos + axis_width / 2, y_pos + axis_height + 5,  25));
    window.draw(drawText(name, x_pos + axis_width / 2, y_pos - axis_height * 3,  25));
}

sf::Text Slider::drawText(std::string s, int x_pos, int y_pos,  unsigned int size){
    text.setString(s);	
    text.setPosition(x_pos, y_pos);
    text.setCharacterSize(size);
    return text;
}
