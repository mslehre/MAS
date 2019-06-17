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
    LearnedPolicy lpol;
    
    lpol.setVModel(&valModel); 
    
    lpol.vModel->learn(dataSet1, 100, 64, 0.1);
	
	//Start of linear Regression learning with LearnedPolicy by setting agent's policy to lpol
    agent.setPolicy(&lpol);
	
    vector<Episode> episodes2;

    for (unsigned int i = 0; i < numbEpisodes; i++) {
        episodes2.push_back(agent.getEpisode());
		cout << i << endl;
    }
	
    RLDataset dataSet2(episodes2);
    lpol.vModel->learn(dataSet2, 100, 64, 0.1);

	vector<Episode> episodes3;

    for (unsigned int i = 0; i < numbEpisodes; i++) {
        episodes3.push_back(agent.getEpisode());
		cout << i << endl;
    }
	
    RLDataset dataSet3(episodes3);
    lpol.vModel->learn(dataSet3, 100, 64, 0.1);

	vector<Episode> episodes4;

    for (unsigned int i = 0; i < numbEpisodes; i++) {
        episodes4.push_back(agent.getEpisode());
		cout << i << endl;
    }
	
    RLDataset dataSet4(episodes4);
    lpol.vModel->learn(dataSet4, 100, 64, 0.1);
}
