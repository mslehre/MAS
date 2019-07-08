#include "valueMLmodel.h"

#ifndef POLICY_H
#define POLICY_H


using namespace std;

class Policy {
    public:
        Policy(){};
        Policy(unsigned int dimstate);
        ~Policy(){};

        /** This valueMLmodel contains data required for prediction of
         * v_pi(s) -for now- using linReg
         */
        valueMLmodel vModel; 
        
        /** This function calculates valueEstimates of a state with vModel.
         *  The policy being created from vModel is thus just identity of v'_pi(s).
         *  \param s state whose valueEstimates are being calculated.
         *  \return Returns the vector of probabilities that is valueEstimates.
         */
        std::vector <float> runPolicy(state* s) {
           return vModel.calcValueEstimates(s);
        };         
};
#endif
