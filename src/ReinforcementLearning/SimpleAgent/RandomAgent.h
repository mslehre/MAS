#ifndef RANDOM_AGENT_H
#define RANDOM_AGENT_H

#include "BaseAgent.h"
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
        for (int j = 0; j < s->selectable.size(); j++) {
            if (s->selectable[j] == true) {
                selectableIndices.push_back(j);
                hasEdge = true;
            }
        }
        if (hasEdge == true) {
            std::uniform_int_distribution<> dis(0, selectableIndices.size() - 1);
            unsigned int edgeIndex = selectableIndices[dis(gen)];
            s->select(edgeIndex);    //For tests ONLY
            return edgeIndex;
        }
        else {
            return -1;
        }
    }
};

/** \brief This RandomAgent class selects edges according to a policy.
*          The policy is to just choose a random edge out of the selectable ones
*/
class RandomAgent : public RandomPolicy {
    public:
    RandomAgent(){};
    ~RandomAgent(){};
    /** This vector consists of pairs of selectedSubset (i.e. a state) and the action taken in that state.
     */
    std::vector <std::pair<std::vector <bool>, unsigned int>> history;
    /** The member executePolicy executes RandomPolicy.act and saves results in history.
     * \param s Expects a state s as input parameter.
     */
    virtual void executePolicy(state* s) {
    RandomPolicy randP;
    this->history.push_back(std::make_pair(s->selectedSubset,randP.act(s)));
    }
};
#endif
