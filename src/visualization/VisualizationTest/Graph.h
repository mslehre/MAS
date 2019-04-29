#pragma once

#include<fstream>
#include<string>
#include<vector>
#include<array>
#include<fstream>
#include "Node.h"
#include<utility>

using std::vector;
using std::string;

class Graph {
    private:
        ///< length of any node (kmer)
        int k;

        ///< vector of adjacency edges for each node in each sequence
        vector<vector<vector<Node> >> listOfEdges;

        // vector of strings for the sequences   
        vector<string> stringListSequence;
           
        ///< the numbers of nodes for each sequence  
        vector<unsigned int> numberOfKmers;

        // list of nodes for each sequence                                       
        vector<vector<Node>> nodeList;

        // Method: calculate list of edges                              
        void calcEdgeList();
    public:
        // constructor
        Graph();
                                               
        // Method: length of node (kmer)             
        int getK();
                                                
        // Method: get StringListSequence
        vector<string>& getStringListSequence();
          
        // Method: get EdgeList
        vector<vector<vector<Node> >>& getEdgeList();
              
        // Method: get adjacent edges from one node
        //         index 
        vector<vector<Node>> getAdjacentEdge(unsigned int index);

        // Method: get nodeList
        vector<vector<Node>>& getNodeList();
               
        // Method: get number of nodes for all sequences
        const vector<unsigned int>& getAmountOfKmer();

        // Method: calculate list of nodes                  
        void calcNodeList();

        // Method: reading fasta file, k length of any node (kmer)
        void readFastaFiles(string nameFile, int k); 
};
