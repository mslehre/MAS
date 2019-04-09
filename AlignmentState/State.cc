#include "State.h"

using namespace std;

state::state(vector <array<int,3>> e){
		for(int i=0;i<e.size();i++){
			this->consistentSubset.push_back(false);
			this->selectable.push_back(true);
		}
		this->edges=e;
}

state::state(){
		vector <bool> consistentSubset;
		vector <array<int,3>> edges;
		vector <bool> selectable;
}

state::~state(){}; 

void state::select(array<int,3> edge){
		for(int i=0;i<this->edges.size();i++){
			if(this->edges[i]==edge && selectable[i]==true){
				this->consistentSubset[i]=true;
				this->selectable[i]=false;
				this->possibleActions();
				break;
			}
		}
}

void state::possibleActions(){
	int l,r;
	for(int i=0;i<this->edges.size();i++){
		if(this->consistentSubset[i]==true){ //if selected -> not selectable
			this->selectable[i]=false;
		}
		else {
			l=i;
			r=i;
			while(l!=-1 && edges[l].at(0)==edges[i].at(0)){ //checks edges on the same sequence that could cross edges[i] from the left
				if(this->consistentSubset[l]==true && ((edges[l].at(1)<edges[i].at(1) && edges[l].at(2)>edges[i].at(2)) || (edges[l].at(1)>edges[i].at(1) && edges[l].at(2)<edges[i].at(2)))){
					this->selectable[i]=false;
				}
			l--;
			}
			while(r<this->edges.size() && edges[r].at(0)==edges[i].at(0)){ //checks edges on the same sequence that could cross edges[i] from the right
				if(this->consistentSubset[r]==true && ((edges[r].at(1)<edges[i].at(1) && edges[r].at(2)>edges[i].at(2)) || (edges[r].at(1)>edges[i].at(1) && edges[r].at(2)<edges[i].at(2)))){
					this->selectable[i]=false;
				}
			r++;
			}
		}
	}
}
				
			
