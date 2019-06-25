#ifndef EPISODE_H
#define EPISODE_H

#include <vector>

using std::vector;

class Episode{
    public:
        Episode(){};
        vector<vector<bool>> states;    ///< Vector of SelectedSubsets of states
        vector<vector<bool>> actions;    ///< Vector of Actions corresponding to states
        unsigned int score;    ///< Score of the states vector
        unsigned int numbOfStates;    ///< Number of States in states
 };
#endif
