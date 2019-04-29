#include "generator.h"
#include <string>
#include <random>
#include <chrono>

using namespace std;

Generator::Generator(){
   mt19937 gen(chrono::high_resolution_clock::now().time_since_epoch().count());
   rng = gen;
}

string Generator::randomDNA(unsigned int DNAlength){	
    uniform_int_distribution<> dis(0, 3); // selects a number between 0 and 3
    string alphabet = "ACTG";    
    string DNA;  
       
    for (unsigned int i = 0; i < DNAlength; i++) {
        DNA = DNA + alphabet[dis(rng)];                    
    }

    return DNA;
}

string Generator::mutateDNA(string DNA, double mutationProbability){
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
