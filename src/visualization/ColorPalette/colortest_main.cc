#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <stdlib.h>
#include <SFML/Graphics.hpp>
#include "../colormap.h"
#include "../colorlist.h"
#include "../../alignment/Graph.h"

using namespace std;

/*
 * this method is predefined by myself, for getting a list of different Kmers.
 * This function will get removed, when we have a function in our
 * libraries, which do the same.
 *
 */
vector<string> giveKmers(vector<string>& Sequences, int k) {

    vector<int> SequenceSizes; // A tupel of integers, where the i integer n stands for n Kmers in Sequencs i

    // initialization of the SequenceSizes
    for (unsigned int i = 0; i < Sequences.size(); i++)
        SequenceSizes.push_back((int)floor((Sequences[i].size()) / k));

    vector<string> allKmers; // The set of all different Kmers

    bool matched = false; // a boolean for the "Is this Kmer already in my set?"-Check

    int index; // a integer, which is index for the k-mers per sequence
    
    /*
     * here we go over the i Sequence and look at the index's Kmer and 
     * push it into our set, when it is not already in.
     */
    for (unsigned int i = 0; i < Sequences.size(); i++) {
        index = 0;
        while (index < SequenceSizes[i]) {
            // comparing all k-mers in our set with the picked one
            for (unsigned int j = 0; j < allKmers.size(); j++) {
                if (allKmers[j] == Sequences[i].substr(index * k, k)) {
                    matched = true;
                    break;
                }
            }
            // pushing a new Kmer
            if (!matched)
                allKmers.push_back(Sequences[i].substr(index * k, k));
            matched = false;
            index += 1;
        }
    }
    return allKmers;
}

int main(int argc, char **argv){
    // initalize the Example Graph
    Graph graphExample(3);

    // Bug Catching for fasta file
    if(argc != 2){
        cerr << "Please start your program with: ./main [fileName.fa]" << endl; 
        return -1;
    }

    // declare the Graph in terms of a fasta file
    graphExample.readingFastaFiles(argv[1]);

    // get Graph information for the Kmerlist and Colorlist
    int k = graphExample.getK(); // integer with size of Kmer
    vector<string> Sequences = graphExample.getStringListSequence(); // vector with strings which stand for Sequences

    // calculation of the different Kmers
    vector<string> Kmers = giveKmers(Sequences, k); // vector of strings which stand for Kmers

    // initialize the colorlist
    colorlist colorExample(Kmers.size());

    // initialize the colormap
    vector<sf::Color> colors = colorExample.giveList(); // vector of different colors
    colormap mapExample(Kmers, colors);

    sf::Color ph; // some kind of placeholder

    /*
     * the test method where i return all color values in
     * the console to check the functionality.
     */
    cout << "(" << Kmers.size()<<";"<<colors.size()<<")"<<endl;
    for(unsigned int i = 0;i<Kmers.size();i++){
        ph = mapExample.Map(Kmers[i]);
        cout <<i<<": "<< Kmers[i] << " bekommt die Farbe: (" << (int)ph.r << ", "<<(int)ph.g<<", "<<(int)ph.b<<")" <<endl;
    }
}

