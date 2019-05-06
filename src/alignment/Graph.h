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

        unsigned int k;                                      ///< length of any node (kmer)

        vector<string> stringListSequence;          ///< vector of strings for the sequences

        vector<int> numberOfKmers;         ///< the numbers of nodes only with matches

        vector<vector<Node>> nodeListAll;           ///< list of all nodes for each sequence

        vector<Node> nodeList;                      ///< list of nodes only with matches (the right set of nodes)
        
        vector<Node> helpList;                      ///< use only for calculation

        vector<Edge> edgesVector;                   ///< vector of edges for all sequences (set of edges)

        /** \brief vector of adjacent edges from all nodes in one sequence (=index)
         *  \param index for a sequence
         */
        void calcAdjacentEdges(unsigned int index);

        /** calculate the list of edges <br>
         *  at first: function calcNodeList() is called <br>
         *  second: function calcAdjacentEdges is called
         */
        void calcEdgeList();

        void calcNodeList(); ///< calcualte nodeListAll with all possible nodes (isolated nodes as well) with properties i,j,kmer
    public:
        // constructor
        Graph();
                                     
        unsigned int getK();                        ///< get the length of node (kmer)

        vector<string>& getStringListSequence();    ///< get the string for every sequence

        vector<Node>& getNodeList();                ///< get list of nodes only with matches

        /** \brief the k-mers are tiled (shift=k) <br>
         *  first index which sequence <br>
         *  second index how many nodes
         *  \return numbers of nodes only with matches
         */
        vector<int>& getNumberOfKmers();

        vector<Edge>& getEdgesVector();             ///< get vector of edges for all sequences

        /** \brief read a fasta file
         *  \param nameFile name of the fasta file
         *  \param k length of any node (kmer)
         */
        void readFastaFiles(string nameFile, unsigned int k);
};
