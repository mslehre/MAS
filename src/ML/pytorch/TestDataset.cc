#include <iostream>
#include "../../alignment/State.h"
#include "../../alignment/Graph.h"
#include "../../alignment/Node.h"
#include "../../alignment/Edge.h"
#include "../SimpleAgent/Agent.h"
#include "../SimpleAgent/Policy.h"
#include "../SimpleAgent/RandomPolicy.h"
#include "../SimpleAgent/Episode.h"
#include "RLDataset.h"
#include <torch/torch.h>
using namespace std;

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


int main() {
    //Following is just a Test

    // example create object from class Graph
    Graph g;
    g.readFastaFiles("../../alignment/sequences.fa" , 3);
    Agent agent(g, Policytype::rnd);
    Episode episode = agent.getEpisode();
    vector<vector<bool>> output = episode.states;
    for (unsigned int i = 0; i < output.size(); i++) {
        for (unsigned int j = 0; j < output.at(i).size(); j++) {
            cout << output.at(i).at(j);
        }
        cout << " next state: " << endl;
    }

    unsigned dim_state = 50;
    unsigned numberOfEpisodes = 10;
    // create a new Net.
    auto net = std::make_shared<Net>(dim_state);
    // create random dataset
    auto data_set = RLDataset(numberOfEpisodes, agent).map(torch::data::transforms::Stack<>());
    // create a multi-threaded data loader for the MNIST dataset.
    auto data_loader = torch::data::make_data_loader<torch::data::samplers::SequentialSampler>(std::move(data_set), /*batch size=*/2);
    // instantiate an SGD optimization algorithm to update our Net's parameters.
    torch::optim::SGD optimizer(net->parameters(), /*lr=*/0.1);

    // iterate the data loader to printout batches from the dataset.
    for (torch::data::Example<>& batch : *data_loader) {
        cout << "Batch size: " << batch.data.size(0) << ": ";
            cout << batch.data << endl;
    } 
}
