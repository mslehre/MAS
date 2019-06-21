#ifndef LEARNEDPOLICY_H
#define LEARNEDPOLICY_H

#include "../SimpleAgent/Policy.h"
#include "valueMLmodel.h"


class LearnedPolicy : public Policy {
    public:

        LearnedPolicy();
        ~LearnedPolicy(){};

        /** This valueMLmodel contains data required for prediction of
         * v_pi(s) -for now- using linReg
         */
        valueMLmodel* vModel; 
        
        void setVModel(valueMLmodel* valModel);    ///< Sets pointer to new valueMLmodel.

        /** This function calculates valueEstimates of a state with vModel.
         *  The policy being created from vModel is thus just identity of v'_pi(s).
         *  \param s state whose valueEstimates are being calculated.
         *  \return Returns the vector of probabilities that is valueEstimates.
         */
        virtual std::vector <float> runPolicy(state* s) const override {
           return vModel->calcValueEstimates(s);
        };                   
};
#endif
