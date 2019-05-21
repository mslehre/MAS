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
    private:

     /** 
     * \param a is a Node
     * \param b is a Node
     * \return TRUE if a and b have the same indices
     */

    bool is_equal(Node& a, Node& b);

     /**
     * This function is recursive and continues a given path in a graph
     * \param path is the path found so far
     * \param graph is the graph (contains all nodes)
     */

    void find_path(std::vector<unsigned int>& path, Graph& graph);

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
   
    /** 
     * \param graph is a graph
     * calculate the score for a given graph
     */

    void calculate_score(Graph& graph);
	
	/** This function determines whether state has a selectable edge.
	 * \return Returns true if it has selectable edge and false otherwise.
	 */
	bool hasEdge();

};

#endif
