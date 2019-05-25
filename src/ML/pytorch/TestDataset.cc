#include <iostream>
#include "../../alignment/State.h"
#include "../../alignment/Graph.h"
#include "../../alignment/Node.h"
#include "../../alignment/Edge.h"
#include "../../ReinforcementLearning/SimpleAgent/Agent.h"
#include "../../ReinforcementLearning/SimpleAgent/Policy.h"
#include "../../ReinforcementLearning/SimpleAgent/RandomPolicy.h"
#include "../../ReinforcementLearning/SimpleAgent/Episode.h"
#include "linearRegression/MyDataset.h"

using namespace std;

int main() {
  //Following is just a Test

    // example create object from class Graph
    Graph g;
    g.readFastaFiles("../../alignment/sequences.fa" , 2);
    state s(g.getEdges());
    RandomPolicy randP;
    Agent agent(s, g, &randP);
    Episode episode = agent.getEpisode();
    vector<vector<bool>> ausgabe = episode.states;
    for (unsigned int i = 0; i < ausgabe.size(); i++) {
        for (unsigned int j = 0; j < ausgabe.at(i).size(); j++) {
            cout << ausgabe.at(i).at(j);
        }
        cout << "next state: " << endl;
    }
   //MyDataset(10, agent);
}
