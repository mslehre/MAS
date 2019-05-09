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

// get StringListSequence
vector<string>& Graph::getStringListSequence(){
    return stringListSequence;
}

// Method: get the length of node (kmer)
unsigned int Graph::getK(){
    return k;
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

// Method: calculate edges and nodes for one sequence
void Graph::calcAdjacentEdges(unsigned int index){//sequence
    vector<string>& stringList = getStringListSequence();

    // counter for nodes with matches
    bool matches = false;   
    // calculate adjacent edges from all nodes in one sequence
    // list of nodes for the sequence i
    for (unsigned int i = 0; i < nodeListAll.at(index).size(); i++) {
        // list of nodes for the sequence i+1
        // the last sequence has no next sequence
        if (index != stringList.size()-1) {
            for (unsigned int j = 0; j < nodeListAll.at(index + 1).size(); j++) {
                // compare strings of nodes
                if (nodeListAll.at(index).at(i).kmer == nodeListAll.at(index + 1).at(j).kmer) {
                    // store begin (Node) and end (Node) of an edge
                    Node firstNode  = nodeListAll.at(index).at(i);
                    Node secondNode = nodeListAll.at(index + 1).at(j);

                    // update adjacency list for this node
                    nodeListAll.at(index).at(i).adjNodes.push_back(secondNode); 
                    // pushes only nodes in nodeList with matches
                    matches = true;
                }        
            }
        }
        if (index != 0) {
            for (unsigned int j = 0; j < nodeListAll.at(index-1).size(); j++) {
                if (nodeListAll.at(index).at(i).kmer == nodeListAll.at(index - 1).at(j).kmer)
                    matches = true;
            }
        }
        if (matches)
            nodeList.push_back(nodeListAll.at(index).at(i));
        matches = false;
    }
    // rewrite index
    unsigned int counter_i = 0;
    unsigned int counter_j = 0;
        for (unsigned int i = 0; i < nodeList.size(); i++) {
            if (nodeList.at(i).i > counter_i) {
                
                counter_i++; 
                counter_j = 0;
            }
            nodeList.at(i).i = counter_i;
            nodeList.at(i).j = counter_j;
            counter_j++;
        }
}

// Method: get number of nodes only with matches
vector<int>& Graph::getNumberOfKmers(){
    return numberOfKmers;
}

// Method: list of edges
void Graph::calcEdgeList() {

    // calculate nodeList only with matches
    for (unsigned int i = 0; i < nodeListAll.size(); i++) {      
        calcAdjacentEdges(i);
    }
    // temporary vector of edges for calculation
    vector<Edge> edgesVec; 
    // create list of edges
    for (auto &node1 : nodeList ) {
        for (auto &node2 : node1.adjNodes) {
            Edge edge;
            edge.first = node1;
            edge.second = node2;
            edgesVec.push_back(edge);
        }
    }  

    // store temporary nodeList
    vector<Node> tempNodeList;
    for(auto edge : edgesVec) {
        tempNodeList.push_back(edge.first);
        tempNodeList.push_back(edge.second);
        edge.first.adjNodes.clear();
        edge.second.adjNodes.clear();
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
    // if helpList empty then return
    if (helpList.empty())
        return;
    // temporary variables for: calculate number of K-mers
    unsigned int counter = 0;
    unsigned int value = helpList.at(0).i;
    // calculate number of K-mers
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
    // clear NodeListAll for the new nodeListALL
    nodeListAll.clear();

    // initialize vector for nodes only with matches
    for (unsigned int i = 0; i < numberOfKmers.size(); i++) {
        nodeListAll.push_back(emptyNodeVector);
    }

    // push vectors into nodeListAll
    counter = 0;
    vector<int> tempVec = numberOfKmers;
    tempVec.insert(tempVec.begin(), 0);
    
    for (unsigned int i = 1; i < tempVec.size(); i++ ) {
        int a = tempVec.at(i-1);
        int b = tempVec.at(i) + tempVec.at(i-1);

        for (int j = a; j < b; j++) {
            nodeListAll.at(counter).push_back(helpList.at(j));
        }
        tempVec.at(i) = b;
        counter = counter + 1;
    }
   
    // sort index j for row
    for (auto &vec : nodeListAll) {
    sort(vec.begin(), vec.end(),
			[](const Node& x, const Node& y) {
					return x.j < y.j;
			});
    }

    // rewrite index i and j in NodeListAll

    for (unsigned int i = 0; i < nodeListAll.size(); i++) {
        for (unsigned int j = 0; j < nodeListAll.at(i).size(); j++) {
            nodeListAll.at(i).at(j).i = i; 
            nodeListAll.at(i).at(j).j = j;
        }
    }
    // clear nodeList for new nodeList
    nodeList.clear();
    for (auto &n : nodeListAll) {
        for (auto &m : n) {
            m.adjNodes.clear();
        }
    }

    // calculate nodeList only with matches with new i and j
    for (unsigned int i = 0; i < nodeListAll.size(); i++) {      
        calcAdjacentEdges(i);
    }

    // create new list of edges  with the new i and j
    for (auto &node1 : nodeList ) {
        for (auto &node2 : node1.adjNodes) {
            Edge edge;
            edge.first = node1;
            edge.second = node2;
            edgesVector.push_back(edge);
        }
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
