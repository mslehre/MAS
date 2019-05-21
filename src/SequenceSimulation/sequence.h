#ifndef sequence_H_ 
#define sequence_H_

/**
 * prints the usage of this program in the console
 */

void printHelp();

/**
 * This function creates one multiple FASTA file "sequences.fa" with numberOfSequences 
 * random sequences of lenght DNAlength and mutation probability mutationpProbability.
 * \param length is the length of the created sequences
 * \param number_of_sequences is the number of sequences that will created   
 * \param probability is the probability for mutations in the sequencens  
 */

void simulate(unsigned int numberOfSequences, unsigned int DNAlength, double mutationpProbability);

#endif //sequence_H_ 
