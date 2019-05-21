#ifndef Gamemaster_H_ 
#define Gamemaster_H_
#include <vector>
#include "../../alignment/DrawNode.h"
#include "../../alignment/Graph.h"
#include "../../alignment/State.h"

class Gamemaster {
    private:
        Graph GameGraph; ///< The Graph of the game
        state GameState; ///< The State of GameGraph
        std::vector<DrawNode> GameNodes; ///< DrawNodes of GameGraph

    public:

        /**
         * \param k is the length of the kmers
         * \param length is the length of the created sequences
         * \param number_of_sequences is the number of sequences that will created   
         * \param probability is the probability for mutations in the sequencens  
         */

        Gamemaster(unsigned int k, unsigned int length, unsigned int number_of_sequences, double probability);

        Graph get_GameGraph();
        state get_GameState();
        std::vector<DrawNode> get_GameNodes();
        
};

#endif //Gamemaster_H_ 

