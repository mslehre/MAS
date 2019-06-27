#ifndef POLICY_H
#define POLICY_H
#include "../../alignment/State.h"

/** \brief This Policy class maps states to probabilities for an action.
*/
class Policy {
    public:

    Policy(){};
    ~Policy(){};

    /** Function act calculates probabilities for taking each action.
     * \param s Expects a state as input parameter.
     * \return Returns the vector of probabilities for each action.
     */
   // virtual std::vector <float> runPolicy(state* s) const = 0;
};
#endif
