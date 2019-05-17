#include "State.h"
#include "Graph.h"
#include "Node.h"
#include "Edge.h"
using namespace std;

int main(){
    //Following is just a Test
    Node n1(0,1,",");
    Node n2(1,3,",");
    Edge e1;
    e1.first = &n1;
    e1.second = &n2;
    Node n3(0,2,",");
    Node n4(1,1,",");
    Edge e2;
    e2.first = &n3;
    e2.second = &n4;
    Node n5(0,3,",");
    Node n6(1,3,",");
    Edge e3;
    e3.first = &n5;
    e3.second = &n6;
    Node n7(0,4,",");
    Node n8(1,2,",");
    Edge e4;
    e4.first = &n7;
    e4.second = &n8;
    Node n9(1,1,",");
    Node n10(2,1,",");
    Edge e5;
    e5.first = &n9;
    e5.second = &n10;
    Node n11(1,2,",");
    Node n12(2,4,",");
    Edge e6;
    e6.first = &n11;
    e6.second = &n12;
    Node n13(1,3,",");
    Node n14(2,2,",");
    Edge e7;
    e7.first = &n13;
    e7.second = &n14;
    Node n15(2,1,",");
    Node n16(3,2,",");
    Edge e8;
    e8.first = &n15;
    e8.second = &n16;
    Node n17(2,1,",");
    Node n18(3,4,",");
    Edge e9;
    e9.first = &n17;
    e9.second = &n18;
    Node n19(2,2,",");
    Node n20(3,5,",");
    Edge e10;
    e10.first = &n19;
    e10.second = &n20;
    Node n21(2,3,",");
    Node n22(3,1,",");
    Edge e11;
    e11.first = &n21;
    e11.second = &n22;
    Node n23(2,4,",");
    Node n24(3,3,",");
    Edge e12;
    e12.first = &n23;
    e12.second = &n24;
    Node n25(3,1,",");
    Node n26(4,2,",");
    Edge e13;
    e13.first = &n25;
    e13.second = &n26;
    Node n27(3,3,",");
    Node n28(4,2,",");
    Edge e14;
    e14.first = &n27;
    e14.second = &n28;
    
    vector<Edge> edgeList = {e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11 , e12, e13, e14};
    state s(edgeList);
    s.select(0);
    for (unsigned int i = 0; i < s.edges.size(); i++) {
        if (s.selectable[i] == true)		
            s.select(i);
    }
    for (unsigned int j = 0; j < s.selectable.size(); j++) {
        if (s.selectedSubset[j] == true) {
            cout<< "true" << endl;
        } else if (s.selectedSubset[j] == false) {
            cout<< "false" << endl;
        }
    }
    cout << endl;
        for (unsigned int j = 0; j < s.selectable.size(); j++) {
            if (s.selectable[j] == true) {
                cout<< "true" << endl;
            }
            else if (s.selectable[j] == false) {
                cout<< "false" << endl;
            }
    }
    return 0;
}
