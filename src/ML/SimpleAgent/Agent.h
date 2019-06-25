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
#include "../pytorch/LearnedPolicy.h"
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
 
    state s0;    ///< The initial state where every episode starts.
    Policy* policy;    ///< Pointer to the Policy that Agent currently uses.

    Agent();    ///< Default constructor
    ~Agent(){};    ///< Default destructor
    
    /** Constructor with Graph and policy being set. 
     *  \param g Graph being used to create state
     *  \param pol Type of Policy, either Random or Learned
     */
    Agent(Graph& g, Policytype pol) : s0(g.getEdges()) {
        switch(pol) {
            case rnd:
                policy = new RandomPolicy();
                break;
            case rl:
                policy = new LearnedPolicy();
                break;
            default: 
                break;
        }
    }

    /** This function runs an episode. It relies on s and policy
     *  to calculate state-action pairs as well as score.
     * \return This function returns an episode
     */
    Episode getEpisode();

    /** The member executePolicy selects an edge in state s according to Policy p.
     * \param s Expects a state s as input parameter.
     * \param p Expects a policy p as input parameter.
     * \return Returns a state action pair.
     */
    std::pair <state*, unsigned int> executePolicy(state* s, Policy* p);

    void setPolicy(Policy *pol);    ///< Sets Policy.
};
#endif
