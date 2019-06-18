#ifndef Gamemaster_H_ 
#define Gamemaster_H_
#include <vector>
#include "../alignment/DrawNode.h"
#include "../alignment/Graph.h"
#include "../alignment/State.h"

class Gamemaster {
    public:
        Graph GameGraph; ///< The Graph of the game
        state GameState; ///< The State of GameGraph
        std::vector<DrawNode> GameNodes; ///< DrawNodes of GameGraph

        /**
         * This function make a list of unique Kmers 
         * \param nodeList is a vector with all nodes (contains the Kmers)
         * \return a vector of unique strings
         */

        std::vector<std::string> getKmers(std::vector<Node>& nodeList);

        /**
         * \param k is the length of the kmers
         * \param length is the length of the created sequences
         * \param number_of_sequences is the number of sequences that will created   
         * \param probability is the probability for mutations in the sequences
         */

        void makeGame(unsigned int k, unsigned int length, unsigned int number_of_sequences, double probability);

        /**
         * standard constructor, which does nothing
         */

        Gamemaster();
};

#endif //Gamemaster_H_
