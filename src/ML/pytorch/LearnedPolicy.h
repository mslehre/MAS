#include "../SimpleAgent/Policy.h"
#include "valueMLmodel.h"

#ifndef LEARNEDPOLICY_H
#define LEARNEDPOLICY_H

class LearnedPolicy : public Policy {
    public:
        LearnedPolicy();
        ~LearnedPolicy(){};
        /** This valueMLmodel contains data required for prediction of
         * v_pi_(s) -for now- using linReg
         */
        valueMLmodel* vModel; 
        
        void setVModel(valueMLmodel* valModel);

        virtual std::vector <float> runPolicy(state* s) const override {
           return vModel->calcValueEstimates(s);  
        };                   
};
#endif
