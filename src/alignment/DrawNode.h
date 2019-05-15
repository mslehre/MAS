#pragma once
#include <SFML/Graphics.hpp>
#include "Node.h"

 /** 
  * \brief The class "DrawNode" inherits from the class "Node"
  * and additionally has the properties "x_coord", "y-coord" and "sf :: Color col".
  */

class DrawNode : public Node {
    public:
        unsigned x_coord;   ///< x-coordinate
        unsigned y_coord;   ///< y-coordinate
        sf::Color col;      ///< color k-mer
};
