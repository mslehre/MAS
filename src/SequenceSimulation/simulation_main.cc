#include <iostream>
#include <random>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include "sequence.h"

/**
 * \brief This programm creates one multiple FASTA file "sequences.fa" with S random sequences of lenght L.
 * If there is more then one sequence then we have mutations with mutation probability P. 
 * Call script with: ./simulation_main S L P
 * Example: ./simulation_main 5 100 0.3
 */

using namespace std;

int main(int argc, char *argv[]){
    if (argc != 4) {
        cerr << "\nMissing arguments or too mutch arguments.\n" << endl;
        printHelp();
        return -1;
    }	
    unsigned int numberOfSequences = atoi(argv[1]);
    if (numberOfSequences <= 0) {
        cerr << "\nThe first number must be an positive integer.\n" << endl;
        printHelp();
        return -1;
    }
    unsigned int DNAlength = atoi(argv[2]);
    if (DNAlength <= 0) {
        cerr << "\nThe second number must be an positive integer.\n"  << endl;
        printHelp();
        return -1;
    }
    double mutationpProbability = atof(argv[3]);
    if (mutationpProbability < 0 || mutationpProbability > 1) {
        cerr << "\nThe third number must be an double between 0 and 1.\n" << endl;
        printHelp();
        return -1;
    }

    vector<string> DNAsequences(numberOfSequences);
    string DNA = randomDNA(DNAlength);

    for (unsigned int i = 0; i < numberOfSequences; i++) {
        string mutantDNA = mutateDNA(DNA, mutationpProbability);
        DNAsequences[i] = mutantDNA;
    }
	
    ofstream outfile("sequences.fa");
    if (!outfile.is_open()) {
        cerr << "Error creating the output file." << endl;
        return -1;
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

    return 0;
}

