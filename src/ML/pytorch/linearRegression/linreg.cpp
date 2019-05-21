#include <torch/torch.h>
#include <random>
#include "MyDataset.h"
#include <iostream>

//Define a new Module.
struct Net : torch::nn::Module {
    Net(unsigned ds) : dim_state(ds) {
        // Construct and register a Linear submodule
        lin_mod = register_module("fc", torch::nn::Linear(dim_state, 1));
    }

    // Implement the Net's algorithm.
    torch::Tensor forward(torch::Tensor x) {
        return lin_mod->forward(x.reshape({x.size(0), dim_state}));
    }

    // Use one of many "standard library" modules.
    unsigned dim_state;
    torch::nn::Linear lin_mod{nullptr};
};

int main() {

    unsigned numberOfEpisodes = 100;
   
    // Create a new Net.
    auto net = std::make_shared<Net>(dim_state);

    //create random dataset
    auto data_set = MyDataset(numberOfEpisodes, agent).map(torch::data::transforms::Stack<>());

    // Create a multi-threaded data loader for the MNIST dataset.
    auto data_loader = torch::data::make_data_loader<torch::data::samplers::SequentialSampler>(std::move(data_set), /*batch size=*/64);

    // Instantiate an SGD optimization algorithm to update our Net's parameters.
    torch::optim::SGD optimizer(net->parameters(), /*lr=*/0.1);

    for (size_t epoch = 1; epoch <= 10; ++epoch) {
        size_t batch_index = 0;
        // Iterate the data loader to yield batches from the dataset.
        for (auto& batch : *data_loader) {
            // Reset gradients.
            optimizer.zero_grad();
            // Execute the model on the input data.
            torch::Tensor prediction = net->forward(batch.data);
            // Compute a loss value to judge the prediction of our model.
            torch::Tensor loss = torch::mse_loss(prediction, batch.target);
            // Compute gradients of the loss w.r.t. the parameters of our model.
            loss.backward();
            // Update the parameters based on the calculated gradients.
            optimizer.step();
            // Output the loss and checkpoint every 100 batches.
            if (++batch_index % 100 == 0) {
                std::cout << "Epoch: " << epoch << " | Batch: " << batch_index
                          << " | Loss: " << loss.item<float>() << std::endl;
                // Serialize your model periodically as a checkpoint.
                torch::save(net, "net.pt");
            }
        }
    }


}
