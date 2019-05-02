#ifndef RANDOM_AGENT_H
#define RANDOM_AGENT_H

#include "BaseAgent.h"

/** \brief This RandomAgent class selects edges according to a policy.
*          The policy is to just choose a random edge out of the selectable ones
*/
class RandomAgent : public BaseAgent {
    public:
    RandomAgent();
    ~RandomAgent();

    virtual void policy(state s) const override{
        bool selectableNotEmpty=true;
        while (selectableNotEmpty){
            for(int j=0;j<s.selectable.size();j++){
                if(s.selectable[j]==true){
                    selectableNotEmpty=true;
                    break;
                }
                else{
                selectableNotEmpty=false;
                }
            }
        std::default_random_engine generator;
        std::uniform_int_distribution<int> distribution(0,s.edges.size());
        int i = distribution(generator);
        if(s.selectable[i]==true){		
                s.select(i);
        }
    }
}
#endif
