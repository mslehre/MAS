#pragma once
#include<string>
#include<vector>
#include<array>
#include<iostream>
#include<fstream>
#include "Node.h"
#include "Edge.h"
#include<utility>
#include<algorithm>
#include<set>

using std::vector;
using std::string;
using std::pair;

class Graph {
    private:

        unsigned int k;                         ///< length of any node (kmer)

        vector<Node> nodes;                     ///< nodes only with matches

        vector<Edge> edges;                     ///< vector of edges for all sequences (set of edges)

        void calcNodeList(vector<string>& stringListSequence); 
    public:
        // constructor
        Graph();

        vector<Node>& getNodes();               ///< get vector of nodes with matches
                              
        unsigned int getNumberOfSequences();    ///< get number of sequences

        /** \brief get number of nodes for a sequence
         *  \param sequence index for sequence 
         */
        unsigned int getNumberOfNodes(unsigned int sequence); 

        vector<Edge>& getEdges();               ///< get vector of edges for all sequences

        /** \brief read a fasta file
         *  \param nameFile name of the fasta file
         *  \param k length of any node (kmer)
         */
        void readFastaFiles(string nameFile, unsigned int k);
};
