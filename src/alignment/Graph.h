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

        unsigned int k;                         ///< length of k-mer

        /** 
         * \brief nodes only with matches in other sequences <br>
         * Nodes in a row i are sorted in ascending order relative to the column number j. <br>
         * The rows are also in ascending order.
         */

        vector<Node> nodes;  

        vector<Edge> edges;                     ///< vector of edges for all sequences (set of edges)

        void calcNodeList(vector<string>& stringListSequence); 
    public:

        Graph();

        vector<Node>& getNodes();               ///< get vector of nodes with matches in other sequences
                              
        unsigned int getNumberOfSequences();    ///< return the number of sequences for an ascending sorted nodes with respect to the rows

        /** 
         * \brief get number of nodes for a sequence
         * \param sequence index for sequence 
         */

        unsigned int getNumberOfNodes(unsigned int sequence); 

        vector<Edge>& getEdges();               ///< get vector of edges for all sequences

        /** 
         * \brief read a fasta file
         * \param nameFile name of the fasta file
         * \param k length of any node (kmer)
         */

        void readFastaFiles(string nameFile, unsigned int k);
        
        /** 
         * \brief reset the Graph
         * clears nodes and edges and sets k to zero
         */

        void resetGraph();
};
