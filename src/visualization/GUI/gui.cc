#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include "gui.h"

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

/** 
 * \return a vector with all textures
 */

std::vector<sf::Texture> load_all_textures() {
    std::vector<sf::Texture> textures;
    textures.push_back(loadtexture("../../../fig/startButton.png"));
    textures.push_back(loadtexture("../../../fig/settingsButton.png"));
    textures.push_back(loadtexture("../../../fig/quitButton.png"));

    return textures;
}

