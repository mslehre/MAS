#include "Graph.h"
#include <fstream>
#include<string>
#include<vector>
#include<array>
#include<fstream>
#include<iostream>

using namespace std;

// constructor
Graph::Graph(int k){ kMer = k;}									// save k-mer

// get StringListSequence
vector<string>& Graph::getStringListSequence(){return stringListSequence;}

// get splitString
vector<vector<string>>& Graph::getSplitString(){return splitString;}

// Method: reading fasta file
void Graph::readingFastaFiles(std::string nameFile){
	
	ifstream data (nameFile);									// open file
	if(!data.is_open()){
		cout << "Can't open file!" << endl;
		
	}else{
		std::string line, name, content;
			while( std::getline( data, line ).good() ){
				if( line.empty() || line[0] == '>' ){ 					// Identifier marker
					if( !name.empty() ){ 
						stringListSequence.push_back(content);	// push sequence into vector
						name.clear();
					}
					if( !line.empty() ){
						name = line.substr(1);
					}
					content.clear();
				} else if( !name.empty() ){
						if( line.find(' ') != std::string::npos ){ 		// Invalid sequence--no spaces allowed
							name.clear();
							content.clear();
						} else {
							content += line;
						}
					}
			}
			if( !name.empty() ){ 
				stringListSequence.push_back(content);			// push sequence into vector		
			}	
	}
	vector<string> empty;										// create empty vector for strings
	int move;
	int numStrings=stringListSequence.size();					// amount of sequences
	// create vector of vectors for the sequences
	for(int i=0; i<numStrings; i++){								// for-loop till the amount of sequences
		splitString.push_back(empty);							// initialization of splitString
		for(int j=0; j<stringListSequence.at(i).length(); j=j+kMer){		// for-loop within a sequence
				if(j+kMer>=stringListSequence.at(i).length()){		// check if you are out of the length of the sequence
					move=stringListSequence.at(i).length()-j;  
				}
				else{
					move=kMer;
				}
				splitString.at(i).push_back(stringListSequence.at(i).substr(j,move));	// push substring for one sequence
		}
	} 
}
// Method: get number of k-mer
const vector<int>& Graph::getNumberOfKmer(){
	int numStrings=stringListSequence.size();					// amount of sequences
	for(int i=0; i<numStrings; i++){								// for-loop to get number of k-mer
		numberOfKmer.push_back(splitString.at(i).size());
        }
	return numberOfKmer;
}
// Method: list of edges
void Graph::calcGetEdgeList() {
	vector<int>& vec=numberOfKmer;
	int n=vec.size();
	int counter=0;

	for(int i=0; i<n-1; i++){
		for(int j=0; j<vec.at(i); j++){
			for(int k=0; k<vec.at(i+1); k++){
					if(splitString.at(i).at(j)==splitString.at(i+1).at(k)   && splitString.at(i).at(j).length() == kMer ){
						array<int,3> edge = {i,j,k};
						listOfEdges.push_back(edge);
					}	
				}
			}
		}				
}

vector<array<int,3>>& Graph::getEdgeList(){
	return listOfEdges;
}
	
	
	
	
