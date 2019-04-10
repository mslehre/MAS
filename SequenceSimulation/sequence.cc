#include <iostream>
#include <random>
#include <string>
#include <cstdlib>
#include <ctime>
#include "sequence.h"

using namespace std;

void printHelp(){
    cout << "\t Call skript with:\t./main S L P \n" <<endl;
    cout << "\t S: Must be an integer greater then zero." << endl;
    cout << "\t\t S is the number of sequences that will created.\n" << endl;
    cout << "\t L: Must be an integer greater then zero." << endl;
    cout << "\t\t L is the lenght of the created sequences.\n" << endl;
    cout << "\t P: Must be an double between zero and one." << endl;
    cout << "\t\t P: is the probability for mutations in the sequencens.\n" << endl;
}

string randomDNA(unsigned int DNAlength){	
    random_device rd;   // Will be used to obtain a seed for the random number engine
    mt19937 gen(rd());  // Standard mersenne_twister_engine seeded with rd()
    uniform_int_distribution<> dis(0, 3);   // Selects a number between 0 and 3

    string alphabet = "ACTG";    
    string DNA;  
       
    for (unsigned int i = 0; i <= DNAlength; i++) {
        DNA = DNA + alphabet[dis(gen)];                    
    }

    return DNA;
}

string mutateDNA(string DNA, double mutationProbability){
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 3);
    string alphabet = "ACTG";

    for (unsigned int i = 1; i <= (DNA.length() + 1); i++) {
        srand((time(NULL) * i));    // random seed for rand()
        double isMutant = ((double) rand() / RAND_MAX); // random number between 0 and 1
        if (isMutant <= mutationProbability)
            DNA[i - 1] = alphabet[dis(gen)];
    }

    return DNA;
}

