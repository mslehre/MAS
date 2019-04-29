#ifndef gui_H_ 
#define gui_H_

#include <string>
#include <vector>

sf::Texture loadtexture(std::string name); ///< loading a single texture
std::vector<sf::Texture> load_all_textures(); ///< loading all textures

#endif //gui_H_ 
