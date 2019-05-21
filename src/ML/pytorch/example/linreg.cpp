#include <torch/torch.h>
#include <random>
#include <iostream>

// Define a new Module.
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


//dataset of random states (0/1 vectors) with scores (floats in range [0,250])
class MyDataset : public torch::data::Dataset<MyDataset>
{
    private:
        torch::Tensor states, scores;

    public:
        explicit MyDataset(unsigned n, unsigned ds) {
            float state_mut_prob = 0.1;

            states = torch::zeros({n,ds}); //dataset of states
            scores = torch::zeros({n,1}); //corresponding scores

            std::default_random_engine gen;
            std::uniform_int_distribution<int> score_dist(0,250);
            std::uniform_real_distribution<double> prob_dist(0.0,1.0);

            //(state, score) dataset
            for (unsigned i = 0; i < n; i++){
                scores[i] = score_dist(gen);
                for (unsigned j = 0; j < ds; j++){
                    if (prob_dist(gen) < state_mut_prob)
                        states[i][j] = 1.0f;
                }
            }
        }

        torch::data::Example<> get(size_t index) override {
            return {states[index], scores[index]};
        }

        torch::optional<size_t> size() const override {
            return states.size(0);
        }
};


int main() {

    unsigned num = 64000;
    unsigned dim_state = 50;

    // Create a new Net.
    auto net = std::make_shared<Net>(dim_state);

    //create random dataset
    auto data_set = MyDataset(num, dim_state).map(torch::data::transforms::Stack<>());

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
