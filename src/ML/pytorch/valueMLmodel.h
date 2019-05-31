#pragma once
#include "RLDataset.h"
#include <math.h>
#include <map.h>


class valueMLmodel {
    public:
        valueMLmodel(RLDataset& data) {
            this->data = data;
        }
        RLDataset data;
		/** This function initialise the RLDataset
		 */
        void setDataset(RLDataset& data) {
			this->data = data;
		}
  
         /** This function calculates Theta from a
          *  RLDataset using linear regression.
          *  \return returns Theta as a vector <float>.
          */
        void calcValueEstimates();
        vector<float> valueEstimates;
        vector<states*> correspondingStates;
        /** This function gives every state an index
         *  Its needed to efficiently find the valueEstimated of a given state 
         *\ return returns a map in which the index of the valueEstimated 
		    of a state is assigned by its binary Value
         */
        map <unsigned int, unsigned int> stateToIndex() {
          	map <unsigned int, unsigned int> index;
			
            for (unsigned int j = 0; j < correspondingStates.size();  j++) {
               	index[calculateBinaryValue(correspondingStates.at(i))] = i;
            }
            return index;
        }
        /** This function ideally would belong to state.
         *  It calculates the binary Value for a given state, which is needed for the calculation in stateToIndex
         *\return returns a binary Value for a given State
         */
        unsigned int calculateBinaryValue(state* s) {
             unsigned int binaryValue = 0;
             for (unsigned int i = s->selectedSubset.size(); i > 0; i--) {
                if (s->selectedSubset.at(i))
                binaryValue += pow(2,i);
             }
                return binaryValue;
        }
                
                
        
       

};
