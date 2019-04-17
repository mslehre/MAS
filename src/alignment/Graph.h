#pragma once

#include<fstream>
#include<string>
#include<vector>
#include<array>
#include<fstream>
#include "Node.h"
#include<utility>

class Graph {
    private:
        // length of any node (kmer)
        int k;

        // vector for vectors and inside a vector are vectors
        // for the adjacent nodes of a node
        // (implicit adjacent edges) 
        std::vector<std::vector<std::vector<Node> >> listOfEdges;

        // vector of strings for the sequences   
        std::vector<std::string> stringListSequence;
           
        // vector of amount of nodes in all sequences   
        std::vector<int> numberOfKmers;

        // list of nodes                                        
		std::vector<std::vector<Node>> nodeList;

        // Method: calculate list of edges                              
        void calcEdgeList();
    public:
        // constructor
        Graph();
                                               
        // Method: length of node (kmer)             
        int getK();
                                                
        // Method: get StringListSequence
        std::vector<std::string>& getStringListSequence();
          
        // Method: get EdgeList
        std::vector<std::vector<std::vector<Node> >>& getEdgeList();
              
        // Method: get adjacent edges from one node
        //         index 
        std::vector<std::vector<Node>> getAdjacentEdge(int index);
               
        // Method: get amount of nodes for all sequences
        const std::vector<int>& getAmountOfKmer();

        // Method: calculate list of nodes                  
        void calcNodeList();

        // Method: reading fasta file, k length of any node (kmer)
        void readingFastaFiles(std::string nameFile, int k); 
};
