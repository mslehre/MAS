#include "Graph.h"
#include <fstream>
#include<string>
#include<vector>
#include<array>
#include<fstream>
#include<iostream>

using namespace std;

// constructor , store k-mer
Graph::Graph(int k){
	kMer = k;
}	

// get StringListSequence
vector<string>& Graph::getStringListSequence(){
	return stringListSequence;
}

// get number k of k-mer
int Graph::getSimpleKOfKmer(){
	return kMer;
}	

// Method: get list of Edges
vector<array<int,3>>& Graph::getEdgeList(){
	return listOfEdges;
}

// Method: reading fasta file
void Graph::readingFastaFiles(std::string nameFile){
	ifstream data (nameFile);										// open file			
																	
	if (!data.is_open()) {
		cout << "Can't open file!" << endl;
	} else {
		std::string line, name, content;
		while (std::getline(data, line).good()) {
			if (line.empty() || line[0] == '>') { 					// Identifier marker
				if (!name.empty()) { 
					stringListSequence.push_back(content);			// push sequence into vector
					name.clear();
				}
				if (!line.empty())
					name = line.substr(1);

					content.clear();
			} else if (!name.empty()) {
						if (line.find(' ') != std::string::npos) { 	// Invalid sequence--no spaces allowed
							name.clear();
							content.clear();
						} else {
							content += line;
						}
					}
		}
		if (!name.empty())
			stringListSequence.push_back(content); 					// push sequence into vector		
	}
}

// Method: get adjacent edges from node
vector<int> Graph::getAdjacentEdge(int seq, int kNum){
	vector<string>& stringList = getStringListSequence();			
	vector<int> adjacentNode;

	if (seq == stringList.size()-1) {								// the last sequence has no next sequence
		cerr << kNum << "It is the last sequence." << endl;
		return adjacentNode;
	}
	
	int kmer = getSimpleKOfKmer(); 
	int position = kmer * kNum;										

	if (position + kmer <= stringList.at(seq).size()) {				
		for (int i=0; i < stringList.at(seq+1).size(); i = i+kmer) {// iteration through the sequence
			if (i+kmer > stringList.at(seq+1).size())
				break;                         
			if (stringList.at(seq).substr(position,kmer) == stringList.at(seq+1).substr(i,kmer))
				adjacentNode.push_back(i/kmer);		
		}
		return adjacentNode;
	} else {
		cerr << kNum << ".k-mer don't exists in sequence " << seq  << "." << endl;
		return adjacentNode; 
	}	
	cerr << kNum << ".k-mer don't exists in sequence " << seq  << "." << endl;
	return adjacentNode;
}

// Method: get Number of k-mer
const vector<int>& Graph::getAmountOfKmer(){
	vector<string>& stringList = getStringListSequence();
	int sizeOfStringList = stringList.size();

	if (!numberOfKmer.empty()) {
		return numberOfKmer; 		
	} else {
		for (int i = 0; i < sizeOfStringList; i++) {
			numberOfKmer.push_back(stringList.at(i).size() / getSimpleKOfKmer());						
		}
	}
	return numberOfKmer; 
}					

// Method: list of edges
void Graph::calcEdgeList() {
	vector<string>& stringList = getStringListSequence();
	const vector<int>& amountKmer = getAmountOfKmer();
	vector<int> adjEdges;
	int j;

	for (int i = 0; i < stringList.size()-1; i++) {
		for (j = 0; j < amountKmer.at(i); j++) {
			adjEdges = getAdjacentEdge(i,j);

			for (auto &k : adjEdges) {
			array<int,3> edge = {i,j,k};
			listOfEdges.push_back(edge);
			}
		}	
	}
}
