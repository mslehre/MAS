#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include "gui.h"

/** 
 * \param all_textures is a vector with all textures
 * \param index is the index of the texture you will load from all_textures
 * \param x_pos is the x coordinate of the sprite in the window
 * \param y_pos is the y coordinate of the sprite in the window
 * \return a sprite with texture on a specific position
 */

sf::Sprite loadSprite(std::vector<sf::Texture>& all_textures, int index, int x_pos, int y_pos) { 
    sf::Sprite Button;
    Button.setTexture(all_textures[index]);
    Button.setPosition(sf::Vector2f(x_pos, y_pos));

    return Button;
}

/** 
 * \param name is the name of the texture
 * \return a Texture
 */

sf::Texture loadtexture(std::string name) {
    sf::Texture ButtonTexture;

    if (!ButtonTexture.loadFromFile(name)) {
        std::cerr << "Error: Can not load " << name << "." << std::endl;
    }

    return ButtonTexture;
}
