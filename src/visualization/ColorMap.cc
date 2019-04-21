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
ColorMap::ColorMap(vector<string>& Sequences, int k){
    ///< This is a variable which save the number of Kmers per Sequence which we have
    vector<int> SequenceSizes;
    for (int i=0;i<Sequences.size();i++)
        SequenceSizes[i] = (int)floor((Sequences[i].size())/k);

    ///< This is a variable which save the number of Kmers
    int numbOfKmer = 0;
    for (int i=0;i<SequenceSizes.size();i++)
        numbOfKmer += SequenceSizes[i];
    updateColorList(numbOfKmer);
    ///< This variable is the output List
    vector<string> kmerDeclarations;

    ///< a boolean for the "got this kmer a color?"-Check
    bool matched = false;
    ///< a index for the k-mers per sequence
    int index;
    
    /**
     * This part of the method will push all Kmers in the List, which are not in the list already.
     */
    for (int i=0;i<Sequences.size();i++) {
        index = 0;
        while (index<SequenceSizes[i]) {
            ///< Comparing all k-mers to know if the Kmer is already in the list
            for (int j=0;j<kmerDeclarations.size();j++) {
                if (kmerDeclarations[j]==Sequences[i].substr(index*k, k)) {
                    matched = true;
                    break;
                }
            }
            ///< If its a new kmer, so we push it here
            if (!matched)
                kmerDeclarations.push_back(Sequences[i].substr(index*k, k));
            matched = false;
            index += 1;
        }
    }
    differentKmers = kmerDeclarations;
}

/**
 * This Method will make a vector of Colors in terms of a number, which defines the Length of the 
 * length of the List. Then it will initialize ColorList with it. In our case the argument 
 * describes the number of Kmers we are looking for to map.
 */
ColorMap::ColorMap(int numbOfKmer){
    vector<Color> returnList; ///< the list i use to adjust this as the new List
    Color placeholder; ///< A placeholder which is needed to programm with rgb values
    /**
     * In this part of the method i push Colors in the List which i searched in the
     * web, so that they are well different.
     */
    placeholder.r = 255;
    placeholder.g = 0;
    placeholder.b = 0;
    returnList.push_back(placeholder);
    placeholder.g = 128;
    returnList.push_back(placeholder);
    placeholder.g = 255;
    returnList.push_back(placeholder);
    placeholder.r = 128;
    returnList.push_back(placeholder);
    placeholder.r = 0;
    returnList.push_back(placeholder);
    placeholder.b = 128;
    returnList.push_back(placeholder);
    placeholder.b = 255;
    returnList.push_back(placeholder);
    placeholder.g = 128;
    returnList.push_back(placeholder);
    placeholder.g = 0;
    returnList.push_back(placeholder);
    placeholder.r = 128;
    returnList.push_back(placeholder);
    placeholder.r = 255;
    returnList.push_back(placeholder);
    placeholder.b = 128;
    returnList.push_back(placeholder);
    placeholder.r = 128;
    placeholder.g = 128;
    placeholder.b = 128;
    returnList.push_back(placeholder);
    /**
     * In this part of the method i push Colors in terms of a algorithm i made for myself.
     * This algorithm is maybe not completed yet.
     */
    int index = 0; ///< i use this index to count about how much Colors are pushed.
    int array[60];
    for (int i=0;i<60;i++)
        array[i] = 11 + i;
    for (int l=59;l>=0;l--) {
        for (int i=0;i<4;i++) {
            for (int j=0;j<4;j++) {
                for (int k=0;k<4;k++) {
                    if (index==numbOfKmer) {
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

ColorMap::ColorMap(){

}

/**
 * This Method will compute in terms of the argument sequences and the k, all kmers we are looking for and call
 * the method which compute us in terms of this number a Colormap. Then the method will compute
 * all different Kmers and push them in a List. We'll use this list to update differentKmers.
 */
void ColorMap::updateSequenceLists(vector<string>& Sequences, int k){
    ///< This is a variable which save the number of Kmers per Sequence which we have
    vector<int> SequenceSizes;
    for (int i=0;i<Sequences.size();i++)
        SequenceSizes[i] = (int)floor((Sequences[i].size())/k);

    ///< This is a variable which save the number of Kmers
    int numbOfKmer = 0;
    for (int i=0;i<SequenceSizes.size();i++)
        numbOfKmer += SequenceSizes[i];
    updateColorList(numbOfKmer);
    ///< This variable is the output List
    vector<string> kmerDeclarations;

    ///< a boolean for the "got this kmer a color?"-Check
    bool matched = false;
    ///< a index for the k-mers per sequence
    int index;
    
    /**
     * This part of the method will push all Kmers in the List, which are not in the list already.
     */
    for (int i=0;i<Sequences.size();i++) {
        index = 0;
        while (index<SequenceSizes[i]) {
            ///< Comparing all k-mers to know if the Kmer is already in the list
            for (int j=0;j<kmerDeclarations.size();j++) {
                if (kmerDeclarations[j]==Sequences[i].substr(index*k, k)) {
                    matched = true;
                    break;
                }
            }
            ///< If its a new kmer, so we push it here
            if (!matched)
                kmerDeclarations.push_back(Sequences[i].substr(index*k, k));
            matched = false;
            index += 1;
        }
    }
    differentKmers = kmerDeclarations;
}

/**
 * This Method will make a vector of Colors in terms of a number, which defines the Length of the 
 * length of the List. Then it will update our ColorList with it. In our case the argument 
 * describes the number of Kmers we are looking for to map.
 */
void ColorMap::updateColorList(int numbOfKmer){
    vector<Color> returnList; ///< the list i use to adjust this as the new List
    Color placeholder; ///< A placeholder which is needed to programm with rgb values
    /**
     * In this part of the method i push Colors in the List which i searched in the
     * web, so that they are well different.
     */
    placeholder.r = 255;
    placeholder.g = 0;
    placeholder.b = 0;
    returnList.push_back(placeholder);
    placeholder.g = 128;
    returnList.push_back(placeholder);
    placeholder.g = 255;
    returnList.push_back(placeholder);
    placeholder.r = 128;
    returnList.push_back(placeholder);
    placeholder.r = 0;
    returnList.push_back(placeholder);
    placeholder.b = 128;
    returnList.push_back(placeholder);
    placeholder.b = 255;
    returnList.push_back(placeholder);
    placeholder.g = 128;
    returnList.push_back(placeholder);
    placeholder.g = 0;
    returnList.push_back(placeholder);
    placeholder.r = 128;
    returnList.push_back(placeholder);
    placeholder.r = 255;
    returnList.push_back(placeholder);
    placeholder.b = 128;
    returnList.push_back(placeholder);
    placeholder.r = 128;
    placeholder.g = 128;
    placeholder.b = 128;
    returnList.push_back(placeholder);
    /**
     * In this part of the method i push Colors in terms of a algorithm i made for myself.
     * This algorithm is maybe not completed yet.
     */
    int index = 0; ///< i use this index to count about how much Colors are pushed.
    int array[60];
    for (int i=0;i<60;i++)
        array[i] = 11 + i;
    for (int l=59;l>=0;l--) {
        for (int i=0;i<4;i++) {
            for (int j=0;j<4;j++) {
                for (int k=0;k<4;k++) {
                    if (index==numbOfKmer) {
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
Color ColorMap::Map(string kmer){
    if (ColorList.size()==0 || differentKmers.size()==0) {
        cerr << "Warning: The map can't be used, until all is initialized!" << endl;
        Color nullElement;
        return nullElement;
    }
    for (int i = 0;i<differentKmers.size();i++) {
        if (differentKmers[i]==kmer)
            return ColorList[i];
    }
}

vector<Color> ColorMap::giveColorList(){
    if (ColorList.size()==0) {
        cerr << "Warning: ColorList is not initialized!" << endl;
    }
    return ColorList;
}

vector<string> ColorMap::giveKmerlist(){
    return differentKmers;
}




