#include <iostream>
#include <random>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "kmercolor.h"

// This programm create one multiple fasta file with S sequences of lenght L. 
// If there are more then one sequence then we have mutants with mutation probabilty P. 
// Call skript with: ./main S L P
// Exemple: ./main 5 100 0.3

using namespace std;

int main(int argc, char *argv[]){	
	//string a = "hallo";
	//bool ex = a[1]=='a';
	//bool ey = a[1]=='v';	
	//cout << a[1] <<a[4]<<a.size()<<ex<<ey<<endl;
	long a = 255*255*255;
	bool b;
	for(int i=1;i<40;i++){
		b = a>pow(4,i);
		cout << b << " in the with k-mer size "<<i<< " with possible elements: "<<pow(4,i)<<endl;
	}
	cout << "hallo welt!" <<endl;
	sf::Color v = kmerPatternColor("CGC");
	cout << (int)v.r << (int)v.g<<(int)v.r <<endl;
}

