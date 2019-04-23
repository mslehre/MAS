#ifndef STATE_H
#define STATE_H

#include <iostream>
#include <vector>
#include <array>

/** \brief state class encapsulates the current game state.
 *         It can output possible Actions and select them.
 */

class state{
    public:
    state(std::vector <std::array<int,3>> e);    ///< 1st entry is sequence nr, 2nd entry is node index in first seq, 3rd node index in 2nd seq
    state();
    ~state();
    std::vector <std::array<int,3>> edges; 
    std::vector <bool> selectedSubset;    ///< shows whether edge is selected in current subset (true=selected)
    std::vector <bool> selectable;    ///< shows whether edge is selectable in the current subset (true=selectable)
    void select(int i);    ///< selects edge i if selectable (does nothing otherwise)
    void possibleActions();    ///< updates state after selecting an edge
    bool checkConsistency(int i);   ///< checks whether edge is selectable while maintaining consistency in current subset
}; ///< This documentation is for a test
#endif

