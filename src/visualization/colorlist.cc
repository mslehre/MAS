#include <iostream>
#include <vector>
#include <SFML/Graphics/Color.hpp>
#include "colorlist.h"

using namespace std;
using namespace sf;


// complete constructor
colorlist::colorlist(int numbOfKmers) {
    updateList(numbOfKmers);
}

// standard consstructor
colorlist::colorlist() {

}


/*
 * Update method for the Colorlist
 */
void colorlist::updateList(int numbOfKmers) {
    vector<Color> returnList; // the list i use to adjust this as the new List
    Color placeholder; // A placeholder which is needed to programm with rgb values
    int index = 13; // index to count the pushed Colors
    /*
     * In this part of the method i push Colors in the vector which i searched in the
     * web, so that they are well-distinguishable. And the hard coded colors are all
     * different to the out of the algorithm, because the r, g and b values from the algorithm have a 
     * distance of each other by 60, 120 or 180.
     * Link: https://www.rapidtables.com/web/color/RGB_Color.html
     */
    unsigned char DistinguishableCols[13][3] = {
        {255, 0, 0}, // red
        {255, 128, 0}, // orange
        {255, 255, 0}, // yellow
        {128, 255, 0}, // light green
        {0, 255, 0}, // green
        {0, 255, 128}, // dark green
        {0, 255, 255}, // cyan
        {0, 128, 255}, // blue
        {0, 0, 255}, // dark blue
        {128, 0, 255}, // violet
        {255, 0, 255}, // pink
        {255, 0, 128}, // dark pink
        {128, 128, 128} // grey
    };
    for (int i = 0; i < 13; i++) {
        placeholder.r = DistinguishableCols[i][0];
        placeholder.g = DistinguishableCols[i][1];
        placeholder.b = DistinguishableCols[i][2];
        returnList.push_back(placeholder);
        if(numbOfKmers == i + 1) {
            index = i + 1;
            break;
        }
    }
    /*
     * in this part of the method i push Colors in the vector
     * in terms of a algorithm i made for myself.
     * this algorithm is maybe not completed yet.
     */
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
                    placeholder.r = (((i) * 60) + array[l]);
                    placeholder.g = (((j) * 60) + array[l]);
                    placeholder.b = (((k) * 60) + array[l]);
                    returnList.push_back(placeholder);
                }
            }
        }
    }
    list = returnList;
}

// return function for class variable
vector<Color> colorlist::giveList() {
    if (list.size() == 0) {
        cerr << "Warning: ColorList is not initialized!" << endl;
    }
    return list;
}

