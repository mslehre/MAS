#include "State.h"
#include "Edge.h"
#include "Node.h"
#include "Graph.h"
#include <iostream>

using namespace std;

// Test for the score calculation
// score = 16

int main(){
    
    Node n1(0,0,0,",");
    Node n2(0,1,1,",");
    Node n3(0,2,2,",");
    Node n4(0,3,3,",");
    Node n5(0,4,4,",");
    Node n6(0,5,5,",");
    Node n7(1,0,6,",");
    Node n8(1,1,7,",");
    Node n9(1,2,8,",");
    Node n10(1,3,9,",");
    Node n11(2,0,10,",");
    Node n12(2,1,11,",");
    Node n13(2,2,12,",");
    Node n14(2,3,13,",");
    Node n15(2,4,14,",");
    Node n16(3,0,15,",");
    Node n17(3,1,16,",");
    Node n18(3,2,17,",");
    Node n19(3,3,18,",");
    Node n20(3,4,19,",");
    Node n21(3,5,20,",");
    // Path 1    
    Edge e1;
    e1.first = n1;
    e1.second = n7;
    Edge e2;
    e2.first = n7;
    e2.second = n12;
    Edge e3;
    e3.first = n12;
    e3.second = n18;
    // Path 2
    Edge e4;
    e4.first = n2;
    e4.second = n8;
    // Path 3
    Edge e5;
    e5.first = n9;
    e5.second = n13;
    Edge e6;
    e6.first = n13;
    e6.second = n19;
    // Path 4
    Edge e7;
    e7.first = n4;
    e7.second = n10;
    Edge e8;
    e8.first = n10;
    e8.second = n14;
    Edge e9;
    e9.first = n14;
    e9.second = n20;

    vector<Edge> edgeList = {e1, e2, e3, e4, e5, e6, e7, e8, e9};

    vector<Node> nodeListe = {n1, n2, n3, n4, n5, n6, n7, n8, n9, n10, n11, 
                             n12, n13, n14, n15, n16, n17, n18, n19, n20, n21};
    
    Graph graph;

//    graph.edgesVector = edgeList;      //works only if edgesVector and nodeList are public in Graph.h  
//    graph.nodeList = nodeListe; 


// need a correct graph, dont work yet 
/*
    graph.readFastaFiles("score_test_fasta.fa", 2);
    state s(graph);
    for( unsigned int i = 0; i < graph.getEdgesVector().size(); i++) {
        s.select(i); //select all edges
    }  
    //s.calculate_score(graph); 
    unsigned int score = s.score;

    if (score == 16) {
        cout << "passed scoreTest successfully" << endl;
        return 0;
    } else {
        cout << "ScoreTest failed. Score is "<< score <<" not 16." << endl;
        return -1;
    }  
*/
return 0; // TODO if the graph works delete this return 

}
