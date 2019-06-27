#include "../SimpleAgent/Policy.h"
#include "valueMLmodel.h"

#ifndef LEARNEDPOLICY_H
#define LEARNEDPOLICY_H
using namespace std;

class LearnedPolicy : public Policy {
    public:
        LearnedPolicy(){};
        LearnedPolicy(unsigned int dimstate);
        ~LearnedPolicy(){};

        /** This valueMLmodel contains data required for prediction of
         * v_pi(s) -for now- using linReg
         */
        valueMLmodel vModel; 
        

        /** This function calculates valueEstimates of a state with vModel.
         *  The policy being created from vModel is thus just identity of v'_pi(s).
         *  \param s state whose valueEstimates are being calculated.
         *  \return Returns the vector of probabilities that is valueEstimates.
         */
        /*virtual std::vector <float> runPolicy(state* s) const override {
           return vModel->calcValueEstimates(s);
        };*/      
        std::vector <float> runPolicy(state* s) {
           return vModel.calcValueEstimates(s);
        };         
};
#endif
