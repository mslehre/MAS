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

        // calcualte nodeListAll with all possible nodes (isolated nodes as well)
        calcNodeList();
        // calculate the list of edges
        calcEdgeList();
	}  
}

// Method: calculate edges and nodes for one sequence
void Graph::calcHelpAdjacentEdges(unsigned int index){
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

                // update adjacency list for this node
                nodeListAll.at(index).at(i).adjNodes.push_back(secondNode); 

                //helpList.push_back()
                
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
vector<int>& Graph::getNumberOfKmers(){
    return numberOfKmers;
}

// Method: list of edges
void Graph::calcEdgeList() {

    // calculate nodeList only with matches
    for (unsigned int i = 0; i < nodeListAll.size() - 1; i++) {      
        calcHelpAdjacentEdges(i);
    }
    
    vector<Edge> edgesVec; 
    // create list of edges
    for (auto &node1 : nodeList ) {
        for (auto &node2 : node1.adjNodes) {
            Edge edge;
            edge.first = node1;
            edge.second = node2;
            edgesVector.push_back(edge);
        }
    }
    // store temporary nodeList
    vector<Node> tempNodeList;
    for(auto edge : edgesVector) {
        tempNodeList.push_back(edge.first);
        tempNodeList.push_back(edge.second);
    }
    // store only nodes one time
    unsigned int ma = 0;
    for (unsigned int i = 0; i < tempNodeList.size(); i++) {
        unsigned int gi = tempNodeList.at(i).i;
        unsigned int gj = tempNodeList.at(i).j;

        for (auto &n : helpList) {
            if (n.i == gi && n.j == gj)
                ma = 1;
        }
        if (ma != 1)
            helpList.push_back(tempNodeList.at(i));
        ma = 0;
    }

    // sort index i for row
    sort(helpList.begin(), helpList.end(),
			[](const Node& x, const Node& y) {
					return x.i < y.i;
			});

    if (helpList.empty())
        return;
    
    unsigned int counter = 0;
    unsigned int value = helpList.at(0).i;

    for (unsigned int i = 0; i < helpList.size() ; i++) {
        if (helpList.at(i).i == value) {
            ++counter;
            if (i+1 == helpList.size())
                numberOfKmers.push_back(counter);
        } else {
            value = helpList.at(i).i;
            numberOfKmers.push_back(counter);
            counter = 1;
            if (i+1 == helpList.size())
                numberOfKmers.push_back(counter);
        }
    }

    // empty vector of nodes for the initialization
    vector<Node> emptyNodeVector;
  
    nodeListAll.clear();

    // initialize vector for all nodes
    for (unsigned int i = 0; i < numberOfKmers.size(); i++) {
        nodeListAll.push_back(emptyNodeVector);
    }

    counter = 0;
    for (unsigned int i = 0; i < numberOfKmers.size(); i++) {
        for (unsigned int j = counter + numberOfKmers.at   ; j != -1 ;  ) {
            cout << j << endl;
            nodeListAll.at(i).push_back(helpList.at(j));
            counter = numberOfKmers.at(i);
        }
        
        cout << numberOfKmers.at(i) << endl;
    }
    
   
/*
    // sort index j for row
    for (auto &vec : nodeListAll) {
    sort(vec.begin(), vec.end(),
			[](const Node& x, const Node& y) {
					return x.j < y.j;
			});
    }

    for (auto &n : nodeListAll ) {
        for (auto &m : n) {
            cout <<  "  (" << m.i << " , " << m.j << ")  "; 

        }
        cout << endl;



    }

*/

    
/*
    vector<vector<Node>> tempNodeList;
    vector<array<unsigned int,2>> numberK = getNumberOfKmers();
    cout << "Anzahl wieviele Sequenzen nur mit Matches: " << numberK.size()  << endl;

    // empty vector of nodes for the initialization
    vector<Node> emptyNodeVector;
  
    // initialize vector for nodes only with matches
    for (unsigned int i = 0; i <  numberK.size()+1; i++) {
        tempNodeList.push_back(emptyNodeVector);
    }

    if (!edgesVector.empty()) {
        unsigned int gi = edgesVector.at(0).first.i;
        int counterI = 0;
        tempNodeList.at(0).push_back(edgesVector.at(0).first);
        tempNodeList.at(1).push_back(edgesVector.at(0).second);
        unsigned matchA;
        unsigned matchB;
        
        for (unsigned int i = 1; i < edgesVector.size() ;i++) {
            if (edgesVector.at(i).first.i == gi) {
                for (auto &node: tempNodeList.at(counterI)) {
                    if (node.j == edgesVector.at(i).first.j) {
                        matchA = 1;
                    }
                }

                for (auto &node: tempNodeList.at(counterI+1)) {
                    if (node.j == edgesVector.at(i).second.j) {
                        matchB = 1;
                    }
                }
           
                if (matchA != 1) {
                    tempNodeList.at(counterI).push_back(edgesVector.at(i).first);
                } 

                if (matchB != 1) {
                    tempNodeList.at(counterI+1).push_back(edgesVector.at(i).second);
                }
                matchA = 0;
                matchB = 0; 
            }
                 
            if (edgesVector.at(i).first.i != gi) {   
                gi = edgesVector.at(i).first.i;
                counterI = counterI + 1;

                for (auto &node: tempNodeList.at(counterI)) {
                    if (node.j == edgesVector.at(i).first.j) {
                        matchA = 1;
                    }
                }

                for (auto &node: tempNodeList.at(counterI+1)) {
                    if (node.j == edgesVector.at(i).second.j) {
                        matchB = 1;
                    }
                }
           
                if (matchA != 1) {
                    tempNodeList.at(counterI).push_back(edgesVector.at(i).first);
                } 

                if (matchB != 1) {
                    tempNodeList.at(counterI+1).push_back(edgesVector.at(i).second);
                }
                matchA = 0;
                matchB = 0; 
            }
        }
    }


*/











   /* // rewrite index i and j for nodeList for drawing
    if (nodeList.size() != 0) {
        int gi = nodeList.at(0).i; 
        nodeList.at(0).i = 0;
        nodeList.at(0).j = 0;
        int gj = 0;

        for (int i = 1; i < nodeList.size(); i++) {
            if (nodeList.at(i).i == gi) {
                nodeList.at(i).i = nodeList.at(i-1).i;
                gj = gj + 1;
                nodeList.at(i).j = gj;
            } else {
                gi = nodeList.at(i).i;
                nodeList.at(i).i = 0;
                gj = 0;
            } 
        }
    } */
    
    

    
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
