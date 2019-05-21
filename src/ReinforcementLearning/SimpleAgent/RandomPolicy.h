#ifndef RANDOM_POLICY_H
#define RANDOM_POLICY_H

#include "Policy.h"
#include "../../alignment/State.h"
#include <stdlib.h>
#include <random>
#include <chrono>
#include <utility>

/** \brief This RandomPolicy promotes random selection of edges.
 */
class RandomPolicy : public Policy {
    public:
    RandomPolicy(){};
    ~RandomPolicy(){};
    /** The function act returns probability vector of 0 if edge not selectable, 1/# of selectable edges otherwise.
     * \param s Expects a state s as input parameter.
     * \return Returns the probability vector.
     */
    virtual std::vector <float> act(state* s) const override {
        unsigned int n = s->edges.size();
        std::vector <float> probAct(n, 0.0);
        int counter = std::count(s->selectable.begin(), s->selectable.end(), true);
        for (int i = 0; i < n; i++) {
            if (s->selectable[i] == true)
                probAct[i] = 1/counter;
        }
        return probAct;
        /*
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
        }*/
    }
};
#endif
