#include <string>
#include <vector>
#include <SFML/Graphics/Color.hpp>
#include <array>
#include <cmath>
#include "ColorMap.h"
#include <iostream>

using namespace std;
using namespace sf;

/**
 * This Method will compute in terms of the argument sequences and the k, all kmers we are looking for and call
 * the method which compute us in terms of this number a Colormap. Then the method will compute
 * all different Kmers and push them in a List. We'll use this list to initialize differentKmers.
 */
ColorMap::ColorMap(vector<string>& Sequences, int k) {
    updateSequenceLists(vector<string>& Sequences, k);
}

/**
 * This Method will make a vector of Colors in terms of a number, which defines the Length of the 
 * length of the List. Then it will initialize ColorList with it. In our case the argument 
 * describes the number of Kmers we are looking for to map.
 */
ColorMap::ColorMap(int numbOfKmers) {
    updateColorList(numbOfKmers);
}

ColorMap::ColorMap() {

}

/**
 * This Method will compute in terms of the argument sequences and the k, all kmers we are looking for and call
 * the method which compute us in terms of this number a Colormap. Then the method will compute
 * all different Kmers and push them in a List. We'll use this list to update differentKmers.
 */
void ColorMap::updateSequenceLists(vector<string>& Sequences, int k) {
    ///< This is a variable which save the number of Kmers per Sequence which we have
    vector<int> SequenceSizes;
    for (int i = 0; i < Sequences.size(); i++)
        SequenceSizes[i] = (int)floor((Sequences[i].size())/k);

    ///< This variable is the output List
    vector<string> allKmers; ///< set of all kmers from all nodes of the graph

    ///< a boolean for the "got this kmer a color?"-Check
    bool matched = false;
    ///< a index for the k-mers per sequence
    int index;
    
    /**
     * This part of the method will push all Kmers in the List, which are not in the list already.
     */
    for (int i = 0; i < Sequences.size(); i++) {
        index = 0;
        while (index < SequenceSizes[i]) {
            ///< Comparing all k-mers to know if the Kmer is already in the list
            for (int j = 0; j < allKmers.size(); j++) {
                if (allKmers[j] == Sequences[i].substr(index*k, k)) {
                    matched = true;
                    break;
                }
            }
            ///< If its a new kmer, so we push it here
            if (!matched)
                allKmers.push_back(Sequences[i].substr(index*k, k));
            matched = false;
            index += 1;
        }
    }
    Kmers = allKmers;
    updateColorList(allKmers.size());
}

/**
 * This Method will make a vector of Colors in terms of a number, which defines the Length of the 
 * length of the List. Then it will update our ColorList with it. In our case the argument 
 * describes the number of Kmers we are looking for to map.
 */
void ColorMap::updateColorList(int numbOfKmers) {
    vector<Color> returnList; ///< the list i use to adjust this as the new List
    Color placeholder; ///< A placeholder which is needed to programm with rgb values
    /**
     * In this part of the method i push Colors in the List which i searched in the
     * web, so that they are well different. And they are all different to the hard coded,
     * because the r, g and b values have a distance of each other by 60, 120 or 180.
     * Link: https://www.rapidtables.com/web/color/RGB_Color.html
     */
    unsigned char DistinguishableCols[13][3] = {
        {255, 0, 0} //red
        {255, 128, 0} //orange
        {255, 255, 0} //yellow
        {128, 255, 0} //light green
        {0, 255, 0} //green
        {0, 255, 128} //dark green
        {0, 255, 255} //cyan
        {0, 128, 255} //blue
        {0, 0, 255} //dark blue
        {128, 0, 255} //violet
        {255, 0, 255} //pink
        {255, 0, 128} //dark pink
        {128, 128, 128} //grey
    };
    for (int i = 0; i < 13; i++) {
        placeholder.r = DistinguishableCols[i][0];
        placeholder.g = DistinguishableCols[i][1];
        placeholder.b = DistinguishableCols[i][2];
    }
    /**
     * In this part of the method i push Colors in terms of a algorithm i made for myself.
     * This algorithm is maybe not completed yet.
     */
    int index = 13; ///< i use this index to count about how much Colors are pushed.
    int array[60];
    for (int i = 0; i < 60; i++)
        array[i] = 11 + i;
    for (int l = 59; l >= 0; l--) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                for (int k = 0; k < 4; k++) {
                    if (index == numbOfKmers) {
                        l = -1;
                        i = 4;
                        j = 4;
                        break;
                    }
                    index += 1;
                    placeholder.r = (((i)*60)+array[l]);
                    placeholder.g = (((j)*60)+array[l]);
                    placeholder.b = (((k)*60)+array[l]);
                    returnList.push_back(placeholder);
                }
            }
        }
    }
    ColorList = returnList;
}

/**
 * This method will map a single Kmer to a unique Color in terms of the 
 * Lists which are in the class. If these lists are not initialized, then
 * the map won't work.
 */
Color ColorMap::Map(string kmer) {
    if (ColorList.size() == 0 || Kmers.size() == 0) {
        cerr << "Warning: The map can't be used, until all is initialized!" << endl;
        Color nullElement;
        return nullElement;
    }
    for (int i = 0; i < Kmers.size(); i++) {
        if (Kmers[i] == kmer)
            return ColorList[i];
    }
}

vector<Color> ColorMap::giveColorList() {
    if (ColorList.size() == 0) {
        cerr << "Warning: ColorList is not initialized!" << endl;
    }
    return ColorList;
}

vector<string> ColorMap::giveKmerlist() {
    return Kmers;
}




