#pragma once

#include<fstream>
#include<string>
#include<vector>
#include<array>

class Node {
    private:
    public:
        // constructor: i sequence, j node in i, string of node 
        Node(unsigned i, unsigned j, std::string kmer);

        unsigned i;
        unsigned j;
        std::string kmer;
};
