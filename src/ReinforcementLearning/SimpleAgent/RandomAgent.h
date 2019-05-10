#ifndef RANDOM_AGENT_H
#define RANDOM_AGENT_H

#include "BaseAgent.h"
#include "../../alignment/State.h"
#include <stdlib.h>
#include <random>
#include <chrono>
#include <utility>

/** \brief This RandomAgent class selects edges according to a policy.
*          The policy is to just choose a random edge out of the selectable ones
*/
class RandomAgent : public BaseAgent {
    public:
    RandomAgent(){};
    ~RandomAgent(){};
    std::vector <std::pair<std::vector <bool>, unsigned int>> history;
    
    /** The member policy selects selectable edges at random.
    */
    virtual int act(state* s) const override {
        std::mt19937 gen(std::chrono::high_resolution_clock::now().time_since_epoch().count());
        std::vector <int> selectableIndices;
        bool hasEdge = false;
        for (int j = 0; j < s->selectable.size(); j++) {
            if (s->selectable[j] == true) {
                selectableIndices.push_back(j);
                hasEdge = true;
            }
        }
        if (hasEdge == true) {
            std::uniform_int_distribution<> dis(0, selectableIndices.size() - 1);
            unsigned int d = selectableIndices[dis(gen)];
            vector <bool> b1 = s->selectedSubset;
            std::pair <std::vector <bool>, unsigned int> p1= std::make_pair(b1, d);
            this->history.push_back(p1);
            s->select(d); //for tests ONLY!!
            return d;
        }
        else {
            return -1;
        }
    }
};
#endif
