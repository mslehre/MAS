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
    cout << "\t\t L is the length of the created sequences.\n" << endl;
    cout << "\t P: Must be an double between zero and one." << endl;
    cout << "\t\t P is the probability for mutations in the sequencens.\n" << endl;
}

string randomDNA(unsigned int DNAlength){	
    random_device rd;   // will be used to obtain a seed for the random number engine
    mt19937 gen(rd());  // standard mersenne_twister_engine seeded with rd()
    uniform_int_distribution<> dis(0, 3);   // selects a number between 0 and 3

    string alphabet = "ACTG";    
    string DNA;  
       
    for (unsigned int i = 0; i < DNAlength; i++) {
        DNA = DNA + alphabet[dis(gen)];                    
    }

    return DNA;
}

string mutateDNA(string DNA, double mutationProbability){
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 3);
    uniform_int_distribution<> dis2(0, 1000000);

    string alphabet = "ACTG";
    srand(time(NULL) + dis2(gen));    // random seed for rand()

    for (unsigned int i = 0; i < DNA.length(); i++) {
        double isMutant = ((double) rand() / RAND_MAX); // random number between 0 and 1
        if (isMutant <= mutationProbability)
            DNA[i] = alphabet[dis(gen)];
    }

    return DNA;
}

