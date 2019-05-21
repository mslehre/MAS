#ifndef POLICY_H
#define POLICY_H
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
    virtual std::vector <float> act(state* s) const = 0;
};
#endif
