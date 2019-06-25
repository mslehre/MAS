#ifndef GraphRenderer_H_
#define GraphRenderer_H_

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <vector>
#include <string>
#include <stdlib.h>
#include <cmath>
#include <string>
#include "colorlist.h"
#include "colormap.h"
#include "../alignment/Graph.h"
#include "../alignment/Edge.h"
#include "../alignment/State.h"
#include "../alignment/DrawNode.h"
#include "ArrowShape.h"
#include "FuncArrowShape.h"
#include "Button.h"
#include "../GameMain/Gamemaster.h"

void printHelp(); ///< a function which calls a troubleshooting for bad arguments

/** \brief This Class stores Methods which manipulates a window in terms of a MAS Game-Structure.
 *
 * This Class Stores different functionalitys: The shape and text data which visualize the Graph
 * via the window and a seperate Draw function, the functions which give the Graph functionality and
 * the functions which implement general functionalitys. \n\n
 *
 * an explanation: The Class will get initialized with vectors \f$\texttt{nodeList, edgeList}\f$ which have the data of all
 * nodes and edges we're looking for, \f$\texttt{sizeConstant}\f$ which is a constant, that is used to scale the visuals in terms of
 * it (see next point) and \f$\texttt{window}\f$ what is a reference to the window u want to manipulate.\n\n
 *
 * \f$\texttt{sizeConstant}\textrm{:}\f$\n
 * We got in the window rectangles and arrows between them. In coordinates would hold:\n
 * \f$\textrm{For the Rectangle }R_{i,j}\textrm{ and a sizeConstant }s\textrm{ ,where }i\textrm{ and }j\textrm{ are the indices of the nodes,
 * holds that length}(R_{i,j})=s, \textrm{width}(R_{i,j})=\frac{1}{2}\cdot s \textrm{ and upperleftpoint}(R_{i,j})=
 * (s\cdot(0,2 + 1,8\cdot j),s\cdot(0,2 + 1,5\cdot i))\f$
 */

class GraphRenderer{
    /**
     * A struct to define textproperties to save text in an other way
     */
    struct TextProps {
        std::string kmer; ///< string we want draw
        sf::Color col; ///< textcolor we set
        vector<int> pos; ///< position of the text
        int charSize; ///< size of the Charakter we draw
    };
    protected:
        std::vector<FuncArrowShape> consistentEdges; ///< vector of FuncArrowShapes which represent consistent edges
        std::vector<FuncArrowShape> selectedEdges; ///< vector of FuncArrowShapes which represent selected edges
        std::vector<ArrowShape> rowArrows; ///< vector of ArrowShapes which get drawed only in a row
        std::vector<std::vector<sf::RectangleShape>> rects; ///< vector of vector of rectangles where a rectangle represent a node (with analogue indices)
        std::vector<TextProps> txt; ///< vector of textproperties to draw Node strings
        sf::Vector2i hoverPosition; ///< a index vector for the actual hovered Node
        sf::Vector2i clickPosition; ///< a index vector for the actual clicked Node
        sf::Color colorOfClickedNode; ///< the color of the Node rectangle, which is in the position of the clickPosition
        unsigned maxNodesPerRow; ///< an upper bound for the row lengths
        unsigned maxSequences; ///< an upper boudn for the column lengths
        int sizeConstant; ///< a constant which defines the scale of the visuals
        float offset; ///< a constant which make a offset on the upper horizontal
        float moveConstant; ///< a (upper bound) constant which is used to scroll in terms of computer speed
        vector<float> direction; ///< a vector of 2 floats which saves the scrolled way of the view
        vector<double> animationSpeed; ///< a vector of doubles for the speed during the animation

    private:

        /**
         * a function which calculate the speed during the animation
         *
         * \param size is the numer of steps we want during the animation
         */

        void calcAnimationSpeed(unsigned int size);

        unsigned int currentAnimationStep;
        std::vector<sf::Vector2f> new_coord;
        vector<DrawNode> old_nodes;

	public:
        bool animate;

        bool nodeHovered; ///< true, if a node is hovered
        bool nodeClicked; ///< true, if a node is clicked
        bool edgeHovered; ///< true, if a edge is hovered
        int hoveredEdgeIndex; ///< the index of the hovered edge
        sf::View actualView; ///< a View which we use as main-"view"
        sf::View defaultView; ///< a View to reset our actualView

        /**
         * The Complete Constructor, which initialize the visuals in the referenced window.
         *
         * \param window a renderWindow what gets the drawed shapes and texts
         * \param nodeList a vector of Nodes we use for the game (shape inits)
         * \param edgeList a vector of Edges we use for the game (state inits)
         */

        GraphRenderer(sf::RenderWindow& window, Gamemaster& gamemaster, float xoffset);

        /**
         * The standard constructor, which do nothing.
         */

        GraphRenderer();

        /**
         * a function which draw the shapes of the class in the argument window
         *
         * \param window a renderWindow what gets the drawed shapes and texts
         */

        void render(sf::RenderWindow& window, vector<DrawNode>& Nodes, vector<Node>& nodeList);

        /**
         * a function which handles events that are given by argument and make
         * adjustments in the argument window
         *
         * \param window a renderWindow which is needed to get informations (i.e. mousepos)
         * \param event a Event which will describe the event that will happen
         * \param nodeList a vector of Nodes which is needed for a few methods
         * \param mouse_pos the current mouse position
         */

        void eventHandler(const sf::Event event, sf::RenderWindow& window, vector<Node>& nodeList, 
                          Gamemaster& gamemaster, const sf::Vector2f& mouse_pos);

        /**
         * a function which display the current score of the game
         * \param window a renderWindow what gets the new score
         * \param gamestate is the current state of the game
         */        

        void display_score(sf::RenderWindow& window, const state& gamestate);
        void updateDrawNode(sf::RenderWindow& window, vector<Node>& nodeList, vector<DrawNode>& Nodes, 
                            const state& GameState, Button& menuButton);

        /**
         * a function which set an upper bound for the scroll speed via the arrow buttons.
         *
         * \param delta a float which gets the upper bound
         */

        void update(float delta);

        /**
         * a function which initialize the shapes and texts in terms of the NodeList. this is only
         * called in the constructor.
         *
         * \param nodeList a vector of Nodes which we want to draw as rectangles with text
         */

        void initShapes(const vector<DrawNode>& Nodes, const vector<Node>& nodeList);
        void setCoords(const vector<DrawNode>& Nodes, const vector<Node>& nodeList);

        /**
         * a function which draw all shapes in their current state
         *
         * \param window a renderWindow which gets the drawed shapes
         */

        void drawShape(sf::RenderWindow& window);

        /**
         * a function which draw all texts in their current state
         *
         * \param window a renderWindow which gets the drawed texts
         */

        void drawText(sf::RenderWindow& window);

        /**
         * a function which manipulate the view with a choosed direction (look in .cc file for more)
         *
         * \param dir an integer which describes the direction that we have chosen
         */

        void moveWindow(int dir);

        /**
         * a function which show consistent edges of a clicked node
         *
         * \param nodeList a vector of Nodes we need to get the adjacent nodes
         * \param pos a position vector we use to get the clicked node
         */

        void showEdges(vector<Node>& nodeList, vector<DrawNode>& Nodes, sf::Vector2f pos, state& gameState);

        /**
         * a function which select a clicked edge (in the state and in visuals)
         */

        void selectEdge(vector<Node>& nodeList, Gamemaster& gamemaster);

        /**
         * a function which highlight a hovered node
         *
         * \param pos a position vector we use to get the hovered node
         */

        void hoverNode(vector<Node>& nodeList, vector<DrawNode>& Nodes, sf::Vector2f pos);

        /**
         * a function which remove the highlight of the hovered node
         */

        void deHoverNode();

        /**
         * a function which highlight a hovered edge
         *
         * \param pos a position vector we use to get the hovered edge
         */

        void hoverEdge(sf::Vector2f pos);

        /**
         * a function which remove the highlight of the hovered edge
         */

        void deHoverEdge();

        /**
         * a function which highlight a clicked node
         *
         * \param pos a position vector we use to get the clicked node
         */

        void clickNode(vector<Node>& nodeList, vector<DrawNode>& Nodes, sf::Vector2f pos);

        /**
         * a function which remove the highlight of the clicked node
         */

        void deClickNode();

        /**
         * a function which returns a node in terms of a position and the 
         * nodeList we use for the game
         *
         * \param pos a position vector we use to get the Node indices
         * \param nodeList a vector of Nodes we use to compare them indices with the argument indices
         * \return a Node which is the searched one in terms of Pos
         */

        Node* positionToNode(sf::Vector2f pos, vector<Node>& nodeList, vector<DrawNode>& Nodes);

        /**
         * a function which returns an possible node index vector in terms of a position
         *
         * \param pos a position vector we use to get the index vector
         * \return a vector2i which is a index vector for a node
         */

        sf::Vector2f positionToCoords(sf::Vector2f pos);

        /**
         * a function which check if the argument is the position of an edge
         *
         * \param a position vector we want to check
         */

        bool isPositionEdge(sf::Vector2f pos);

        /**
         * a function which check if the argument is the position of a node
         *
         * \param a position vector we want to check
         */

        bool isPositionNode(sf::Vector2f pos, vector<DrawNode>& Nodes, vector<Node>& nodeList);

        void animation(sf::RenderWindow& window, Gamemaster& gamemaster, vector<Node>& nodeList, Button& menuButton);
        std::vector<sf::Vector2f> calcNewNodeCoord(Gamemaster& gamemaster, vector<Node>& nodeList);
};

#endif //GraphRenderer_H_

