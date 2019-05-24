#ifndef EPISODE_H
#define EPISODE_H
#include <vector>

using std::vector;

class Episode {
    public:

        Episode() {};
        ~Episode() {};


        /** Contains selectedSubsets where an additional edge is selected
         *  in every following selectedSubset.
         */
        vector<vector<bool>> states;
        /** Contains series of boolean vectors where the index that is true
         *  is the index of the edge that has been selected to get from
         *  the previous state (i-1) to the current state (i). 
         *  i.e.: states[0]->actions[0]->states[1]
         */
        vector<vector<bool>> actions;
        unsigned int score;    ///< Contains score of this episode (score of final state).
        unsigned int numbOfStates;    ///< Number of States ( = number of selected edges)
 };
#endif
