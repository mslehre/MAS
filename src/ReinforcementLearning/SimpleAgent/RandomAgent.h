#ifndef RANDOM_AGENT_H
#define RANDOM_AGENT_H

#include "BaseAgent.h"
#include "RandomPolicy.h"
#include "Policy.h"
#include "../../alignment/State.h"
#include <stdlib.h>
#include <random>
#include <chrono>
#include <utility>

/**TODO: Include score (maybe expected score) in history, make RandomAgent dependent on BaseAgent.
 *       The policy is supposed to map states to a vector of action probabilities in my view.
 *       How do we use history to find optimal strategy?
 */

/**TODO: Make RandomAgent dependent on BaseAgent, also initialise RandomAgent with state*
 */

/** \brief This RandomAgent class selects edges according to a policy.
*          The policy is to just choose a random edge out of the selectable ones
*/
class RandomAgent /*: public BaseAgent.h*/ {
    public:
    state* constState;
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
