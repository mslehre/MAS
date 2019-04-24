#pragma once
#include<string>
#include<vector>
#include<array>
#include<iostream>
#include<fstream>
#include "Node.h"
#include "Edge.h"
#include<utility>

using std::vector;
using std::string;
using std::pair;

class Graph {
    private:

        int k;                                      ///< length of any node (kmer)

        vector<string> stringListSequence;          ///< vector of strings for the sequences

        vector<std::array<unsigned int,2>> numberOfKmers;         ///< the numbers of nodes only with matches

        vector<vector<Node>> nodeListAll;           ///< list of all nodes for each sequence

        vector<Node> nodeList;                      ///< list of nodes only with matches (the right set of nodes)

        vector<Edge> edgesVector;                   ///< vector of edges for all sequences (set of edges)

        /** calculate the list of edges <br>
         *  at first: function calcNodeList() is called <br>
         *  second: function calcAdjacentEdges is called
         */
        void calcEdgeList();
    public:
        // constructor
        Graph();
                                     
        int getK();                                 ///< get the length of node (kmer)

        vector<string>& getStringListSequence();    ///< get the string for every sequence
 
        /**  vector of adjacent edges from all nodes in one sequence (=index)
         *  \param index for a sequence
         */
        void calcAdjacentEdges(unsigned int index);

        vector<Node>& getNodeList();                ///< get list of nodes only with matches

        /** the k-mers are tiled (shift=k) <br>
         *  first index which sequence <br>
         *  second index how many nodes
         *  \return numbers of nodes only with matches
         */
        vector<std::array<unsigned int,2>>& getNumberOfKmers();

        vector<Edge>& getEdgesVector();             ///< get vector of edges for all sequences

        void calcNodeList(); ///< calcualte nodeListAll with all possible nodes (isolated nodes as well) with properties i,j,kmer

        /** \param nameFile name of the fasta file
         *  \param k length of any node (kmer)
         */
        void readFastaFiles(string nameFile, int k);
};
