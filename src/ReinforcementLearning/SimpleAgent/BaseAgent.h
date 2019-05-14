#ifndef BASE_AGENT_H
#define BASE_AGENT_H

#include "../../alignment/State.h"

/** \brief This Policy class maps states to an action deterministically.
*/
class Policy {
    public:
    Policy(){};
    ~Policy(){};
    /** Member policy selects edges in order as long as they are selectable.
     * \param s Expects a state as input parameter.
     * \return Returns the index of edge that was selected according to policy.
     */
    virtual unsigned int act(state* s) const = 0; 
};

/** \brief This BaseAgent class executes Policy and saves the results.
*/
class BaseAgent : public Policy {
    public:
    BaseAgent(){};
    ~BaseAgent(){};
    /** This vector consists of pairs of selectedSubset (i.e. a state) and the action taken in that state.
     */
    std::vector <std::pair<std::vector <bool>, unsigned int>> history;
    /** The member executePolicy maps a state to an Action-State pair.
     * \param s Expects a state.
     * \return Returns vector of pairs of selectedSubset vector and the action taken in that state.
     */
    virtual void executePolicy(state* s);
};
#endif
