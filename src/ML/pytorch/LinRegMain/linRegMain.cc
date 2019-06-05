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
#include <vector>

using std::vector;

int main() {
    Graph g;
    g.readFastaFiles("../../../alignment/sequences.fa" , 3);
    Agent agent(g, Policytype::rnd);
    vector<Episode> episodes1;
    unsigned int numbEpisodes = 100;
    for (unsigned int i = 0; i < numbEpisodes; i++) {
        episodes1.push_back(agent.getEpisode());
    }
    
    RLDataset dataSet1(episodes1);
    valueMLmodel valModel(g.getEdges().size());
    LearnedPolicy* lpol;
    
    lpol->setVModel(valModel);
    std::cout<<"hello"<<std::endl;
    
    
    lpol->vModel->learn(dataSet1, 100, 64, 0.1);
    agent.setPolicy(lpol);
    vector<Episode> episodes2;

    for (unsigned int i = 0; i < numbEpisodes; i++) {
        episodes2.push_back(agent.getEpisode());
    }
    RLDataset dataSet2(episodes2);
    lpol->vModel->learn(dataSet2, 100, 64, 0.1);
}
