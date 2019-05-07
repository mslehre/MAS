#ifndef BASE_AGENT_H
#define BASE_AGENT_H

#include "State.h"

/** \brief This BaseAgent class simply selects edges according to a policy.
*/
class BaseAgent{
    public:
    BaseAgent(){};
    ~BaseAgent(){};
    /** Member policy selects edges in order as long as they are selectable.
    */
    virtual void policy(state* s) const = 0; 
};
#endif
