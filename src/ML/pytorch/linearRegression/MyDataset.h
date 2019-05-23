#pragma once
#include "../../../ReinforcementLearning/SimpleAgent/Agent.h"
class MyDataset : public torch::data::Dataset<MyDataset>
{
    private:
        torch::Tensor states, scores;

    public:
        /** 
         * \brief calculate states and scores for the dataset
         * \param numbEpisodes number of episodes
         * \param agent random agent
         */
        explicit MyDataset(unsigned numbEpisodes, RandomAgent& agent) {          
          
            vector<Episode> episodes;               // vector of episodes
            vector<vector<bool>> states;            // vector of states
            vector<vector<bool>> actions;           // vector of actions
            unsigned int score;                     // score of one episode
            unsigned int numbStates = 0;            // total number of states of all episodes

            for (unsigned int i = 0; i < numbEpisodes; i++) { // calculate the total number of all states of all episodes
                episodes.push_back(agent.getEpisode());
                numbStates+=episode.numbStates;    
            }

            unsigned int numbEdges = episodes.at(0).states.at(0).size();    // number of edges of one graph
                            
            statesAndActions = torch::zeros({numbStates,2*numbEdges});      ///< dataset of states and actions
            scores = torch::zeros({numbStates,1});                          ///< corresponding scores

            unsigned int counter = 0;
         
            // get the states, actions and scores of all episodes
            for (unsigned int i = 0; i < numbEpisodes; i++) {
                statesVector = episodes.at(i).states;
                actionsVector = episodes.at(i).actions;   
                score = episodes.at(i).score;
                // save the score for every episode
                for (unsigned int j = 0; j < statesVector.size(); j++) {
                    scores[counter] = score;
                    // save the states for every episode
                    for(unsigned int k = 0; k < numbEdges; k++) {
                    statesAndActions[counter][k] = statesVector.at(j).at(k);
                    }
                    // save the actions for every episode
                    for(unsigned int k = numbEdges; k < 2*numbEdges; k++) {
                    statesAndActions[counter][k] = actionsVector.at(j).at(k);
                    }
                    counter++;
                 }   
            }
        }

        torch::data::Example<> get(size_t index) override {
            return {statesAndActions[index], scores[index]};
        }

        torch::optional<size_t> size() const override {
            return statesAndActions.size(0);
        }
};