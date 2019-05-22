#include "sequence.h"
#include "generator.h"
#include <string>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <iostream>

using namespace std;

void printHelpSequenceSimulation(){
    cout << "\t Call skript with:\t./simulation_main S L P \n" << endl;
    cout << "\t Example: ./simulation_main 5 100 0.3 \n" << endl;
    cout << "\t S: Must be an integer greater then zero." << endl;
    cout << "\t\t S is the number of sequences that will created.\n" << endl;
    cout << "\t L: Must be an integer greater then zero." << endl;
    cout << "\t\t L is the length of the created sequences.\n" << endl;
    cout << "\t P: Must be an double between zero and one." << endl;
    cout << "\t\t P is the probability for mutations in the sequencens.\n" << endl;
}

void simulate(unsigned int numberOfSequences, unsigned int DNAlength, double mutationProbability){
    vector<string> DNAsequences(numberOfSequences);
    Generator gen;
    string DNA = gen.randomDNA(DNAlength);

    for (unsigned int i = 0; i < numberOfSequences; i++) {
        string mutantDNA = gen.mutateDNA(DNA, mutationProbability);
        DNAsequences[i] = mutantDNA;
    }
	
    ofstream outfile("sequences.fa");
    if (!outfile.is_open()) {
        cerr << "Error creating the output file." << endl;
    }

    const int maxLineLength = 80;

    for (unsigned int i = 0; i < DNAsequences.size(); i++) {
        outfile << ">seq" << i + 1;
        for (unsigned int j = 0; j < DNAlength; j++) {
            if (j % maxLineLength == 0) 
                outfile << "\n";
            outfile << DNAsequences[i][j];
        }
        outfile << endl;
    }
    outfile.close();
}

