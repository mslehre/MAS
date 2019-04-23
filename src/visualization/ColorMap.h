
#ifndef ColorMap_H_
#define ColorMap_H_

#include <string>
#include <SFML/Graphics.hpp>
#include <vector>

/** \brief This Class stores a List of well-distinguishable Colors and a method, 
 *         which assign a Color to a argumentstring.
 *
 * The Class stores 2 variables: ColorList, which is a vector with different Color Values and differentKmers, which
 * is a vector of strings, where the strings contains the different Kmers, which are in the input Sequence.
 * You can initialize a "ColorMap" with the ColorList and with all variables. (See constructors)
 * Also there are update methods, to initialize variables after the constructor call.
 * The main Idea of this class is the method "Color Map(string)" which maps a Kmer 
 * to a unique Color, which we pick out of the ColorList.
 */
class ColorMap {
    private:
        std::vector<sf::Color> ColorList;           ///< list of well-distinguishable Colors which we assign to Kmers
        std::vector<std::string> Kmers;    ///< the list of all different Kmers in the "Sequence" Argument
    public:
        /**
         * \param sequences A Vector which storage multiple Sequences (strings)
         * \param k an integer which defines the k of Kmer
         */
        ColorMap(std::vector<std::string>& Sequences, int k);   ///< the complete Constructor which initalize all
        /** 
         * \param numbOfKmer an integer which defines the size of the ColorList
         */
        ColorMap(int numbOfKmers);   ///< constructor which only initialize the Colorlist
        ColorMap();                 ///< standard Constructor

        /** 
         * \param numbOfKmer an integer which defines the size of the ColorList
         */
        void updateColorList(int numbOfKmers);   ///< update function for the ColorList
        /**
         * \param sequences A Vector which storage multiple Sequences (strings)
         * \param k an integer which defines the k of Kmer
         */
        void updateSequenceLists(std::vector<std::string>& Sequences, int k);   ///< update function for differentKmers
        /**
         * \param kmer a String which storage a Kmer
         * \return a unique color
         */
        sf::Color Map(std::string kmer);    ///< the Method to map single Kmers to a color
        /**
         * \return the list of Colors of the object
         */
        std::vector<sf::Color> giveColorList();     ///< method to output ColorList
        /**
         * \return the list of Kmers of the object
         */
        std::vector<std::string> giveKmerlist();    ///< method to output differentKmers

};

#endif //kmercolor_H_
