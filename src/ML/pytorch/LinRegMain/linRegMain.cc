#include <iostream>
#include "../../../alignment/State.h"
#include "../../SimpleAgent/Agent.h"
#include "../valueMLmodel.h"
#include <torch/torch.h>
#include <vector>
#include "../TrainingSet.h"

using std::vector;
using namespace std;

int main() {
    Graph g;
    g.readFastaFiles("../../../alignment/sequences.fa" , 3);

	// Start of linear Regression learning with RandomPolicy
    Agent agent(g, Policytype::rnd);
	//Creation of Episodes
    vector<Episode> episodes1;
    unsigned int numbEpisodes = 30;
    for (unsigned int i = 0; i < numbEpisodes; i++) {
        episodes1.push_back(agent.getEpisode());
    }
    //Creation of dataSet and valModel, "learning" by influencing learnedPolicy
    RLDataset dataSet1(episodes1);
    valueMLmodel valModel(g.getEdges().size());
    LearnedPolicy lpol(&valModel);
    
    
    
    lpol.vModel->learn(dataSet1, 100, 64, 0.1);
	
	//Start of linear Regression learning with LearnedPolicy by setting agent's policy to lpol
    //agent.setPolicy(&lpol);
    //TODO: Agent agent(g, Policytype::rl);
    TrainingSet TS(10, 100, 20, 64, 0.1);
    //TODO: TS.train(&agent);
    TS.train(&agent, lpol);
}
