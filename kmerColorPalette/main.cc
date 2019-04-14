#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "kmercolor.h"
#include "Graph.h"

using namespace std;

int main(int argc, char **argv){
    //Initalize the Graph
    Graph Example(3);

    //Bug Catching for fasta files
    if(argc != 2){
        cerr << "Please start your program with: ./main [fileName.fa]" << endl; 
        return -1;
    }

    //Declare the Graph in terms of a fasta file
    Example.readingFastaFiles(argv[1]);

    //Get a vector of colors (with the same structure like in the graph to map unique for each kmer)
    vector<vector<sf::Color>> ColorList = ColorBasedOnGraph(Example);

    //get Graph information for the following iteration (Example)
    int index;
    int k = Example.getSimpleKOfKmer();
    vector<int> SequenceSize = Example.getNumberOfKmer();
    vector<string> Sequences = Example.getStringListSequence();
    for (int i = 0;i<SequenceSize.size();i++) {
        if (Sequences[i].substr(k*(SequenceSize[i]-1),k).size()!=k)
            SequenceSize[i] -= 1;
    }

    //iterate to test the colors of all kmers - main part of the Example
    for (int i=0;i<Sequences.size();i++) {
        index = 0;
        while (index<SequenceSize[i]) {
            cout << Sequences[i].substr(index*k, k) << " bekommt die Farbe: (" << (int)ColorList[i][index].r;
            cout << ", "<<(int)ColorList[i][index].g<<", "<<(int)ColorList[i][index].b<<")" <<endl;
            index += 1;
        }    
    }
}

