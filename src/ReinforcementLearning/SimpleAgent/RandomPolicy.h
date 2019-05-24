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

    RandomPolicy() {};
    ~RandomPolicy() {};


    /** The function act returns probability vector of 0 if edge not selectable, 1/# of selectable edges otherwise.
     * \param s Expects a state s as input parameter.
     * \return Returns the probability vector.
     */
    virtual std::vector <float> act(state* s) const override {
        unsigned int n = s->edges.size();
        std::vector <float> probAct(n, 0);    // Initializes probAct with zeros
        int cTemp = std::count(s->selectable.begin(), s->selectable.end(), true);
        float counter = (float) cTemp;    // Counts the number of selectable edges.
        for (unsigned int i = 0; i < n; i++) {
            if (s->selectable[i] == true)
                probAct[i] = (float)(1/counter);    // Gives each selectable edge same probability
        }
        return probAct;
    }
};
#endif
