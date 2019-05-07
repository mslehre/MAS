#include "Graph.h"

using namespace std;

// constructor
Graph::Graph(){}

// Method: get number of secquences
unsigned int Graph::getNumberOfSequences() {
    return nodes.at(nodes.size()-1).i;
}
// Method: get vector of nodes with matches
vector<Node>& Graph::getNodes() {
    return nodes;
}

// Method: get number of nodes
unsigned int Graph::getNumberOfNodes(unsigned int sequence){
    unsigned int numberOfNodes;
    for (unsigned int i = 0; i < nodes.size(); i++){
        if (nodes.at(i).i == sequence)
            numberOfNodes++;
    }
    return numberOfNodes;
} 

// Method: get vector of edges for all sequences
vector<Edge>& Graph::getEdges(){
    return edges;
}

// Method: read fasta file
void Graph::readFastaFiles(std::string nameFile, unsigned int k){
    // store length of k-mer
    this->k = k;
    // vector of strings for sequences
    vector<string> stringListSequence;

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

        // calcualte nodeListAll
        calcNodeList(stringListSequence);
	}  
}

// Method: calculate list of nodes
void Graph::calcNodeList(vector<string>& stringList) {
    // temporary vector of nodes
    vector<Node> nodeListAll;

    // store temporary number of k-mers of nodes for all sequences (isolated nodes as well)
    vector<unsigned int> numberOfKmersTemp;
    // the k-mers are tiled (shift=k)
    // calculate number of nodes for all sequences (isolated nodes as well)
    for (unsigned int i = 0; i < stringList.size(); i++) {
         numberOfKmersTemp.push_back(stringList.at(i).size() / k);		
    }

    // get length of any k-mer
    unsigned int stringLength = k;
    unsigned int j;
    
    // nodeListAll with isolated nodes as well
    for (unsigned int i = 0; i < stringList.size(); i++) {
        for (j = 0; j < numberOfKmersTemp.at(i); j++) {
            if (stringList.at(i).length() - k >= j * k){
                // store node in nodeListAll
                nodeListAll.push_back(Node(i, j, stringList.at(i).substr(j * k, stringLength)));
            }
        }
    }
    // vector for matches
    vector<bool> matches;
    // store if node had a match
    bool matched;
    // For-Loop if node has a match: then true else false
    for (unsigned int m = 0; m < nodeListAll.size(); m++) {
        matched = false;
        for (unsigned int n = 0; n < nodeListAll.size(); n++) {
                if (nodeListAll.at(m).kmer == nodeListAll.at(n).kmer && nodeListAll.at(m).i != nodeListAll.at(n).i) {
                    if (nodeListAll.at(n).i == nodeListAll.at(m).i + 1 || nodeListAll.at(n).i == nodeListAll.at(m).i - 1 ) {
                        matched = true;
                    }
                }
        }
        matches.push_back(matched); 
    }
    // push node in nodes only with match
    for (unsigned int m = 0; m < nodeListAll.size(); m++) {
        if (matches.at(m))
            nodes.push_back(nodeListAll.at(m)); 
    }
    // counters to store row and column for For-Loop
    unsigned int counter_i = 0;
    unsigned int counter_j = 0;

    // rewrite index of row and column
    for(unsigned int i = 0; i < nodes.size(); i++) {
        if (nodes.at(i).i != counter_i) {
            counter_j = 0;
            counter_i++;
        }
        nodes.at(i).j = counter_j;
        counter_j++;
    }
    
    // index to store the begin of every sequence
    vector<unsigned int> index;
    // index to store the begin of every sequence
    unsigned int counter = 0;
    index.push_back(0);
    // push index into vector
    for(unsigned int i = 0; i < nodes.size(); i++) {
        if (nodes.at(i).i != counter) {
            index.push_back(i);
            counter++;
        }
    }
    // push the size of nodes for the last index
    index.push_back(nodes.size());
   
    // create adjacency vector and edges
    for (unsigned int i = 0; i < index.size() - 2; i++) {
        for (unsigned m = index.at(i); m < index.at(i + 1); m++) {
            for (unsigned n = index.at(i + 1); n < index.at(i + 2); n++) {
                // only nodes with the same k-mer
                if (nodes.at(m).kmer == nodes.at(n).kmer) {
                    nodes.at(m).adjNodes.push_back(&nodes.at(n));
                    // create edge
                    Edge edge;
                    edge.first = &nodes.at(m); 
                    edge.second = &nodes.at(n);
                    // push edge into edges
                    edges.push_back(edge);             
                }
            }
        }
    }
} 
