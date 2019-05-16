#pragma once
#include <SFML/Graphics.hpp>

 /** 
  * \brief The class "DrawNode" has the properties "sf::Vector2f" and "sf :: Color col".
  */

class DrawNode {
    public:
       /** 
         * \brief a simple class that defines a mathematical vector with two coordinates (x and y) <br>
         * public attributes: <br>
         * x for the x-coordinate of the vector <br>
         * y for the y-coordinate of the vector 
         */    

        sf::Vector2f coordinate;

        sf::Color col;      ///< color k-mer
};
