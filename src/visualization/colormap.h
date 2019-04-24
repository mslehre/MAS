
#ifndef colormap_H_
#define colormap_H_

#include <string>
#include <SFML/Graphics.hpp>
#include <vector>
#include <unordered_map>

/** \brief This Class stores an unordered_map from strings to colors and a method to map
 *         strings (expecially kmers) to a unique color
 * 
 * The Class stores 1 variable: colorAssignment, which is a unordered_map with kmers (strings) 
 * as keys and a color as the assigned value. 
 * You can initialize a "colormap" with a vector of colors and a vector of kmers (strings).
 * But both lists have to has the same size so, that the map method is unique 
 * and functionally complete.
 * The Class stores 1 function: Map, which maps a single kmer (string) to a unique color
 */
class colormap {
    private:
        std::unordered_map<std::string,sf::Color> colorAssignment; ///< a unordered map with Kmers as Keys and Colors as values
    public:
        /**
         * the complete constructor, which initialize the unordered_map
         * with strings as keys and Color values as values
         * 
         * \param givenKmers a vector of different kmers (strings)
         * \param givenColorlist a vector of different Color values 
         */
        colormap(std::vector<std::string>& givenKmers, std::vector<sf::Color>& givenColorlist);

        /**
         * the standard constructor, which initialize the unordered_map empty
         */
        colormap(); ///< standard Constructor

        /**
         * this method initialize the unordered map colorAssignment.
         * 
         * \param givenKmers a vector of different kmers (strings)
         * \param givenColorlist a vector of different Color values 
         */
        void updateAssignment(std::vector<std::string>& givenKmers, std::vector<sf::Color>& givenColorlist);

        /**
         * this method will map a single Kmer (string) to a unique Color value
         * with the class functions of the unorderd map.
         *
         * \param kmer a string which is a Kmer
         * \return a Color value (unique)
         */
        sf::Color Map(std::string Kmer);

        /**
         * Method to return the private unordered_map colorAssignment, which have
         * strings as keys and Color values as values
         *
         * \return an unordered_map with kmers as keys and Colors as values
         */
        std::unordered_map<std::string,sf::Color> giveAssignment();
};

#endif //colormap_H_
