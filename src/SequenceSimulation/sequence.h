#ifndef sequence_H_ 
#define sequence_H_

/**
 * prints the usage of this program in the console
 */

void printHelpSS();

/**
 * This function creates one multiple FASTA file "sequences.fa" with numberOfSequences 
 * random sequences of lenght DNAlength and mutation probability mutationProbability.
 * \param numberOfSequences is the number of sequences that will created 
 * \param DNAlength is the length of the created sequences  
 * \param mutationProbability is the probability for mutations in the sequences (between 0 and 100, measured in %)
 */

void simulate(unsigned int numberOfSequences, unsigned int DNAlength, unsigned int mutationProbability);

#endif //sequence_H_ 
