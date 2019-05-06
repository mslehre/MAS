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
     * This function is recursive and find a path for a given set of edges and nodes
     * \param path is the path found so far
     * \param edgesVector are all possible edges
     * \param graph is the graph (contains all nodes)
     */

    void find_path(std::vector<unsigned int>& path, std::vector<Edge>& edgesVector, Graph& graph);

    /** 
     * \param graph is a graph
     * calculate the score for a given graph
     */

    void calculate_score(Graph& graph);
};

#endif
