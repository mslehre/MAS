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
    state();
    ~state();

    /**
     * Contains Edges as pairs of Nodes ('first' and 'second').
     * Nodes consist of Sequence index 'i', their index within that sequence 'j' and their k-mer string.
     */

    std::vector <Edge> edges;
    std::vector <bool> selectedSubset;    ///< Shows whether edge is selected in current subset (true = selected)
    std::vector <bool> selectable;    ///< Shows whether edge is selectable in the current subset (true = selectable)
    unsigned int score; ///< The score of the State
    
    /**
     * Selects edge i if selectable (does nothing otherwise)
     * \parm i is the index of the edge
     */

    void select(int i);

    /**
     * Checks whether edges in same sequence as edge i are selectable while maintaining consistency in current subset.
     * The first while loop goes through 'previous' edges until it finds one on a different starting sequence. 
     * It checks edges on the same sequence as edge i for crossings from right or left.
     * The second loop goes 'forwards' through edge vector doing exactly the same.
     * If it finds any edge crossing our selected ones, it sets selectable for that edge to false.
     * \parm i is the index of the edge
     */

    void updateSelectability(int i); 

    /** 
     * \param a is a Node
     * \param b is a Node
     * \return TRUE if a and b have the same indices
     */

    void find_path(std::vector<unsigned int>& path, std::vector<Edge>& edgesVector, Graph& graph);

    /** 
     * \param nodeList is the vector with all nodes
     * \param edgesVector is a vector with all edges
     */

    void calculate_score(Graph& graph);
};

#endif
