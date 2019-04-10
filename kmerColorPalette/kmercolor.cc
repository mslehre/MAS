#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <SFML/Graphics/Color.hpp>
#include "kmercolor.h"

using namespace std;
using namespace sf;


int charRead(char character){
	if(character=='A'){
		return 0;	
	} else if(character == 'C'){
		return 1;	
	} else if(character == 'T'){
		return 2;
	} else if(character == 'G'){
		return 3;
	}
}

sf::Color kmerPatternColor(string kmer){
	int kmerSize = kmer.size();
	Color returnValue(2,3,4,5);	
	if(kmerSize==3){
		//do something declared	
		vector<int> characterMap;
		characterMap.push_back(60);
		characterMap.push_back(120);
		characterMap.push_back(180);
		characterMap.push_back(240);
		returnValue.r = characterMap[charRead(kmer[0])];
		returnValue.g = characterMap[charRead(kmer[1])];
		returnValue.b = characterMap[charRead(kmer[2])];
		return returnValue;
	} else {
		//do something automatically
		
	}
}

