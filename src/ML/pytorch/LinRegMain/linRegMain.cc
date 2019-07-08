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
	//Start of linear Regression learning with LearnedPolicy by setting agent's policy to lpol
    //agent.setPolicy(&lpol);
    Agent agent(g);
    TrainingSet TS(100, 50, 150, 64, 0.1);    
    //TODO: TS.train(&agent);
    TS.train(&agent);
}
