#pragma once
#inlcude "../SimpleAgent/Policy.h"
#include "../SimpleAgent/state.h"

class LearnedPolicy : public Policy {
    public:
        /** This vector changes some process in the act function to change
         *  Pi into Pi', vector<float> is a naive idea to change probabilities
         */
        vector<float> learnResults;

        /** This function uses theta to calculate v_pi(s, theta) and then
         *  return learnResults
         */
        vector<float> learnFromTheta(vector<float> theta);

        /* This function maps a state to a probability for each action.
         * Here it is influenced by learnResults.
         */
        vector<float> act(state* s);



};
