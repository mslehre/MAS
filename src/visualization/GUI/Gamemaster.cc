#include <iostream>
#include "Gamemaster.h"
#include "../../SequenceSimulation/sequence.h"
#include "../colorlist.h"
#include "../colormap.h"
#include <stdio.h>

Gamemaster::Gamemaster(unsigned int k, unsigned int length, unsigned int number_of_sequences, double probability){
    simulate(number_of_sequences, length, probability);     
    GameGraph.readFastaFiles("sequences.fa", k);
    remove("sequences.fa");
    state statetemp(GameGraph);
    GameState = statetemp;
/*
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
*/
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
