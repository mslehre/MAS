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
// Maurice: consistency_check
    TEST(alignment_tests, consistency_check) {
        vector <Edge> edgeList;
        Node n1(0,1,",");
        Node n2(1,3,",");
        Edge e1;
        e1.first=&n1;
        e1.second=&n2;
        Node n3(0,2,",");
        Node n4(1,1,",");
        Edge e2;
        e2.first=&n3;
        e2.second=&n4;
        Node n5(0,3,",");
        Node n6(1,3,",");
        Edge e3;
        e3.first=&n5;
        e3.second=&n6;
        Node n7(0,4,",");
        Node n8(1,2,",");
        Edge e4;
        e4.first=&n7;
        e4.second=&n8;
        Node n9(1,1,",");
        Node n10(2,1,",");
        Edge e5;
        e5.first=&n9;
        e5.second=&n10;
        Node n11(1,2,",");
        Node n12(2,4,",");
        Edge e6;
        e6.first=&n11;
        e6.second=&n12;
        Node n13(1,3,",");
        Node n14(2,2,",");
        Edge e7;
        e7.first=&n13;
        e7.second=&n14;
        Node n15(2,1,",");
        Node n16(3,2,",");
        Edge e8;
        e8.first=&n15;
        e8.second=&n16;
        Node n17(2,1,",");
        Node n18(3,4,",");
        Edge e9;
        e9.first=&n17;
        e9.second=&n18;
        Node n19(2,2,",");
        Node n20(3,5,",");
        Edge e10;
        e10.first=&n19;
        e10.second=&n20;
        Node n21(2,3,",");
        Node n22(3,1,",");
        Edge e11;
        e11.first=&n21;
        e11.second=&n22;
        Node n23(2,4,",");
        Node n24(3,3,",");
        Edge e12;
        e12.first=&n23;
        e12.second=&n24;
        Node n25(3,1,",");
        Node n26(4,2,",");
        Edge e13;
        e13.first=&n25;
        e13.second=&n26;
        Node n27(3,3,",");
        Node n28(4,2,",");
        Edge e14;
        e14.first=&n27;
        e14.second=&n28;
        edgeList.push_back(e1);
        edgeList.push_back(e2);
        edgeList.push_back(e3);
        edgeList.push_back(e4);
        edgeList.push_back(e5);
        edgeList.push_back(e6);
        edgeList.push_back(e7);
        edgeList.push_back(e8);
        edgeList.push_back(e9);
        edgeList.push_back(e10);
        edgeList.push_back(e11);
        edgeList.push_back(e12);
        edgeList.push_back(e13);
        edgeList.push_back(e14);

        // test of two crossings of single edge (indices apart)
        state doubleCrossInd(edgeList);
        doubleCrossInd.select(0);
        EXPECT_FALSE(doubleCrossInd.selectable[0]);
        EXPECT_FALSE(doubleCrossInd.selectable[1]);
        EXPECT_FALSE(doubleCrossInd.selectable[3]);
        EXPECT_TRUE(doubleCrossInd.selectedSubset[0]);
        // test for two crossings of a single edge
        state doubleCross(edgeList);
        doubleCross.select(9);
        EXPECT_FALSE(doubleCross.selectable[9]);
        EXPECT_FALSE(doubleCross.selectable[10]);
        EXPECT_FALSE(doubleCross.selectable[11]);
        EXPECT_TRUE(doubleCross.selectedSubset[9]);
        // test for two outgoing edges from a node (7 and 8)
        state outEdge(edgeList);
        outEdge.select(7);
        EXPECT_TRUE(outEdge.selectedSubset[7]);
        EXPECT_FALSE(outEdge.selectable[7]);
        EXPECT_FALSE(outEdge.selectable[8]);
        EXPECT_FALSE(outEdge.selectable[10]);
        // test for two incoming edges towards a node
        state inEdge(edgeList);
        inEdge.select(0);
        EXPECT_TRUE(inEdge.selectedSubset[0]);
        EXPECT_FALSE(inEdge.selectable[2]);
        // test if selectable is false after trying to select every edge
        state s(edgeList);
        for (unsigned int i = 0; i < s.edges.size(); i++) {
            if (s.selectable[i] == true)		
                s.select(i);
        }
        for (unsigned int i = 0; i < s.edges.size(); i++) {
            EXPECT_FALSE(s.selectable[i]);
        }
    }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
