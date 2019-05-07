#include "sequence.h"
#include <iostream>

using namespace std;

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

