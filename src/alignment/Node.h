#pragma once

#include<string>

using std::string;

class Node {
    public:
        // constructor: i sequence, j node in i, string of node 
        Node(unsigned int i, unsigned int j, string kmer);

        unsigned int i;         ///< the index of the row/sequence
        unsigned int j;         ///< the index of the node
        string kmer;            ///< the string of the node
};
