#include "Button.h"
#include <iostream>

Button::Button(std::string texturename, unsigned int x_pos, unsigned int y_pos, std::string nextStatus, std::string myStatus){
    Button_texturename = texturename;   
    load_Texture(texturename);
    Button_Sprite.setPosition(sf::Vector2f(x_pos, y_pos));
    next_status = nextStatus; 
    my_status = myStatus;  
}

void Button::load_Texture(std::string name){
    if (!Button_Texture.loadFromFile(name))
        std::cerr << "Error: Can not load " << name << "." << std::endl;
    Button_Sprite.setTexture(Button_Texture);
}

sf::Sprite Button::get_Button_Sprite(){
    return Button_Sprite;
}

std::string Button::eventHandler(sf::Event event, std::string status, sf::Vector2f global_mouse_pos) {
    if (status == my_status) {
        if (event.type == sf::Event::EventType::MouseMoved) {
            if (Button_Sprite.getGlobalBounds().contains(global_mouse_pos)) {
                std::string hover = Button_texturename.substr(0, Button_texturename.size() - 4) + "_hover.png";
                load_Texture(hover);
            } else {
                load_Texture(Button_texturename);
            }
        }

        if (event.type == sf::Event::EventType::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            if (Button_Sprite.getGlobalBounds().contains(global_mouse_pos)) {
                Button_function();
                return next_status;
            }
        }
    }
    return status;
}

void Button::setFunction(std::function<void()> func) {
    Button_function = func;
}

