
#ifndef ArrowShape_H_
#define ArrowShape_H_

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <vector>
#include <string>
#include <cmath>
#include "../alignment/Edge.h"

using namespace std;

const double PI = 3.14159265359; ///< \f$ \pi \f$ defined by myself
double norm(sf::Vector2f vec); ///< the euclidean norm \f$ ||\cdot||_2 \f$
double innerPr(sf::Vector2f vec1, sf::Vector2f vec2); ///< the standard inner product \f$ <\cdot ,\cdot > \f$

/** \brief This Class stores the methods to draw a Arrow with a start and end coordinate
 *
 * 
 *
 */
class ArrowShape {
    protected:
        sf::RectangleShape line; ///< the line of the arrow
        sf::CircleShape tri; ///< the front of the arrow (triangle)
    public:
        /**
         * The standard constructor. This does nothing.
         */
        ArrowShape();
        /**
         * The complete constructor, which initialize a arrow by start and end coords, 
         * with a specified color and in terms of the sizeConstant we know out of 
         * GraphRenderer.h
         *
         * \param s the start coords point of the arrow
         * \param e the end coords point of the arrow
         * \param sizeConstant an integer which scales the arrow
         * \param col the color of the arrow
         */
        ArrowShape(sf::Vector2f s, sf::Vector2f e, int sizeConstant, sf::Color col);
        /**
         * The function which initialize both shapes.
         *
         * \param start the start coords point of the arrow
         * \param end the end coords point of the arrow
         * \param sizeConstant an integer which scales the arrow
         * \param col the color of the arrow
         */
        void initArrow(sf::Vector2f start, sf::Vector2f end, int sizeConstant, sf::Color col);
        /**
         * A Method to draw the initialized arrow in a specified window
         *
         * \param window a renderWindow that get the drawed arrowshape
         */
        void Draw(sf::RenderWindow& window);
        /**
         * A method to return the front of the arrow
         *
         * \return a CircleShape which is the triangle of the arrow
         */
        sf::CircleShape getShape();
};

#endif //ArrowShape_H_

