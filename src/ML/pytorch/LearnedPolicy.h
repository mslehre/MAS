#pragma once
#include "../SimpleAgent/Policy.h"
#include "../SimpleAgent/state.h"
#include "valueMLmodel.h"

class LearnedPolicy : public Policy {
    public:

        /** This function assigns valueEstimates to corresponding successor states
         *  \return returns a vector of valueEstimates(0 if not successor state)
         */
        vector<float> getPiGreedy(const vector<float> &valueEstimates) {
       
        }
                         
        vector<float> getPiSoftMax(const vector<float> &valueEstimates) {
              
        }     
};
