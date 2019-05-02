#include "State.h"

using namespace std;

state::state(vector <Edge> e){
        for(int i=0;i<e.size();i++){
            this->selectedSubset.push_back(false);
            this->selectable.push_back(true);
        }
        this->edges=e;
}

state::state(){
        vector <bool> selectedSubset;
        vector <Edge> edges;
        vector <bool> selectable;
}

state::~state(){}; 

void state::select(int i){
    if(this->selectable[i]==true){
        this->selectedSubset[i]=true;
        this->selectable[i]=false;
        this->updateSelectability(i);
    }
}

void state::updateSelectability(int i){
    int left=i;
    int right=i;
    while(left!=-1 && edges[left].first.i==edges[i].first.i){ 
        if((edges[left].first.j<edges[i].first.j && edges[left].second.j>edges[i].second.j) 
            || (edges[left].first.j>edges[i].first.j && edges[left].second.j<edges[i].second.j)){
            this->selectable[left]=false;
        }
        left--;
    }
    while(right<this->edges.size() && edges[right].first.i==edges[i].first.i){
        if((edges[right].first.j<edges[i].first.j && edges[right].second.j>edges[i].second.j)
            || (edges[right].first.j>edges[i].first.j && edges[right].second.j<edges[i].second.j)){
            this->selectable[right]=false;
        }
        right++;
    }
}                                                                                                                                                   
