#include "../SimpleAgent/Agent.h"
#include <torch/torch.h>
#include <iostream>
#include "../SimpleAgent/Episode.h"
using std::vector;

#ifndef RLDATASET_H
#define RLDATASET_H

class RLDataset : public torch::data::Dataset<RLDataset>
{
    private:
        torch::Tensor states, scores, actions;

    public:
        unsigned int numbEpisodes;
        vector<Episode> episodes;               // vector of episodes
        /** 
         * \brief calculate states and scores for the dataset
         * \param numbEpisodes number of episodes
         * \param agent random agent
         */
        RLDataset(vector<Episode>& episodes);
        RLDataset(){};

        void set(vector<Episode>& episodes);
        
        torch::data::Example<> get(size_t index) override {
            return {states[index], scores[index]};
        }

        torch::optional<size_t> size() const override {
            return states.size(0);
        }
};
#endif
