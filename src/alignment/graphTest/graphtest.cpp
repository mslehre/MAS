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

    

    return 0;
}
