#include<iostream>
#include<stdlib.h>
#include "Graph.h"

using namespace std;

int main(int argc, char **argv){
    // example create object from class Graph
    Graph g;	
																		 
    // reading fasta file
    if (argc != 3) {
        cerr << "Please start your program with: ./graphtest [fileName.fa] [length of node]" << endl;
        return -1;
    }
    // reading fasta file and calculate edgelist, length of node
    g.readFastaFiles(argv[1],atoi(argv[2]));

    //###################################################################
    // test
    cout << "TestProgramm: k-mer with length the of " << atoi(argv[2]) << endl; 

    // get nodes 
    vector<Node> nodes = g.getNodes();

    for (auto &node : nodes) {
        cout << "("<< node.i << "," << node.j << ")" << " with " << node.kmer << " has match with: " << endl;
        for (auto &element : node.adjNodes) {
             cout << "("<< element->i << "," << element->j << ")" << " " << node.kmer << " ";
        }
        cout << endl;
        cout << "###################################################" << endl;
    }
    
    // get edges
    vector<Edge> edges = g.getEdges();
    cout << "Output all edges:" << endl;
    for (auto a : edges) {
        cout << "Edge: " << "(" << a.first->i << " ," << a.first->j << ")" << "---" << "(" << a.second->i << " ," << a.second->j << ")"<< endl;
    }
    //#####################################################################
    return 0;
}
