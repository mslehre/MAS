#include "RLDataset.h"

RLDataset::RLDataset(vector<Episode>& episodes) { 
    this->episodes = episodes;
    numbEpisodes = episodes.size();  
	// Vector of states       
    vector<vector<bool>> s;   
    // vector of actions         
    vector<vector<bool>> a;
    // score of one episode           
    unsigned int score;      
    // total number of states of all episodes               
    unsigned int numbStates = 0;            

    // calculate the total number of all states of all episodes
    for (unsigned int i = 0; i < numbEpisodes; i++) { 
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
