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
        
        int k;                                     ///< length of any node (kmer)

        /** vector of adjacency edges for each 
         *  node in each sequence
         */
        vector<vector<vector<Node> >> listOfEdges;

        vector<string> stringListSequence;         ///< vector of strings for the sequences 
        
        vector<unsigned int> numberOfKmers;        ///< the numbers of nodes for each sequence 
                                        
        vector<vector<Node>> nodeList;             ///< list of nodes for each sequence
               
        /** calculate the list of edges <br>
         *  at first: function calcNodeList() is called <br>
         *  second: pushes vector of adjacent edges from 
         *  all nodes in one sequence in listOfEdges through
         *  the function getAdjacentEdges(unsigned int index)   
         */               
        void calcEdgeList();                       
    public:
        // constructor
        Graph();
                                                                 
        int getK();                                 ///< get the length of node (kmer)
                                                    
        vector<string>& getStringListSequence();    ///< get the string for every sequence
          
        /** get the vector of adjacency edges for each
         *  node in each sequence 
         */
        vector<vector<vector<Node> >>& getEdgeList();
              
        /** \param index for a sequence
         *  \return vector of adjacent edges from all nodes in one sequence (=index)
         */
        vector<vector<Node>> getAdjacentEdges(unsigned int index);

        // get nodeList
        vector<vector<Node>>& getNodeList();
               
        // get the numbers of nodes for each sequences
        const vector<unsigned int>& getAmountOfKmer();
                        
        void calcNodeList(); ///<fill the vector of nodes with all possible nodes (with properties)

        /** \param nameFile name of the fasta file
         *  \param k length of any node (kmer)
         */
        void readFastaFiles(string nameFile, int k);
};
