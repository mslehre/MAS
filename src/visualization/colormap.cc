#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <SFML/Graphics/Color.hpp>
#include "colormap.h"

using namespace std;
using namespace sf;

// complete constructor
colormap::colormap(vector<string>& givenKmers, vector<Color>& givenColorlist) {
    updateAssignment(givenKmers, givenColorlist);
}

// standard constructor
colormap::colormap() {

}

/*
 * this method initialize the unordered map colorAssignment.
 */
void colormap::updateAssignment(vector<string>& givenKmers, vector<Color>& givenColorlist) {
    // bugcatching for wrong arguments
    if (givenKmers.size() != givenColorlist.size()) {
        cerr << "Warning: the lists haven't the same size! it can't be initialized." << endl;
    } else {
        if (colorAssignment.size() > 0) {
            colorAssignment.clear();
        }
        for (unsigned int i = 0; i < givenColorlist.size(); i++) {
            colorAssignment[givenKmers[i]] = givenColorlist[i];
        }
    }
}


/*
 * this method will map a single Kmer (string) to a unique Color value
 * with the class functions of the unorderd map.
 */
Color colormap::Map(string kmer) {
    if(colorAssignment.size() == 0) {
        cerr << "error: updateAssignment is not initialized!" << endl;
        Color nullValue;
        return nullValue;
    } else {
        Color value = colorAssignment.at(kmer);
        return value;
    }
}

unordered_map<string,Color> colormap::giveAssignment() {
    return colorAssignment;
}


