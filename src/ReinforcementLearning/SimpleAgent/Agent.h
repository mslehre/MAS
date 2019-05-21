#ifndef AGENT_H
#define AGENT_H

#include "RandomPolicy.h"
#include "Policy.h"
#include "../../alignment/State.h"
#include <stdlib.h>
#include <random>
#include <chrono>
#include <utility>
#include <iostream>

/**TODO: Include score (maybe expected score) in history.
 *       The policy is supposed to map states to a vector of action probabilities in my view.
 */

/** \brief This Agent class selects edges according to a policy.
*/
class Agent {
    public:
    state* constState;
    Agent(){};
    Agent(state* cs){
        constState = cs;
    }
    ~Agent(){};
    /** This vector consists of pairs of selectedSubset (i.e. a state) and the action taken in that state.
     */
    std::vector <std::pair<std::vector <bool>, unsigned int>> history;
    /** The member executePolicy selects an edge in state s according to Policy p.
     * \param s Expects a state s as input parameter.
     * \param p Expects a policy p as input parameter.
     */
    void executePolicy(state* s, Policy* p) {
        std::mt19937 gen(std::chrono::high_resolution_clock::now().time_since_epoch().count());
        std::vector <float> probActions = p->act(s);
        std::discrete_distribution<> dis(probActions.begin(), probActions.end());
        int edgeSelection = dis(gen);
        if (edgeSelection == 0) {
            std::cout << "done" << std::endl;
            edgeSelection = -1;
        }
        s->select(edgeSelection);
        this->history.push_back(std::make_pair(s->selectedSubset, edgeSelection));
    }
};
#endif
