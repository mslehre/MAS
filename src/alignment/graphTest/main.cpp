#include<iostream>
#include<vector>
#include<string>
#include "Graph.h"

using namespace std;

int main(int argc, char **argv){
	// example create object from class Graph with 2-mer
	Graph g(2);	
																		 
	// reading fasta file
	if (argc != 2) {
		cerr << "Please start your program with: ./main [fileName.fa]" << endl;
		return -1;
	}
	g.readingFastaFiles(argv[1]);							                        	
	
	cout << "Just an example: with " << g.getK() << "-mer.\n" <<  endl;
	cout << "output sequences:" << endl;
	// output sequences
	for (const string &element : g.getStringListSequence()) {
		cout << element << endl;
	}  	

	for(const array<int,3>& element : g.getEdgeList()){
		for(const int& a :element ){
			cout << a << "  ";
		}
		cout << "" << endl;
	}
	return 0;
}
