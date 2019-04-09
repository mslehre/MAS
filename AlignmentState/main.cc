#include "State.h"
//Bastis graph includen
using namespace std;

int main(){
	array<int,3> e1={0,1,3}; //testMAS
	array<int,3> e2={0,2,1};
	array<int,3> e3={0,3,3};
	array<int,3> e4={0,4,2};
	array<int,3> e5={1,1,1};
	array<int,3> e6={1,2,4};
	array<int,3> e7={1,3,2};
	array<int,3> e8={2,1,2};
	array<int,3> e9={2,1,4};
	array<int,3> e10={2,2,5};
	array<int,3> e11={2,3,1};
	array<int,3> e12={2,4,3};
	array<int,3> e13={3,1,1};
	array<int,3> e14={3,3,2};
	vector <array<int,3>> edgeList;
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
	state s(edgeList);
	s.select(e1);
	for(int i=0;i<s.edges.size();i++){
		if(s.selectable[i]==true){		
			s.select(s.edges[i]);
		}
	}
	for(int j=0;j<s.selectable.size();j++){
		if(s.consistentSubset[j]==true){ cout<< "true" << endl;}
		else if(s.consistentSubset[j]==false){cout<< "false" << endl;}
	}
	cout << endl;
		for(int j=0;j<s.selectable.size();j++){
		if(s.selectable[j]==true){ cout<< "true" << endl;}
		else if(s.selectable[j]==false){cout<< "false" << endl;}
	}
	return 0;
}
