#include <iostream>
#include "RLDataset.h"
#include <math.h>
#include "LinearNet.h"
#include <torch/torch.h>

#ifndef VALUEMLMODEL_H
#define VALUEMLMODEL_H

using std::vector;

class valueMLmodel {
    public:
        valueMLmodel();
        valueMLmodel(unsigned int dimstate);

        torch::Tensor tensState;
        
        std::shared_ptr<LinearNet> linearNet;
        unsigned int dimstate;    ///< Number of possible edges in state.

        /** "Der lernt halt. Also... passt die Werte des Nets an" - Moritz L. Grillo, 21.06.2019
         */  
        void learn(RLDataset& dataSet, unsigned int numberOfEpochs, unsigned int batch_size, float alpha);
        
		/** This function calculates Value Estimates for learning of learnedPolicy.
		 *  \param s State that we use to calculate ValueEstimates using its successor States.
		 *  \return Returns prediction values for creation of learnedPolicy.
		 */             
        vector<float> calcValueEstimates(state* s);

        torch::Tensor vectorToTensor(vector<vector<bool>>& vec);    ///< Takes a vector makes a tensor.

        vector<float> tensorToVector(torch::Tensor& tens);    ///< Takes a tensor makes a vector.
};
#endif
