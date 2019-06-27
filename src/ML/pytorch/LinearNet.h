#ifndef LINEARNET_H
#define LINEARNET_H

#include <iostream>
#include <torch/torch.h>

/** \brief This class defines a new Module */
class LinearNet : public torch::nn::Module {
    public:

        LinearNet(){};

        LinearNet(unsigned ds) : dim_state(ds) {
            // Construct and register a Linear submodule
            lin_mod = register_module("fc", torch::nn::Linear(dim_state, 1));
            for (auto& p : this->parameters()) {
                torch::nn::init::constant_(p, 0.5);
                //p.uniform_(0,0);
            }
        }

        // Implement the Net's algorithm.
        torch::Tensor forward(torch::Tensor& x) {
            return lin_mod->forward(x.reshape({x.size(0), dim_state}));
        }

   	    // Use one of many "standard library" modules.
        unsigned dim_state;
        torch::nn::Linear lin_mod{nullptr};
};
#endif
