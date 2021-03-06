#include "../SequenceSimulation/sequence.h"
#include "../visualization/colorlist.h"
#include "../visualization/colormap.h"
#include "Gamemaster.h"
#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm> 

using namespace std;

Gamemaster::Gamemaster(){};

void Gamemaster::makeGame(unsigned int k, unsigned int length, unsigned int number_of_sequences, double probability){
    simulate(number_of_sequences, length, probability);
    GameGraph.resetGraph();
    GameGraph.readFastaFiles("sequences.fa", k);
    remove("sequences.fa");
    state statetemp(GameGraph);
    GameState = statetemp;
	AgentState = statetemp;
	GameAgent.reset(new Agent(GameGraph));
	GameTS.reset(new TrainingSet(10, 30, 5, 64, 0.1));
	GameTS->train(GameAgent.get());
    //Initialize colomap
    vector<string> Kmers = getKmers(GameGraph.getNodes());
    colorlist colorExample(Kmers.size());
    vector<sf::Color> colors = colorExample.giveList();
    colormap mapExample(Kmers, colors);
    //initialize DrawNodes
    GameNodes.resize(GameGraph.getNodes().size());
    for (unsigned int i = 0; i < GameGraph.getNodes().size(); i++) {
        sf::Vector2f coords(GameGraph.getNodes().at(i).j, GameGraph.getNodes().at(i).i);
        GameNodes.at(i).coordinate = coords;
        GameNodes.at(i).col = mapExample.Map(GameGraph.getNodes().at(i).kmer);
    }
}

vector<string> Gamemaster::getKmers(vector<Node>& nodeList) {
    vector<string> allKmers(nodeList.size());
    for (unsigned int i = 0; i < nodeList.size(); i++) {
        allKmers[i] = nodeList.at(i).kmer;
    }
    sort(allKmers.begin(), allKmers.end());
    allKmers.erase(unique(allKmers.begin(), allKmers.end()), allKmers.end());
 
    return allKmers;
}
