#ifndef sequence_H_ 
#define sequence_H_

#include <string>

void printHelp();
std::string randomDNA(unsigned int DNAlength);
std::string mutateDNA(std::string DNA, double mutationProbability);

#endif //sequence_H_ 
