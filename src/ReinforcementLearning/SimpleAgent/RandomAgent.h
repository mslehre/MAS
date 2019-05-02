#ifndef RANDOM_AGENT_H
#define RANDOM_AGENT_H

#include "BaseAgent.h"
#include "State.h"
#include <stdlib.h>

/** \brief This RandomAgent class selects edges according to a policy.
*          The policy is to just choose a random edge out of the selectable ones
*/
class RandomAgent : public BaseAgent {
    public:
    RandomAgent(){};
    ~RandomAgent(){};
    /** This function does not work, enters an endless loop. Help.
    */
    virtual void policy(state s) const override{
        bool hasEdge=true;
        while (hasEdge==true){
            std::vector <int> selectableIndices;
            for(int j=0;j<s.selectable.size();j++){
                if(s.selectable[j]==true){
                    selectableIndices.push_back(j);
                }
            }
            if(selectableIndices.empty()==true){
                hasEdge=false;
            }
            int d = selectableIndices[std::rand() % selectableIndices.size()-1];
            if(s.selectable[d]==true){
                s.select(d);
            }
        }
    }
};
#endif
