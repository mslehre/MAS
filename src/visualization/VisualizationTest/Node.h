#pragma once

#include<string>

using std::string;

class Node {
    public:
        // constructor: i sequence, j node in i, string of node 
        Node(unsigned int i, unsigned int j, string kmer);

        ///< the index of the row/sequence
        unsigned int i;
        unsigned int j;
        string kmer;
};
