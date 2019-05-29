#pragma once
#include "RLDataset.h"
#include <vector>

using std::vector;

class Theta {
    public:
    Theta();    ///< constructor
    /** This function calculates Theta from a
     *  RLDataset using linear regression.
     *  \return returns Theta as a vector <float>.
     */
    void calcTheta(RLDataset& data);
    vector<float> values;
};
