#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "gui.h"

/** 
 * \param name is the name of the texture
 * \return a Sprite with the texture
 */

sf::Sprite loadtexture(std::string name){ //TODO: solve the white box problem (missing texture)
    sf::Texture ButtonTexture;

    if (!ButtonTexture.loadFromFile(name)) {
        std::cerr << "Error: Can not load " << name << "." << std::endl;
    }

    sf::Sprite Button;
    Button.setTexture(ButtonTexture);
    Button.setPosition(sf::Vector2f(200.f, 300.f));

    return Button;
}
