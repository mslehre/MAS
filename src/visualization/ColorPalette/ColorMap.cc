#include <string>
#include <vector>
#include <SFML/Graphics/Color.hpp>
#include <array>
#include <cmath>
#include "ColorMap.h"
#include <iostream>

using namespace std;
using namespace sf;

ColorMap::ColorMap(vector<string>& Sequences, int k){
    vector<int> SequenceSizes;
    //Informations about the Graph
    for(int i=0;i<Sequences.size();i++){
        SequenceSizes.push_back((int)floor((Sequences[i].size())/k));
    }

    //a List of Colorvalues with a parallel list of k-mers to compare
    int numbOfKmer = 0;
    for (int i=0;i<SequenceSizes.size();i++)
        numbOfKmer += SequenceSizes[i];
    updateColorList(numbOfKmer);
    vector<string> kmerDeclarations;

    //a boolean for the "got this kmer a color?"-Check and a index for the k-mers per sequence
    bool matched = false;
    int index;
    //The mainmethod of this function
    for (int i=0;i<Sequences.size();i++) {
        index = 0;
        while (index<SequenceSizes[i]) {
            //Comparing all k-mers which got a color already to give the same color
            for (int j=0;j<kmerDeclarations.size();j++) {
                if (kmerDeclarations[j]==Sequences[i].substr(index*k, k)) {
                    matched = true;
                    break;
                }
            }
            //If its a new kmer, then put a new color out of it
            if (!matched) {
                kmerDeclarations.push_back(Sequences[i].substr(index*k, k));
            }
            matched = false;
            index += 1;
        }
    }
    differentKmers = kmerDeclarations;
}

ColorMap::ColorMap(int numbOfKmer){
    vector<Color> returnList;
    Color placeholder;
    int index = 0;
    int array[60];
    for(int i=0;i<60;i++)
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

void ColorMap::updateSequenceLists(vector<string>& Sequences, int k){
    
    vector<int> SequenceSizes;
    //Informations about the Graph
    for(int i=0;i<Sequences.size();i++){
        SequenceSizes[i] = (int)floor((Sequences[i].size())/k);
    }

    //a List of Colorvalues with a parallel list of k-mers to compare
    int numbOfKmer = 0;
    for (int i=0;i<SequenceSizes.size();i++)
        numbOfKmer += SequenceSizes[i];
    updateColorList(numbOfKmer);
    vector<string> kmerDeclarations;

    //a boolean for the "got this kmer a color?"-Check and a index for the k-mers per sequence
    bool matched = false;
    int index;
    
    //The mainmethod of this function
    for (int i=0;i<Sequences.size();i++) {
        index = 0;
        while (index<SequenceSizes[i]) {
            //Comparing all k-mers which got a color already to give the same color
            for (int j=0;j<kmerDeclarations.size();j++) {
                if (kmerDeclarations[j]==Sequences[i].substr(index*k, k)) {
                    matched = true;
                    break;
                }
            }
            //If its a new kmer, then put a new color out of it
            if (!matched) {
                kmerDeclarations.push_back(Sequences[i].substr(index*k, k));
            }
            matched = false;
            index += 1;
        }
    }
    differentKmers = kmerDeclarations;
}



//This method calculate the color list (most possible different colors)
void ColorMap::updateColorList(int numbOfKmer){
    vector<Color> returnList;
    Color placeholder;
    int index = 0;
    int array[60];
    for(int i=0;i<60;i++)
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


Color ColorMap::Map(string kmer){
    if(ColorList.size()==0 || differentKmers.size()==0){
        cerr << "Warning: The map can't be used, until all is initialized!" << endl;
        Color nullElement;
        return nullElement;
    }
    for(int i = 0;i<differentKmers.size();i++){
        if(differentKmers[i]==kmer){
            return ColorList[i];
        }
    }
}

vector<Color> ColorMap::giveColorList(){
    if(ColorList.size()==0){
        cerr << "Warning: ColorList is not initialized!" << endl;
    }
    return ColorList;
}

vector<string> ColorMap::giveKmerlist(){
    return differentKmers;
}




