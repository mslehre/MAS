#ifndef RANDOM_POLICY_H
#define RANDOM_POLICY_H

#include "Policy.h"
#include "../../alignment/State.h"
#include <stdlib.h>
#include <random>
#include <chrono>
#include <utility>

/** \brief This RandomPolicy can select edges at random.
 */
class RandomPolicy : public Policy {
    public:
    RandomPolicy(){};
    ~RandomPolicy(){};
    /** The member act selects an edge at random.
     * \param s Expects a state s as input parameter.
     * \return Returns the index of selected edge.
     */
    virtual unsigned int act(state* s) const override {
        std::mt19937 gen(std::chrono::high_resolution_clock::now().time_since_epoch().count());
        std::vector <int> selectableIndices;
        bool hasEdge = false;
        for (unsigned int j = 0; j < s->selectable.size(); j++) {
            if (s->selectable[j] == true) {
                selectableIndices.push_back(j);
                hasEdge = true;
            }
        }
        if (hasEdge == true) {
            std::uniform_int_distribution<> dis(0, selectableIndices.size() - 1);
            unsigned int edgeIndex = selectableIndices[dis(gen)];
            s->select(edgeIndex);    ///<The select in the act function is for tests ONLY
            return edgeIndex;
        }
        else {
            return -1;
        }
    }
};
#endif
