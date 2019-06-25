#ifndef STATE_H
#define STATE_H

#include <iostream>
#include <vector>
#include <array>
#include "Node.h"
#include "Edge.h"
#include "Graph.h"

/** 
 * \brief This state class encapsulates the current game state.
 * It can output possible actions and select them.      
 */

class state{

    public:
    state(Graph& graph); ///< Constructor with a Graph
    state(std::vector <Edge> e); ///< Constructor with an Edge vector
    state();
    ~state();

    /**
     * Contains Edges as pairs of Nodes ('first' and 'second').
     * Nodes consist of Sequence index 'i', their index within that sequence 'j' and their k-mer string.
     */

    std::vector <Edge> edges;
    std::vector <bool> selectedSubset;    ///< Shows whether edge is selected in current subset (true = selected)
    std::vector <bool> selectable;    ///< Shows whether edge is selectable in the current subset (true = selectable)
    std::vector<unsigned int> selectedEdgeIndex; ///< contains indices from "edges" for all edges that are selected
    unsigned int score; ///< The score of the State
    vector<vector<bool>> successorStates; ///< The direct successor States
    
        
    /**
     * Selects edge i if selectable (does nothing otherwise)
     * \param i is the index of the edge
     */

    void select(int i);

    /**
     * Checks whether edges in same sequence as edge i are selectable while maintaining consistency in current subset.
     * The first while loop goes through 'previous' edges until it finds one on a different starting sequence. 
     * It checks edges on the same sequence as edge i for crossings from right or left.
     * The second loop goes 'forwards' through edge vector doing exactly the same.
     * If it finds any edge crossing our selected ones, it sets selectable for that edge to false.
     * \param i is the index of the edge
     */

    void updateSelectability(int i);

    /**
     * If edges can both be selected while maintaining consistency, return true.
     * Otherwise return false.
     * \param e is an Edge
     * \param f is an Edge
     */

    bool consistent(Edge& e, Edge& f);
	
	/** This function determines whether state has a selectable edge.
	 * \return Returns true if it has selectable edge and false otherwise.
	 */
	bool hasEdge();
    
    /** This function calculates the beginning state
    * \param e is vector of edges
    */
    void reset();

    /** This function determines all direct successor states.
     */
    vector<bool> calcSuccessorStates();

    /**
     * update the current score of the state: 
     * \f$ \textrm{score} = \sum_{c \in C} |c| (|c| - 1) / 2\f$, 
     * where C is the set of connected components and |c| is the number of nodes in connected 
     * component c.
     * This function requires that the edges are sorted increasingly by i.
     */
    void calculate_score();


};

#endif
