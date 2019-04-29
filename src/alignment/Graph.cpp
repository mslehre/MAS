#include "Graph.h"

using namespace std;

// constructor
Graph::Graph(){}

// get StringListSequence
vector<string>& Graph::getStringListSequence(){
    return stringListSequence;
}

// get the length of node (kmer)
unsigned int Graph::getK(){
    return k;
}	

// Method: get vector of edges for all sequences
vector<Edge>& Graph::getEdgesVector(){
    return edgesVector;
}

// Method: get list of nodes only with matches
vector<Node>& Graph::getNodeList() {
    return nodeList;
}

// Method: read fasta file
void Graph::readFastaFiles(std::string nameFile, unsigned int k){
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

// Method: calculate edges and nodes for one sequence
void Graph::calcAdjacentEdges(unsigned int index){
    vector<string>& stringList = getStringListSequence();

    // the last sequence has no next sequence
    if (index == stringList.size()-1) {
        cerr << "It is the last sequence." << endl;
        return;
    }
    // counter for nodes with matches
    unsigned int matches = 0;
    // calculate adjacent edges from all nodes in one sequence
    // list of nodes for the sequence i
    for (unsigned int i = 0; i < nodeListAll.at(index).size(); i++) {
        // list of nodes for the sequence i+1
        for (unsigned int j = 0; j < nodeListAll.at(index + 1).size(); j++) {
            // compare strings of nodes
            if (nodeListAll.at(index).at(i).kmer == nodeListAll.at(index + 1).at(j).kmer) {
                // store begin (Node) and end (Node) of an edge
                Node firstNode  = nodeListAll.at(index).at(i);
                Node secondNode = nodeListAll.at(index + 1).at(j);

                // create edge from sequence i to sequence i+1
                Edge edge;
                edge.first = firstNode;
                edge.second = secondNode;

                //update list of edges
                edgesVector.push_back(edge);

                // update adjacency list for this node
                nodeListAll.at(index).at(i).adjNodes.push_back(secondNode); 

                // pushes only nodes in nodeList with matches
                if (nodeListAll.at(index).at(i).kmer == nodeListAll.at(index + 1).at(j).kmer) {
                    matches = 1;
                }                       
            }                         
        }
        if (matches == 1)
            nodeList.push_back(nodeListAll.at(index).at(i));
        matches = 0;
    }
}

// Method: get number of nodes only with matches
vector<array<unsigned int,2>>& Graph::getNumberOfKmers(){
    // counter to count how much nodes are in a sequence
    unsigned int counter = 0;
    // temporary array for the number of k-mers
    array<unsigned int, 2> arrayTemp;

    if (!nodeList.empty()) {
        // iterate through the list of nodes
        for (vector<Node>::iterator it = nodeList.begin(); it != nodeList.end(); ++it) {
            if (nodeList.size() != 1) {
                ++counter; 
                if ((*it).i != (*(it+1)).i) {
                    arrayTemp = {(*it).i, counter};
                    numberOfKmers.push_back(arrayTemp);
                    counter = 1;
                }   
            } else {    
                arrayTemp = {(*it).i, 1};
                numberOfKmers.push_back(arrayTemp);
                return numberOfKmers;
            }
        }
    } else {
        return numberOfKmers;
    }
    return numberOfKmers;
}

// Method: list of edges
void Graph::calcEdgeList() {
    // calculate list of nodes
    calcNodeList();

    // fill list of edge
    for (unsigned int i = 0; i < nodeListAll.size() - 1; i++) {      
        calcAdjacentEdges(i);
    }
}

// Method: calculate list of nodes
void Graph::calcNodeList() {
    // get list of strings for all sequences
    vector<string>& stringList = getStringListSequence();
  
    // store temporary number of k-mers of nodes for all sequences (isolated nodes as well)
    vector<unsigned int> numberOfKmersTemp;
    // the k-mers are tiled (shift=k)
    // calculate number of nodes for all sequences (isolated nodes as well)
    for (unsigned int i = 0; i < stringList.size(); i++) {
         numberOfKmersTemp.push_back(stringList.at(i).size() / getK());		
    }

    // get length of any k-mer
    unsigned int stringLength = k;
    unsigned int j;
    // empty vector of nodes for the initialization
    vector<Node> emptyNodeVector;
  
    // initialize vector for all nodes
    for (unsigned int i = 0; i < stringList.size(); i++) {
        nodeListAll.push_back(emptyNodeVector);
    }

    // fill nodeListAll with all possible nodes (isolated nodes as well) with properties i,j,kmer
    for (unsigned int i = 0; i < stringList.size(); i++) {
        for (j = 0; j < numberOfKmersTemp.at(i); j++) {
            if (stringList.at(i).length() - k >= j * k){
                // store node in nodeListAll
                nodeListAll.at(i).push_back(Node(i, j, stringList.at(i).substr(j * k, stringLength)));   
            }
        }
    }
}
