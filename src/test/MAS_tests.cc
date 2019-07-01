#include <gtest/gtest.h>
#include "../alignment/State.h"
#include "../alignment/Edge.h"
#include "../alignment/Node.h"
#include "../alignment/Graph.h"

namespace MAS_test {
    TEST(MAS_tests, test_test) {
        EXPECT_EQ(0,0);
    }
// Timon: score_test
    TEST(alignment_tests, score_test) {
        Node n1(0,0,"AA");
        Node n2(0,1,"TT");
        Node n3(0,2,"GG");
        Node n4(0,3,"CC");
        Node n5(0,4,"AG");
        Node n6(0,5,"AG");
        Node n7(1,0,"AA");
        Node n8(1,1,"TT");
        Node n9(1,2,"AT");
        Node n10(1,3,"CC");
        Node n11(2,0,"GG");
        Node n12(2,1,"AA");
        Node n13(2,2,"AT");
        Node n14(2,3,"CC");
        Node n15(2,4,"CG");
        Node n16(3,0,"GC");
        Node n17(3,1,"TA");
        Node n18(3,2,"AA");
        Node n19(3,3,"AT");
        Node n20(3,4,"CC");
        Node n21(3,5,"GC");
        // Path 1    
        Edge e1;
        e1.first = &n1;
        e1.second = &n7;
        Edge e2;
        e2.first = &n7;
        e2.second = &n12;
        Edge e3;
        e3.first = &n12;
        e3.second = &n18;
        // Path 2
        Edge e4;
        e4.first = &n2;
        e4.second = &n8;
        // Path 3
        Edge e5;
        e5.first = &n9;
        e5.second = &n13;
        Edge e6;
        e6.first = &n13;
        e6.second = &n19;
        // Path 4
        Edge e7;
        e7.first = &n4;
        e7.second = &n10;
        Edge e8;
        e8.first = &n10;
        e8.second = &n14;
        Edge e9;
        e9.first = &n14;
        e9.second = &n20;

        vector<Edge> edgeList = {e1, e2, e3, e4, e5, e6, e7, e8, e9};
        state s(edgeList);

        for (unsigned int i = 0; i < edgeList.size(); i++) {
            s.select(i); // select all edges
        }  
        s.calculate_score(); // score = 16
        unsigned int score = s.score;
        EXPECT_EQ(score,16);
    }
//  SEBASTIAN and MORITZ: graph_test
    TEST(alignment_tests, graph_tests) {
        Graph g;
        // reading fasta file "sequences.fa" and selected length of k-mer = 2
        g.readFastaFiles("sequences.fa",2);
        // get edges
        vector<Edge> edges = g.getEdges();
        Edge edge1 = edges.at(0);
        Edge edge2 = edges.at(8);
        Edge edge3 = edges.at(10);
        Edge edge4 = edges.at(14);   
        Edge edge5 = edges.at(16);

        vector<std::pair<int,int>> edgesIndices = {
            std::make_pair(edge1.second->i,1),
            std::make_pair(edge1.second->j,4),
            std::make_pair(edge2.second->i,1),
            std::make_pair(edge2.second->j,9),
            std::make_pair(edge3.second->i,2),
            std::make_pair(edge3.second->j,1),
            std::make_pair(edge4.second->i,2),
            std::make_pair(edge4.second->j,5),
            std::make_pair(edge5.second->i,2),
            std::make_pair(edge5.second->j,4)
        };

        for (auto &a : edgesIndices ) {
            EXPECT_EQ(a.first,a.second);                
        }
    }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
