#pragma once
#include "RLDataset.h"
#include <math.h>
#include <map.h>

class valueMLmodel {
    public:
        valueMLmodel(unsigned int dimstate) {
            this->dimstate = dimstate;
            auto linearNet = std::make_shared<LinearNet>(dimstate);
        };
        LinearNet linearNet;
        unsigned int dimstate;
        
        void learn(RLDataset& dataSet, unsigned int numberOfEpochs, unsigned int batch_size, float alpha) {
            auto data_set = dataSet.map(torch::data::transforms::Stack<>());
            // create a multi-threaded data loader for the MNIST dataset.
            auto data_loader = torch::data::make_data_loader<torch::data::samplers::SequentialSampler>(std::move(data_set), /*batch size=*/batch_size);
            // instantiate an SGD optimization algorithm to update our LinearNet's parameters.
            torch::optim::SGD optimizer(linearNet->parameters(), /*lr=*/alpha);
            for (size_t epoch = 1; epoch <= numberOfEpochs; ++epoch) {
                torch::Tensor loss;
                // Iterate the data loader to yield batches from the dataset.
                for (auto& batch : *data_loader) {
                    // Reset gradients.
                    optimizer.zero_grad();
                    // Execute the model on the input data.
                    torch::Tensor prediction = linearNet->forward(batch.data);
                    // Compute a loss value to judge the prediction of our model.
                    loss = torch::mse_loss(prediction, batch.target);
                    // Compute gradients of the loss w.r.t. the parameters of our model.
                    loss.backward();
                    // Update the parameters based on the calculated gradients.
                    optimizer.step();
                    // Output the loss and checkpoint every 100 batches
                 }
                 std::cout << "Epoch: " << epoch << " | Loss: " << loss.item<float>() << std::endl;
            }
       };
            
            
        vector<float> calcValueEstimates(state* s) {
            vector<bool> index = s->calcSuccessorStates();
            torch::Tensor succStates = vectorToTensor(s->successorStates);
            torch::Tensor pred = linearNet->forward(succStates);
            vector<float> tempPrediction = tensorToVector(pred);
            vector<float> prediction;
            unsigned int counter = 0;
            for (unsigned int i = 0; i < dimstate; i++) {
                if (index.at(i)) {
                    prediction.push_back(tempPrediction.at(counter));
                    counter++;
                } else {
                    prediction.push_back(0);
                }
            }                                        
            return prediction;                              
        };

        torch::Tensor vectorToTensor(vector<vector<bool>> vec) {
            torch::Tensor tens = torch::zeros({vec.at(0).size(), dimstate});
            for (unsigned int i = 0; i < vec.size(); i++){
                for (unsigned int j = 0; j < vec.at(i).size(); j++) {
                    tens[i][j] = (float)vec.at(i).at(j);
                }
            }
            return tens;
        };


        vector<float> tensorToVector(torch::Tensor tens) {
            for (unsigned int i = 0; i < tens
              








