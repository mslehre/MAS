#include <iostream>
#include <random>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <SFML/Graphics.hpp>
#include "kmercolor.h"

// This programm create one multiple fasta file with S sequences of lenght L. 
// If there are more then one sequence then we have mutants with mutation probabilty P. 
// Call skript with: ./main S L P
// Exemple: ./main 5 100 0.3

using namespace std;

int main(int argc, char *argv[]){	
	string a = "hallo";
	bool ex = a[1]=='a';
	bool ey = a[1]=='v';	
	cout << a[1] <<a[4]<<a.size()<<ex<<ey<<endl;
	cout << "hallo welt!" <<endl;
	
}

