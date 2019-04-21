
#ifndef ColorMap_H_
#define ColorMap_H_

#include <string>
#include <SFML/Graphics.hpp>
#include <vector>

/** \brief This Class stores a List of well-different Colors and a method, 
 *         which assign a Color to a argumentstring.
 *
 * The Class stores 2 variables: ColorList, which is a vector with different Color Values and differentKmers, which
 * is a vector of strings, where the strings contains the different Kmers, which are in the input Sequence.
 * You can initialize a "ColorMap" only with the ColorList and with all variables. (See constructors)
 * Aswell there are update methods, to initialize variables after the constructor call.
 * The Main Idea of this class is the method "Color Map(string)" which maps a Kmer 
 * to a unique Color, which we pick out of the ColorList.
 */
class ColorMap {
    private:
        std::vector<sf::Color> ColorList;           ///< List of well-different Colors which we assign to Kmers
        std::vector<std::string> differentKmers;    ///< The List of all different Kmers in the "Sequence" Argument
    public:
        /**
         * \param Sequences A Vector which storage multiple Sequences (strings)
         * \param k an integer which defines the k of Kmer
         */
        ColorMap(std::vector<std::string>& Sequences, int k);   ///< The complete Constructor which initalize all
        /** 
         * \param numbOfKmer an integer which defines the size of the ColorList
         */
        ColorMap(int numbOfKmer);                               ///< Constructor which only initialize the Colorlist
        ColorMap();                                             ///< standard Constructor

        /** 
         * \param numbOfKmer an integer which defines the size of the ColorList
         */
        void updateColorList(int numbOfKmer);                                   ///< Update function for the ColorList
        /**
         * \param Sequences A Vector which storage multiple Sequences (strings)
         * \param k an integer which defines the k of Kmer
         */
        void updateSequenceLists(std::vector<std::string>& Sequences, int k);   ///< Update function for differentKmers
        /**
         * \param kmer a String which storage a Kmer
         * \return a unique color
         */
        sf::Color Map(std::string kmer);                                        ///< The Method to map single Kmers to a color
        /**
         * \return The List of Colors of the object
         */
        std::vector<sf::Color> giveColorList();                                 ///< Method to output ColorList
        /**
         * \return The List of Kmers of the object
         */
        std::vector<std::string> giveKmerlist();                                ///< Method to output differentKmers

};

#endif //kmercolor_H_
