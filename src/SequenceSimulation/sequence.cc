#include <iostream>
#include <random>
#include <string>
#include <chrono>
#include "sequence.h"

using namespace std;

/**
 * prints the usage of this program in the console
 */

void printHelp(){
    cout << "\t Call skript with:\t./simulation_main S L P \n" << endl;
    cout << "\t Example: ./simulation_main 5 100 0.3 \n" << endl;
    cout << "\t S: Must be an integer greater then zero." << endl;
    cout << "\t\t S is the number of sequences that will created.\n" << endl;
    cout << "\t L: Must be an integer greater then zero." << endl;
    cout << "\t\t L is the length of the created sequences.\n" << endl;
    cout << "\t P: Must be an double between zero and one." << endl;
    cout << "\t\t P is the probability for mutations in the sequencens.\n" << endl;
}

/** 
 * \param DNAlength is the lenght of the DNA String that will returned
 * \return a random DNA String with length DNAlength
 */

string randomDNA(unsigned int DNAlength){	
    mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());
    uniform_int_distribution<> dis(0, 3); // selects a number between 0 and 3

    string alphabet = "ACTG";    
    string DNA;  
       
    for (unsigned int i = 0; i < DNAlength; i++) {
        DNA = DNA + alphabet[dis(rng)];                    
    }

    return DNA;
}

/** 
 * \param DNA string that will be mutated
 * \param mutationProbability is the probability to mutate a character in the DNA string
 * \return a mutated DNA
 */

string mutateDNA(string DNA, double mutationProbability){
    mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());
    uniform_int_distribution<> dis(0, 3);
    uniform_real_distribution<> dis2(0, 1);

    string alphabet = "ACTG";

    for (unsigned int i = 0; i < DNA.length(); i++) {
        double isMutant = dis2(rng); // random number between 0 and 1
        if (isMutant <= mutationProbability)
            DNA[i] = alphabet[dis(rng)];
    }

    return DNA;
}

