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

        vector<string> stringListSequence;      ///< vector of strings for the sequences

        vector<Edge> edges;                     ///< vector of edges for all sequences (set of edges)

        /** \brief calculate vector of nodes and implicit edges
         *  \param stringListSequence vector of strings (sequences)  
         */
        void calcNodeList(vector<string>& stringListSequence); 
    public:
        // constructor
        Graph();

        unsigned int getK();                    ///< get the length of node (kmer)

        vector<string>& getStringListSequence(); ///< get the string for every sequence

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
