#ifndef generator_H_ 
#define generator_H_

#include <string>
#include <random>

/** \brief This class generate random seeds. 
 * randomDNA returns a random DNA String with length DNAlength.
 * mutateDNA returns a DNA with mutations.
 */

class Generator {
    private:
        std::mt19937 rng; ///< random seed generator

    public:
        Generator(); // constructor
        ~Generator(){}; // destructor
        /** 
         * \param DNAlength is the lenght of the DNA String that will returned
         * \return a random DNA String with length DNAlength
         */
        std::string randomDNA(unsigned int DNAlength); 
        /** 
         * \param DNA string that will be mutated
         * \param mutationProbability is the probability to mutate a character in the DNA string
         * \return a mutated DNA
         */
        std::string mutateDNA(std::string DNA, double mutationProbability); 
};

#endif //generator_H_ 
