#ifndef AGENT_H
#define AGENT_H

#include "RandomPolicy.h"
#include "Policy.h"
#include "../../alignment/State.h"
#include <stdlib.h>
#include <random>
#include <chrono>
#include <utility>
#include <iostream>
#include <map>
#include "../../alignment/Graph.h"
#include "Episode.h"
#include <memory>

using std::vector;
enum Policytype {rnd, rl};
/** \brief This Agent class selects edges according to a policy.
*/


class Agent {
    public:

    
    //The beginning state for every Episode
    state s;
    std::unique_ptr<Policy> policy;
    Agent(){};
    Agent(Graph& g, Policytype pol) : s(g.getEdges()){
        switch(pol) {
            case rnd:
                policy = std::unique_ptr<Policy>(new RandomPolicy()); 
                break;
            case rl:
                break;

            default : 
                break;
        }
     }
    ~Agent(){};
    /** This function runs an episode. It relies on constState, policy and graph
     *  to calculate state-action pairs as well as score.
     * \return This function returns an episode
     */
    Episode getEpisode() {
        s.reset();
        Episode episode;
        unsigned int n = s.edges.size();
        vector <bool> action(n, false);
        episode.states.push_back(s.selectedSubset); 
        unsigned int counter = 0;
        std::pair <state*, unsigned int> stateAction = executePolicy(&s, policy.get());
        
       
        while (stateAction.first->hasEdge()) { ///< state needs boolean to determine whether a selectable edge exists
            episode.states.push_back(stateAction.first->selectedSubset);
            episode.actions.push_back(action);
            episode.actions.at(counter).at(stateAction.second)=true;
            counter++;
            stateAction = executePolicy(stateAction.first, policy.get());
        }
        
        episode.actions.push_back(action);
        episode.numbOfStates = counter + 1;
        stateAction.first->calculate_score();
        episode.score = stateAction.first->score;

        return episode;
    }

    /** The member executePolicy selects an edge in state s according to Policy p.
     * \param s Expects a state s as input parameter.
     * \param p Expects a policy p as input parameter.
     */                      
    std::pair <state*, unsigned int> executePolicy(state* s, Policy* p) {
   
        std::random_device rd;
        std::mt19937 gen(rd());
        std::vector <float> probActions = p->act(s);
        std::discrete_distribution<> dis(probActions.begin(), probActions.end());
        unsigned int edgeSelection = dis(gen);
        if (s->selectable[edgeSelection] == false) {
            edgeSelection = -1;
        }
        else {
            s->select(edgeSelection);
        }
        return std::make_pair(s,edgeSelection);
    }
};
#endif
