#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <functional>
#include "button.h"

Button::Button(std::string texturename, unsigned int x_pos, unsigned int y_pos, std::function<void()> function){ 
    load_Texture(texturename);
    Button_Sprite.setPosition(sf::Vector2f(x_pos, y_pos));    
    Button_function = function;
}

void Button::load_Texture(std::string name){
    if (!Button_Texture.loadFromFile(name)) {
        std::cerr << "Error: Can not load " << name << "." << std::endl;
    }
    Button_Sprite.setTexture(Button_Texture);
}

sf::Sprite Button::get_Button_Sprite(){
    return Button_Sprite;
}
