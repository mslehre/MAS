#include<iostream>
#include<vector>
#include<string>
#include "Graph.h"

using namespace std;

int main(int argc, char **argv){

	Graph g(3);																			// example create object from class Graph with 2-mer 

	if(argc != 2){cerr << "Please start your program with: ./main [fileName.fa]" << endl; return -1;}

	g.readingFastaFiles(argv[1]);							                        	// reading fasta file
	
	cout << "Just an example: with " << g.getSimpleKOfKmer() << "-mer.\n" <<  endl;
	cout << "output sequences:" << endl;
	for(const string &element : g.getStringListSequence()){cout << element << endl;}  	// output sequences
		
	cout << "############" << endl;
	cout << "output split string from sequences:" << endl;
	for(const auto &vec : g.getSplitString()){											// output split string from sequences
		for(const auto &element : vec){
			cout << element << " ";
		}
		cout << "" << endl;
	}

	cout << "############" << endl;
	cout << "amount of k-mer of an sequence:" << endl;
	for(const int &element : g.getNumberOfKmer()){										// output length of sequences
		cout << element << " ";
	}
	
	cout << "\n############" << endl;

	g.calcGetEdgeList();																// calculate Edge List

	cout << "possible edges: (a,b,c), a index for sequence, b index which k-mer, c index which k-mer in the next sequence, " << endl;
	for(const auto &arrayElement : g.getEdgeList()){
		for(const auto &element : arrayElement){
			cout << element << " ";
		}
		cout << "" << endl;
	}
	return 0;
}
