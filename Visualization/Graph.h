
#pragma once

#include<string>
#include<vector>
#include<array>
#include<fstream>

class Graph {
	private:
		int kMer;											// number k mer
		std::vector<int> numberOfKmer;						// vector of number of k-mer
		std::vector<std::array<int,3>> listOfEdges;			// vector of edges (as array with size 3)
		std::vector<std::string> stringListSequence;			// vector of strings for the sequences
		std::vector<std::vector<std::string>> splitString;		// vector of vectors for splitted string
		
	public:
	    Graph(int k);										// constructor
		void readingFastaFiles(std::string nameFile);			// Method: reading fasta file
		const std::vector<int>& getNumberOfKmer();			// Method: get Number of k-mer
		void calcGetEdgeList(); 								// Method: list of edges
		std::vector<std::string>& getStringListSequence();		// Method: get StringListSequence
		std::vector<std::vector<std::string>>& getSplitString();	// Method: get splitString
		
		std::vector<std::array<int,3>>& getEdgeList();

	
	
};
