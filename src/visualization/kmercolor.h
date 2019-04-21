
#ifndef kmercolor_H_ 
#define kmercolor_H_

#include <string>
#include <SFML/Graphics.hpp>
#include <vector>

class ColorMap {

    private:
        std::vector<sf::Color> ColorList;
        std::vector<std::string> differentKmers;

    public:
        ColorMap(std::vector<std::string>& Sequences, int k);
        ColorMap(int numberOfKmer);
        ColorMap();

        void updateColorList(int numberOfKmer);
        void updateSequenceLists(std::vector<std::string>& Sequences, int k);
        sf::Color Map(std::string kmer);
        std::vector<sf::Color> giveColorList();

};

#endif //kmercolor_H_
