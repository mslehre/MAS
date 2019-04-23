#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "ColorMap.h"
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

    //get Graph information for the following iteration (Example)
    int k = Example.getK();
    vector<string> Sequences = Example.getStringListSequence();
    //iterate to test the colors of all kmers - main part of the Example
    ColorMap Expl(Sequences,k);
    vector<string> Kmers = Expl.giveKmerlist();
    sf::Color ph;

    for(int i = 0;i<Kmers.size();i++){
        ph = Expl.Map(Kmers[i]);
        cout <<i<<": "<< Kmers[i] << " bekommt die Farbe: (" << (int)ph.r << ", "<<(int)ph.g<<", "<<(int)ph.b<<")" <<endl;
    }
}

