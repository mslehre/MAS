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

using std::vector;

/**TODO: Include score (maybe expected score) in history.
 *       The policy is supposed to map states to a vector of action probabilities in my view.
 */

/** \brief This Agent class selects edges according to a policy.
*/
class Agent {
    public:
    state* constState;
    Policy* policy;
    Graph graph;
    Agent(){};
    Agent(state* cs, Graph& g, Policy* pol){
        constState = cs;
        policy = pol;
        graph = g;
    }
    ~Agent(){};
    /** This vector consists of pairs of selectedSubset (i.e. a state) and the action taken in that state.
     */
    std::vector <std::pair<std::vector <bool>, unsigned int>> history;
    /** This function runs an episode. It relies on constState, policy and graph
     *  to calculate state-action pairs as well as score.
     * \return This function returns an episode
     */
    Episode getEpisode() {

        Episode episode;
        unsigned int n = constState->edges.size();
        vector <bool> action(n, false);
        episode.states.push_back(constState->selectedSubset); 
        unsigned int counter = 0;
        std::pair <state*, unsigned int> stateAction = executePolicy(constState, policy);
        
       
        while (stateAction.first->hasEdge()) { ///< state needs boolean to determine whether a selectable edge exists
            episode.states.push_back(stateAction.first->selectedSubset);
            episode.actions.push_back(action);
            episode.actions.at(counter).at(stateAction.second)=true;
            counter++;
            stateAction = executePolicy(stateAction.first, policy);
        }
        
        episode.actions.push_back(action);
        episode.numbOfStates = counter + 1;
        stateAction.first->calculate_score(graph);
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
        this->history.push_back(std::make_pair(s->selectedSubset, edgeSelection));
        return std::make_pair(s,edgeSelection);
    }
};
#endif
