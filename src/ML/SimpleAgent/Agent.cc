#include "Agent.h"
using namespace std;

Agent::Agent(){}

Episode Agent::getEpisode() {
    // Reset s0 so that it is the beginning state.
    s0.reset();
    Episode episode;
    // Get the size of the states
    unsigned int n = s0.edges.size();
    // Initialise a boolean vector for an action 
    vector <bool> action(n, false);
    // Pushes the initial state at the beginning of an episode. 
    //episode.states.push_back(s0.selectedSubset); 
    unsigned int counter = 0;
    // The agent chooses the first action and first successor state with a given policy.
    //std::pair <state*, unsigned int> stateAction = executePolicy(&s0, lpolicy);
    state* s0prime = &s0; 
    std::pair <state*, unsigned int> stateAction = std::make_pair(s0prime, 0); 
    // While the actual state has a selectable edge.
    while (stateAction.first->hasEdge()) { 
        // Pushes the actual state in the states vector.
        episode.states.push_back(stateAction.first->selectedSubset);
        // Pushes an "empty" action in the action vector.
        episode.actions.push_back(action);
        // Sets the corresponding entry of the choosen edge true in the pushed action boolean vector
        episode.actions.at(counter).at(stateAction.second)=true;
        counter++;
        // Choose an action and a successor state for the actual state with a given policy.
        stateAction = executePolicy(stateAction.first, lpolicy);
            
    }
    // Pushes an empty action so that every episode has the same number of states and actions
    episode.actions.push_back(action);
    // Set the number of States
    episode.numbOfStates = counter + 1;
    // Calculate the score for the terminal state,
    stateAction.first->calculate_score();
    // which is the score for the whole episode.
    episode.score = stateAction.first->score;
    
    return episode;
}

std::pair <state*, unsigned int> Agent::executePolicy(state* s, LearnedPolicy& p) {
    // Create random device.
    std::random_device rd;
    std::mt19937 gen(rd());
    // Get the value estimates for every action of a given state dependant on the policy
    std::vector <float> probActions = p.runPolicy(s);
    // Create a distribution dependant on the value estimates
    std::discrete_distribution<> dis(probActions.begin(), probActions.end());
    // Randomly choose an action with probabalities of distribution
    unsigned int edgeSelection = dis(gen);
    if (s->selectable[edgeSelection] == false) {
        edgeSelection = -1;
    } else {
        s->select(edgeSelection);
    }
    // Returns a pair of the successor state and the action chosen to get there
    return std::make_pair(s, edgeSelection);
}
 
