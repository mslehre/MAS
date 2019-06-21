#ifndef FuncArrowShape_H_
#define FuncArrowShape_H_

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <vector>
#include <cmath>
#include "ArrowShape.h"
#include "../alignment/Edge.h"

using namespace std;

/** \brief This Class stores the methods to draw an arrow for the game with some functionalities
 *
 * 
 *
 */
class FuncArrowShape : public ArrowShape {
    protected:
        sf::Color hovCol; ///< the color of a hovered edge (see GraphRenderer.h)
        int indexOfState; ///< the index of the edge for the state vectors (see State.h)
        sf::Vector2i indexOfDrawNode;
    public:
        /**
         * The standard constructor. This does nothing.
         */
        FuncArrowShape();
        /**
         * The half-complete constructor, which initialize a arrow by start and end coords, 
         * with a specified color and in terms of the sizeConstant we know out of 
         * GraphRenderer.h
         *
         * \param s the start coords point of the arrow
         * \param e the end coords point of the arrow
         * \param sizeConstant an integer which scales the arrow
         * \param col the color of the arrow
         */
        FuncArrowShape(sf::Vector2f s, sf::Vector2f e, int sizeConstant, sf::Color col);
        /**
         * The complete constructor, which initialize a arrow by an edge, 
         * with a specified color, the index of the state vector it corresponds to and 
         * in terms of the sizeConstant we know out of GraphRenderer.h
         *
         * \param Arr the edge which get made to an Funcarrowshape
         * \param ind an integer which is the index of the corresponded edge Vector in state
         * \param sizeConstant an integer which scales the arrow
         * \param col the color of the arrow
         */
        FuncArrowShape(vector<DrawNode>& Nodes, int sizeConstant, sf::Color col, int start, int end, int ind2);
        /**
         * a function to get the protected index
         *
         * \return an integer which is the index in the corresponded edge vector in state
         */
        void setCoordsByPos(vector<DrawNode>& Nodes, int sizeConstant);
        sf::Vector2i getIndexOfArrow();
        int getIndex();
        /**
         * A function which manipulate the FuncArrowShape
         */
        void hoverFunc();
        /**
         * A function which remove all manipulations of the FuncArrowShape
         */
        void deHoverFunc();
};

#endif //FuncArrowShape_H_
