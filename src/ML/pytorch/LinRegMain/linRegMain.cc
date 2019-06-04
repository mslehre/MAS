#include <iostream>
#include "../../../alignment/State.h"
#include "../../../alignment/Graph.h"
#include "../../../alignment/Node.h"
#include "../../../alignment/Edge.h"
#include "../../SimpleAgent/Agent.h"
#include "../../SimpleAgent/Policy.h"
#include "../../SimpleAgent/RandomPolicy.h"
#include "../../SimpleAgent/Episode.h"
#include "../valueMLmodel.h"
#include "../LearnedPolicy.h"
#include "../LinearNet.h"
#include "../RLDataset.h"

#include <torch/torch.h>



int main() {
    Graph g;
    g.readFastaFiles("../../alignment/sequences.fa" , 2);
    Agent agent(g, Policytype::rnd);
    vector<Episodes> episodes1;
    unsigned int numbEpisodes = 100;
    for (unsigned int i = 0; i < numbEpisodes; i++) {
        episodes1.push_back(agent.getEpisode());
    }
    RLDataset dataSet1(episodes1);
    valueMLmodel vModel(g.getEdges.size());
    LearnedPolicy lpol;
    lpol->vModel = &vModel;
    vModel.learn(dataSet, 100, 64, 0.1);
    agent.setPolicy(lpol);
    vector<Episodes> episodes2;
    unsigned int numbEpisodes = 100;
    for (unsigned int i = 0; i < numbEpisodes; i++) {
        episodes2.push_back(agent.getEpisode());
    }
    RLDataset dataSet2(episodes2);
    vModel.learn(dataSet2, 100, 64, 0.1);
}
