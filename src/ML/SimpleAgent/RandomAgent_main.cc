#include "../../alignment/State.h"
#include "../../alignment/Graph.h"
#include "../../alignment/Node.h"
#include "../../alignment/Edge.h"
#include "Agent.h"
#include "Policy.h"
#include "RandomPolicy.h"
#include "Episode.h"

using namespace std;

int main(){
    //Following is just a Test

    // example create object from class Graph
    Graph g;
    g.readFastaFiles("../../alignment/sequences.fa" , 2);
    Agent agent(g, Policytype::rnd);
    Episode episode = agent.getEpisode();
    vector<vector<bool>> output = episode.states;
    for (unsigned int i = 0; i < output.size(); i++) {
        for (unsigned int j = 0; j < output.at(i).size(); j++) {
            cout << output.at(i).at(j);
        }
        cout << " next state: " << endl;
    }
}

