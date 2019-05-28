#ifndef EPISODE_H
#define EPISODE_H
#include <vector>

using std::vector;

class Episode{
    public:
        Episode(){};
        vector<vector<bool>> states;
        vector<vector<bool>> actions;
        unsigned int score;
        unsigned int numbOfStates;
 };
#endif
