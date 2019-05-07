#ifndef RANDOM_AGENT_H
#define RANDOM_AGENT_H

#include "BaseAgent.h"
#include "../../alignment/State.h"
#include <stdlib.h>
#include <random>
#include <chrono>

/** \brief This RandomAgent class selects edges according to a policy.
*          The policy is to just choose a random edge out of the selectable ones
*/
class RandomAgent : public BaseAgent {
    public:
    RandomAgent(){};
    ~RandomAgent(){};
    /** The member policy selects selectable edges at random.
    */
    virtual void policy(state* s) const override {
        std::mt19937 gen(std::chrono::high_resolution_clock::now().time_since_epoch().count());
        bool hasEdge = true;
        while (hasEdge) {
            hasEdge = false;
            std::vector <int> selectableIndices;
            for (int j = 0; j < s->selectable.size(); j++) {
                if (s->selectable[j] == true) {
                    selectableIndices.push_back(j);
                    hasEdge = true;
                }
            }
            if (hasEdge == true) {
                std::uniform_int_distribution<> dis(0, selectableIndices.size() - 1);
                int d = selectableIndices[dis(gen)];
                s->select(d);
            }
        }
    }
};
#endif
