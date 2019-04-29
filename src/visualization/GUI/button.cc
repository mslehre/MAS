#include <SFML/Graphics.hpp>
#include <vector>
#include "button.h"

Button::Button(std::vector<sf::Texture>& all_textures, int index, int x_pos, int y_pos, void function()) {    
    Button_texture = loadSprite(all_textures, index, x_pos, y_pos);
    Button_function = function;
}

sf::Sprite Button::loadSprite(std::vector<sf::Texture>& all_textures, int index, int x_pos, int y_pos) { 
    sf::Sprite Button;
    Button.setTexture(all_textures[index]);
    Button.setPosition(sf::Vector2f(x_pos, y_pos));

    return Button;
}

sf::Sprite Button::get_Button_texture() {
    return Button_texture;
}
