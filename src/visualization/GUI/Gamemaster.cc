#include <iostream>
#include "../../alignment/Graph.h"
#include "../../SequenceSimulation/sequence.h"
#include <stdio.h>

Gamemaster::Gamemaster(unsigned int k, unsigned int length, unsigned int number_of_sequences, double probability){
    simulate(number_of_sequences, length, probability);     
    GameGraph.readFastaFiles("sequences.fa", k);
    int remove("sequences.fa");
    Gamestate(GameGraph);

    GameNodes.resize(GameGraph.getNodes().size())
    for (unsigned int i = 0; i < GameGraph.getNodes().size(); i++) {
        sf::Vector2f coords(GameGraph.getNodes().at(i).j, GameGraph.getNodes().at(i).i);
        GameNodes.at(i).coordinate = coords;
        GameNodes.at(i).col = mapExample.Map(GameGraph.getNodes().at(i).kmer);
    }
}
