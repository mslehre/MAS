#pragma once
#include <torch/torch.h>

// Define a new Module.
class LinearNet : torch::nn::Module {
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

