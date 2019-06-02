#pragma once
#include "../SimpleAgent/Agent.h"

class MLAgent : public Agent {
    public:
        /** This valueMLmodel contains data required for prediction of
         * v_pi_(s) -for now- using linReg
         */
        valueMLmodel vModel; 
        // pointer to learned policy inherited from agent
};
