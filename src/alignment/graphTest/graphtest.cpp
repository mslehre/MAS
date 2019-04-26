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

    // get list of nodes only with matches 
    vector<Node> nodes = g.getNodeList();
    cout << "All nodes only with matches:" << endl;
    for (auto &node : nodes) {
        cout << "("<< node.i << "  ," << node.j << ")" << endl;
        for (auto &element : node.adjNodes) {
             cout << "Match with: ("<< element.i << "  ," << element.j << ")" << "  ";
        }
        cout << endl;
        cout << "###################################################" << endl;
    }
    // get list of edges
    vector<Edge> edgeVec = g.getEdgesVector();
    cout << "Output all edges:" << endl;
    for (auto a : edgeVec) {
        cout << "(" << a.first.i << " ," << a.second.j << ")" << endl;
    }
    //#####################################################################

    return 0;
}
