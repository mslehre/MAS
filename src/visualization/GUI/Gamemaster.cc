#include "../../SequenceSimulation/sequence.h"
#include "../colorlist.h"
#include "../colormap.h"
#include "Gamemaster.h"
#include <stdio.h>
#include <string>
#include <vector>

Gamemaster::Gamemaster(unsigned int k, unsigned int length, unsigned int number_of_sequences, double probability){
    simulate(number_of_sequences, length, probability);     
    GameGraph.readFastaFiles("sequences.fa", k);
    remove("sequences.fa");
    state statetemp(GameGraph);
    GameState = statetemp;

    //Initialize colomap
    vector<string> Kmers = giveKmers(GameGraph.getNodes());
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

Graph Gamemaster::get_GameGraph(){
    return GameGraph;
}

state Gamemaster::get_GameState(){
    return GameState;
}

std::vector<DrawNode> Gamemaster::get_GameNodes(){
    return GameNodes;
}

std::vector<std::string> Gamemaster::giveKmers(vector<Node>& nodeList) {
    vector<std::string> allKmers; 
    bool elementOf;
    for (unsigned int i = 0; i < nodeList.size(); i++) {
        elementOf = false;
        for (unsigned int j = 0; j < i; j++) {
            if (nodeList.at(i).kmer == nodeList.at(j).kmer) {
                elementOf = true;
                break;
            }
        }
        if (!elementOf)
            allKmers.push_back(nodeList.at(i).kmer);
    }
    return allKmers;
}
