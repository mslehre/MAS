#include "State.h"

using namespace std;

state::state(vector <array<int,3>> e){
        for(int i=0;i<e.size();i++){
            this->selectedSubset.push_back(false);
            this->selectable.push_back(true);
        }
        this->edges=e;
}

state::state(){
        vector <bool> selectedSubset;
        vector <array<int,3>> edges;
        vector <bool> selectable;
}

state::~state(){}; 

void state::select(int i){
    if(this->selectable[i]==true){
        this->selectedSubset[i]=true;
        this->selectable[i]=false;
        this->updateSelectability();
    }
}

void state::updateSelectability(){
    for(int i=0;i<this->edges.size();i++){
        if(this->selectedSubset[i]==true)
            this->selectable[i]=false;
        else if(this->checkConsistency(i)!=true)
            this->selectable[i]=false;
    }
}

bool state::checkConsistency(int i){
    int left=i;
    int right=i;
    while(left!=-1 && edges[left].at(0)==edges[i].at(0)){ 
        if(this->selectedSubset[left]==true && ((edges[left].at(1)<edges[i].at(1) && edges[left].at(2)>edges[i].at(2)) || (edges[left].at(1)>edges[i].at(1) && edges[left].at(2)<edges[i].at(2)))){
            return false;
        }
        left--;
    }
    while(right<this->edges.size() && edges[right].at(0)==edges[i].at(0)){
        if(this->selectedSubset[right]==true && ((edges[right].at(1)<edges[i].at(1) && edges[right].at(2)>edges[i].at(2)) || (edges[right].at(1)>edges[i].at(1) && edges[right].at(2)<edges[i].at(2)))){
            return false;
        }
        right++;
    }
    return true;
}
                                                                                                                                                                
