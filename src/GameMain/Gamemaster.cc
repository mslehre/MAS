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

Graph Gamemaster::getGameGraph(){
    return GameGraph;
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

void Gamemaster::makeGame(const unsigned int& k, const unsigned int& length, const unsigned int& number_of_sequences, const unsigned int& probability){
    simulate(number_of_sequences, length, probability); 
    GameGraph.resetGraph();
    GameGraph.readFastaFiles("sequences.fa", k);
    remove("sequences.fa");
    state statetemp(GameGraph);
    GameState = statetemp;

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

