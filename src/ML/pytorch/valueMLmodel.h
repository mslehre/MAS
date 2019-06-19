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

        std::shared_ptr<LinearNet> linearNet;
        unsigned int dimstate;
          
        void learn(RLDataset& dataSet, unsigned int numberOfEpochs, unsigned int batch_size, float alpha);
        
		/** \brief This function calculates Value Estimates for learning of learnedPolicy.
		 *  \param s State that we use to calculate ValueEstimates using its successor States.
		 *  \return Returns prediction values for creation of learnedPolicy.
		 */             
        vector<float> calcValueEstimates(state* s);

        torch::Tensor vectorToTensor(vector<vector<bool>>& vec);

        vector<float> tensorToVector(torch::Tensor& tens);
};
#endif
