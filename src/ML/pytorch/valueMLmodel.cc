#include "valueMLmodel.h"
#include <typeinfo>
#include <math.h>



//default constructor
valueMLmodel::valueMLmodel(){}

//constructor
valueMLmodel::valueMLmodel(unsigned int ds) {
    dim = ds;
    linearNet = std::make_shared<LinearNet>(dim);
    tensState = torch::zeros({dim,dim});
}

void valueMLmodel::learn(RLDataset& dataSet, unsigned int numberOfEpochs, unsigned int batch_size, float alpha) {
    auto data_set = dataSet.map(torch::data::transforms::Stack<>());
    // create a multi-threaded data loader 
    auto data_loader = torch::data::make_data_loader<torch::data::samplers::SequentialSampler>(std::move(data_set), batch_size);
    // instantiate an SGD optimization algorithm to update our LinearNet's parameters.
    torch::optim::SGD optimizer(linearNet->parameters(), /*lr=*/alpha);
    torch::Tensor loss;
    torch::Tensor prediction;
    for (size_t epoch = 1; epoch <= numberOfEpochs; ++epoch) {
        // Iterate the data loader to yield batches from the dataset.
        for (auto& batch : *data_loader) {
            // Reset gradients.
            optimizer.zero_grad();
            // Execute the model on the input data.
            prediction = linearNet->forward(batch.data);
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
}

vector<float> valueMLmodel::calcValueEstimates(state* s) {
    /* Calculate all possible successor states of s.
       Returns a boolean vector corresponding to edges in such a way that true means an edge is selectable */
   
    for (unsigned int j = 0; j < dim; j++) {
        tensState[j] = (float) s->selectedSubset.at(j);
        
    }
    
    vector<unsigned int> index = s->calcSuccessorStates();
    torch::Tensor succsStates = torch::zeros({index.size(), dim});
    for (unsigned int i = 0; i < index.size(); i++) {
        for (unsigned int j = 0; j < dim; j++) {
                succsStates[i][j] = *tensState[j].data<float>();          
        }
        succsStates[i][index[i]] = 1;

    }
    torch::Tensor tensPred = linearNet->forward(succsStates);
    unsigned int sum = 0;
    // Softmax:
    for(unsigned int i = 0; i < index.size(); i++) {
        sum += exp((double) *tensPred[i].data<float>());
    }
    
    for(unsigned int i = 0; i < index.size(); i++) {
        tensPred[i] = exp((double) *tensPred[i].data<float>())/sum;
    }
    
    vector<float> prediction(dim,0);
    
    for (unsigned int i = 0; i < index.size(); i++) {
        prediction.at(index.at(i)) = *tensPred[i].data<float>();
     }
    return prediction;
}
