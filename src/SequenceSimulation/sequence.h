#ifndef sequence_H_ 
#define sequence_H_

#include <string>

void printHelp(); ///< print help
std::string randomDNA(unsigned int DNAlength); ///< return a random DNA String with length DNAlength
std::string mutateDNA(std::string DNA, double mutationProbability); ///< return a mutated DNA

#endif //sequence_H_ 
