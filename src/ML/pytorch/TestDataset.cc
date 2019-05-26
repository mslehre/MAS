#include <iostream>
#include "../../alignment/State.h"
#include "../../alignment/Graph.h"
#include "../../alignment/Node.h"
#include "../../alignment/Edge.h"
#include "../../ReinforcementLearning/SimpleAgent/Agent.h"
#include "../../ReinforcementLearning/SimpleAgent/Policy.h"
#include "../../ReinforcementLearning/SimpleAgent/RandomPolicy.h"
#include "../../ReinforcementLearning/SimpleAgent/Episode.h"
#include "linearRegression/MyDataset.h"
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
    g.readFastaFiles("../../alignment/sequences.fa" , 2);
    state s(g.getEdges());
    RandomPolicy randP;
    Agent agent(s, g, &randP);
    Episode episode = agent.getEpisode();
    vector<vector<bool>> ausgabe = episode.states;
    for (unsigned int i = 0; i < ausgabe.size(); i++) {
        for (unsigned int j = 0; j < ausgabe.at(i).size(); j++) {
            cout << ausgabe.at(i).at(j);
        }
        cout << "next state: " << endl;
    }

    unsigned dim_state = 50;
    unsigned numberOfEpisodes = 5;
    // Create a new Net.
    auto net = std::make_shared<Net>(dim_state);

    // create random dataset
    auto data_set = MyDataset(numberOfEpisodes, agent).map(torch::data::transforms::Stack<>());

   //MyDataset(10, agent);
}
