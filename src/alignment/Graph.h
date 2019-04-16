#pragma once

#include <fstream>
#include<string>
#include<vector>
#include<array>
#include<fstream>

class Graph {
    private:
        int k;

        std::vector<std::array<int,3>> listOfEdges;                 // vector of edges (as array with size 3)
        std::vector<std::string> stringListSequence;                // vector of strings for the sequences
        std::vector<int> numberOfKmer;                              // vector amount of k-mer
        // std::vector<std::vector<int>> adjacentEdges;
        void calcEdgeList();                                        // Method: calculate list of edges
		
    public:
        Graph(int k);                                               // constructor

        void readingFastaFiles(std::string nameFile);               // Method: reading fasta file
        int getK();                                                 // Method: length k-mer

        std::vector<std::string>& getStringListSequence();          // Method: get StringListSequence
        std::vector<std::array<int,3>>& getEdgeList();              // Method: get EdgeList
        std::vector<int> getAdjacentEdge(int sequence, int kNum);   // Method: get adjacent edges from one node
        const std::vector<int>& getAmountOfKmer();                  // Method: get Number of k-mer for all sequences
};
