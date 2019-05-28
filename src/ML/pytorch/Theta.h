#pragma once
#include "RLDataset.h"
#include <vector>

using std::vector;

class Theta {
    public:
    Theta(RLDataset& data);    ///< constructor
    /** This function calculates Theta from a
     *  RLDataset using linear regression.
     *  \return returns Theta as a vector <float>.
     */
    vector <float> calcTheta();

};
