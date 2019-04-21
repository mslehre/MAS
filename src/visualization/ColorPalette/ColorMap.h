
#ifndef ColorMap_H_
#define ColorMap_H_

#include <string>
#include <SFML/Graphics.hpp>
#include <vector>

class ColorMap {

    private:
        std::vector<sf::Color> ColorList;
        std::vector<std::string> differentKmers;

    public:
        ColorMap(std::vector<std::string>& Sequences, int k);
        ColorMap(int numbOfKmer);
        ColorMap();

        void updateColorList(int numbOfKmer);
        void updateSequenceLists(std::vector<std::string>& Sequences, int k);
        sf::Color Map(std::string kmer);
        std::vector<sf::Color> giveColorList();
        std::vector<std::string> giveKmerlist();

};

#endif //kmercolor_H_
