#pragma once
#include "../SimpleAgent/Agent.h"
#include <torch/torch.h>
#include <iostream>
using std::vector;

class RLDataset : public torch::data::Dataset<RLDataset>
{
    private:
        torch::Tensor states, scores, actions;

    public:
        /** 
         * \brief calculate states and scores for the dataset
         * \param numbEpisodes number of episodes
         * \param agent random agent
         */
        explicit RLDataset(unsigned numbEpisodes, Agent& agent) {          

            vector<Episode> episodes;               // vector of episodes
            vector<vector<bool>> s;            // vector of states
            vector<vector<bool>> a;           // vector of actions
            unsigned int score;                     // score of one episode
            unsigned int numbStates = 0;            // total number of states of all episodes

            // calculate the total number of all states of all episodes
            for (unsigned int i = 0; i < numbEpisodes; i++) { 
                episodes.push_back(agent.getEpisode());
                numbStates = numbStates + episodes.at(i).numbOfStates;    
            }
            std::cout << "Number of states: " << numbStates << std::endl;
            unsigned int numbEdges = episodes.at(0).states.at(0).size();    // number of edges of one graph
            std::cout << "Number of edges: " << numbEdges << std::endl;                
            states = torch::zeros({numbStates, numbEdges});                ///< dataset of states
            actions = torch::zeros({numbStates, numbEdges});                ///< dataset of actions
            scores = torch::zeros({numbStates,1});                          ///< corresponding scores
           
            unsigned int counter = 0;
        
            // get the states, actions and scores of all episodes
            for (unsigned int i = 0; i < numbEpisodes; i++) {
                s = episodes.at(i).states;
                a = episodes.at(i).actions;   
                score = episodes.at(i).score;          
                // save the score for every episode
                for (unsigned int j = 0; j < s.size(); j++) {
                    scores[counter] = (float) score;             
                    // save the states and actions for every episode
                    for (unsigned int k = 0; k < numbEdges; k++) {
                        states[counter][k] = (float) s.at(j).at(k);
                        actions[counter][k] = (float) a.at(j).at(k);
                    }
                    counter++;
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
