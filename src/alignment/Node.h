#pragma once
#include<string>
#include "Node.h"
#include<vector>
using std::string;
using std::vector;

class Node {
    public:
        // constructor: i sequence, j node in i, string of node
        Node(unsigned int i, unsigned int j, string kmer);

        unsigned int i;         ///< the index of the row/sequence
        unsigned int j;         ///< the index of the node
        string kmer;            ///< the string of the node

        vector<Node> adjNodes;     ///< the nodes that match with this node in the following sequence
};

