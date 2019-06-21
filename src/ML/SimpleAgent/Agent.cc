#include "Agent.h"

Agent::Agent(){}

Episode Agent::getEpisode() {
    s.reset();
    Episode episode;
    unsigned int n = s.edges.size();
    vector <bool> action(n, false);
    episode.states.push_back(s.selectedSubset); 
    unsigned int counter = 0;
    std::pair <state*, unsigned int> stateAction = executePolicy(&s, policy);
        
    while (stateAction.first->hasEdge()) { ///< state needs boolean to determine whether a selectable edge exists
            episode.states.push_back(stateAction.first->selectedSubset);
            episode.actions.push_back(action);
            episode.actions.at(counter).at(stateAction.second)=true;
            counter++;
            stateAction = executePolicy(stateAction.first, policy);
    }
        
    episode.actions.push_back(action);
    episode.numbOfStates = counter + 1;
    stateAction.first->calculate_score();
    episode.score = stateAction.first->score;
    
    return episode;
}

std::pair <state*, unsigned int> Agent::executePolicy(state* s, Policy* p) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::vector <float> probActions = p->runPolicy(s);
    std::discrete_distribution<> dis(probActions.begin(), probActions.end());
    unsigned int edgeSelection = dis(gen);
    if (s->selectable[edgeSelection] == false) {
        edgeSelection = -1;
    } else {
        s->select(edgeSelection);
    }
    return std::make_pair(s,edgeSelection);
}

void Agent::setPolicy(Policy *pol) {
    this->policy = pol;
} 
