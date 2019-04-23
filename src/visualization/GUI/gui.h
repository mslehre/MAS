#ifndef gui_H_ 
#define gui_H_

#include <string>
#include <vector>

sf::Texture loadtexture(std::string name); ///< loading texture
sf::Sprite loadSprite(std::vector<sf::Texture>& all_textures, int index, int x_pos, int y_pos); ///< loading sprite

#endif //gui_H_ 
