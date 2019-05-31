#pragma once
#include "../SimpleAgent/Policy.h"
#include "../SimpleAgent/state.h"
#include "valueMLmodel.h"


class LearnedPolicy : public Policy {
    public:

        /** This function assigns valueEstimates to corresponding successor states
         *  \return returns a vector of valueEstimates(0 if not successor state)
         */
        vector<float> getPiGreedy(const state *s, const vector<float> &valueEstimates, vector<unsigned int> &index;) {
            vector<float> values;
            for (unsigned int i = 0; i < s->selectedSubset.size(); i++) {
                if (!s->selectedSubset.at(i) && s->selectable.at(i)) {
                    s->selectedSubset.at(i) = true;
                    values.push_back(valueEstimates.at(index.at(binaryValue(s->selectedSubset))));
                    s->selectedSubset.at(i) = false;
                } else {
                    values.push_back(0);
                }
            }
            return values;
        }
                
                
            
        vector<float> getPiSoftMax(const state *s, const vector<float> &valueEstimates, vector<unsigned int> index;);
        
};
