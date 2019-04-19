#include "Graph.h"
#include<fstream>
#include<string>
#include<vector>
#include<array>
#include<fstream>
#include<iostream>
#include "Node.h"

using namespace std;

// constructor
Graph::Graph(){}

// get StringListSequence
vector<string>& Graph::getStringListSequence(){
    return stringListSequence;
}

// get the length of node (kmer)
int Graph::getK(){
    return k;
}	

// Method: get nodeList
vector<vector<Node>>& Graph::getNodeList(){
    return nodeList;
}

// Method: get list of Edges
vector<vector<vector<Node>>>& Graph::getEdgeList(){
    return listOfEdges;
}

// Method: read fasta file
void Graph::readFastaFiles(std::string nameFile, int k){
    this->k = k;

    ifstream data (nameFile);                                         			
	// open file																
    if (!data.is_open()) {
        cout << "Can't open file!" << endl;
	} else {
        std::string line, name, content;
        while (std::getline(data, line).good()) {
            // Identifier marker
            if (line.empty() || line[0] == '>') {                       
                if (!name.empty()) {
                    // push sequence into vector 
                    stringListSequence.push_back(content);              
                    name.clear();
                }
                if (!line.empty()) {
                    name = line.substr(1);
                }
                    content.clear();
                } else if (!name.empty()) {
                    // Invalid sequence--no spaces allowed
                    if (line.find(' ') != std::string::npos) {          
                        name.clear();
                        content.clear();
                    } else {
                        content += line;
                    }
                }
        }
        if (!name.empty())
            // push sequence into vector
            stringListSequence.push_back(content);                      		
	}
    calcEdgeList();
}

// Method: get vector of adjacent edges from all nodes in one sequence
vector<vector<Node>> Graph::getAdjacentEdges(unsigned int index){			
    vector<vector<Node>> adjacentNodes;
    vector<Node> emptyVecNode;
    vector<string>& stringList = getStringListSequence();

    // the last sequence has no next sequence
    if (index == stringList.size()-1) {                                 
        cerr << "It is the last sequence." << endl;
        return adjacentNodes;
    }
    // calculate adjacent edges from all nodes in one sequence 
    for (unsigned int i = 0; i < nodeList.at(index).size(); i++) {
        // initialize adjacentNode
        adjacentNodes.push_back(emptyVecNode);
        for (unsigned int j = 0; j < nodeList.at(index + 1).size(); j++) {
            // compare strings of nodes
            if (nodeList.at(index).at(i).kmer == nodeList.at(index + 1).at(j).kmer){
                adjacentNodes.at(i).push_back(nodeList.at(index + 1).at(j));  
            }            
        }
    }
    return adjacentNodes;
}

// Method: get amount of nodes for all sequences
const vector<unsigned int>& Graph::getAmountOfKmer(){
    vector<string>& stringList = getStringListSequence();
    int sizeOfStringList = stringList.size();

    if (!numberOfKmers.empty()) {
        return numberOfKmers; 		
    } else {
        for (int i = 0; i < sizeOfStringList; i++) {
            numberOfKmers.push_back(stringList.at(i).size() / getK());						
        }
    }
    return numberOfKmers; 
}					

// Method: list of edges
void Graph::calcEdgeList() {
    // calculate list of nodes
    calcNodeList();

    // fill edge list
    for (unsigned int i = 0; i < nodeList.size() - 1; i++) {      
            listOfEdges.push_back(getAdjacentEdges(i));
            }
        }	

// Method:: calculate list of nodes
void Graph::calcNodeList() {
    vector<string>& stringList = getStringListSequence();
    const vector<unsigned int>& amountKmer = getAmountOfKmer();
    int stringLength = k;
    unsigned int j;
    vector<Node> emptyNodeVector;
  
    // initialize vector of nodes
    for (unsigned int i = 0; i < stringList.size(); i++) {
        nodeList.push_back(emptyNodeVector);
    }
    
    // fill the vector of nodes with all possible nodes (with properties)
    for (unsigned int i = 0; i < stringList.size(); i++) {
        for (j = 0; j < amountKmer.at(i); j++) {
            if (stringList.at(i).length() - k >= j * k){
                nodeList.at(i).push_back(Node(i, j, stringList.at(i).substr(j * k, stringLength)));     
            }
        }
    }
}
