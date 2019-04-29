#ifndef STATE_H
#define STATE_H

#include <iostream>
#include <vector>
#include <array>

/** \brief This state class encapsulates the current game state.
*       It can output possible actions and select them.
*       
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
    void updateSelectability();    ///< if checkConsistensy returns false or if edge has been selected, sets selectable to false
    /**
    *Checks whether edge i is selectable (true) while maintaining consistency in current subset.
    *The first while loop checks edges on the same sequence that could cross edges[i] from the left.
    *The second loop checks for crossings from the right.
    *Returns true if edge selection maintains consistency, false if it does not.
    */
    bool checkConsistency(int i);
};
#endif

