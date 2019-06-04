#pragma once
#include "../SimpleAgent/Policy.h"
#include "../../alignment/State.h"
#include "valueMLmodel.h"


class LearnedPolicy : public Policy {
    public:
        LearnedPolicy(){};
        /** This valueMLmodel contains data required for prediction of
         * v_pi_(s) -for now- using linReg
         */
        valueMLmodel* vModel; 

        virtual std::vector <float> runPolicy(state* s) const override {
           return vModel->calcValueEstimates(s);  
        };                
        /*vector<float> getPiSoftMax(const vector<float> &valueEstimates) {
              
        }*/     
};
