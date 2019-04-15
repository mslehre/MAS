#include <string>
#include <vector>
#include <SFML/Graphics/Color.hpp>
#include <array>
#include "src/alignment/Graph.h"
#include "kmercolor.h"
#include <iostream>

using namespace std;
using namespace sf;

//needed to map unique from Alphabet to integers
int charRead(char character){
    if (character=='A')
        return 0;
    else if(character == 'C')
        return 1;
    else if(character == 'T')
        return 2;
    else if(character == 'G')
        return 3;
    
}

//This is the Method 1: based on mapping single K-mers - not completed
Color ColorBasedOnMapping(string kmer){
    int kmerSize = kmer.size();
    Color returnValue;
    if (kmerSize==3) {
        vector<int> characterMap;
        characterMap.push_back(60);
        characterMap.push_back(120);
        characterMap.push_back(180);
        characterMap.push_back(240);
        returnValue.r = characterMap[charRead(kmer[0])];
        returnValue.g = characterMap[charRead(kmer[1])];
        returnValue.b = characterMap[charRead(kmer[2])];
        return returnValue;
    }
}


//This method calculate the color list (most possible different colors)
vector<vector<int>> giveColorList(int numbOfKmer){
    vector<vector<int>> returnList;
    vector<int> placeholder;
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
                    placeholder.push_back(((i)*60)+array[l]);
                    placeholder.push_back(((j)*60)+array[l]);
                    placeholder.push_back(((k)*60)+array[l]);
                    returnList.push_back(placeholder);
                    placeholder.clear();
                }
            }
        }
    }
    return returnList;
}

//This is the Method 2: based on mapping all Kmers of the whole Graph - completed
vector<vector<Color>> ColorBasedOnGraph(Graph& copiedGraph){
    //Placeholder for the outputformal "Color"
    Color placeholder;
    vector<vector<Color>> output;

    //Informations about the Graph
    int k = copiedGraph.getSimpleKOfKmer();
    vector<int> SequenceSize = copiedGraph.getAmountOfKmer();
    vector<string>& Sequences = copiedGraph.getStringListSequence();
    //iteration to ignore the unnecessary end of each sequence
    for (int i = 0;i<SequenceSize.size();i++) {
        if (Sequences[i].substr(k*(SequenceSize[i]-1),k).size()!=k)
            SequenceSize[i] -= 1;
    }

    //a List of Colorvalues with a parallel list of k-mers to compare
    int numbOfKmer = 0;
    for (int i=0;i<SequenceSize.size();i++)
        numbOfKmer += SequenceSize[i];
    vector<vector<int>> ColorList = giveColorList(numbOfKmer);
    vector<string> kmerDeclarations;

    //a boolean for the "got this kmer a color?"-Check and a index for the k-mers per sequence
    bool matched = false;
    int index;
    
    //The mainmethod of this function
    for (int i=0;i<Sequences.size();i++) {
        vector<Color> filler;
        output.push_back(filler);
        index = 0;
        while (index<SequenceSize[i]) {
            //Comparing all k-mers which got a color already to give the same color
            for (int j=0;j<kmerDeclarations.size();j++) {
                if (kmerDeclarations[j]==Sequences[i].substr(index*k, k)) {
                    placeholder.r = ColorList[j][0];
                    placeholder.g = ColorList[j][1];
                    placeholder.b = ColorList[j][2];
                    output[i].push_back(placeholder);
                    matched = true;
                    break;
                }
            }
            //If its a new kmer, then put a new color out of it
            if (!matched) {
                placeholder.r = ColorList[kmerDeclarations.size()][0];
                placeholder.g = ColorList[kmerDeclarations.size()][1];
                placeholder.b = ColorList[kmerDeclarations.size()][2];
                output[i].push_back(placeholder);
                kmerDeclarations.push_back(Sequences[i].substr(index*k, k));
            }
            matched = false;
            index += 1;
        }
    }
    return output;
}

