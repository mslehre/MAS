#include "State.h"
#include "Edge.h"
#include "Node.h"
#include "Graph.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

state::state(Graph& graph){
    this->edges = graph.getEdges();
    reset();

}

state::state(vector <Edge> e){
    vector<bool> tempSelectedSubset(e.size(), false);
    vector<bool> tempSelectable(e.size(), true);
    this->selectedSubset = tempSelectedSubset;
    this->selectable = tempSelectable;
    this->edges = e;
    this->score = 0;
}

state::state(){
    vector <bool> selectedSubset;
    vector <Edge> edges;
    vector <bool> selectable;
}

state::~state(){}; 

void state::select(int i){
    if (this->selectable[i] == true) {
        this->selectedSubset[i] = true;
        this->selectable[i] = false;
        this->updateSelectability(i);
        selectedEdgeIndex.push_back(i);
        sort(selectedEdgeIndex.begin(), selectedEdgeIndex.end()); 
    }
}

void state::reset(){
    selectedEdgeIndex.clear();
    vector<bool> tempSelectedSubset(edges.size(), false);
    vector<bool> tempSelectable(edges.size(), true);
    this->selectedSubset = tempSelectedSubset;
    this->selectable = tempSelectable;
    this->score = 0;
}

void state::updateSelectability(int i){
    int left = i;
    unsigned int right = i;
    while (left != -1 && edges[left].first->i == edges[i].first->i) { 
        if ((edges[left].first->j <= edges[i].first->j && edges[left].second->j >= edges[i].second->j) 
            || (edges[left].first->j >= edges[i].first->j && edges[left].second->j <= edges[i].second->j)) {
            this->selectable[left] = false;
        }
        left--;
    }
    while (right<this->edges.size() && edges[right].first->i == edges[i].first->i) {
        if ((edges[right].first->j <= edges[i].first->j && edges[right].second->j >= edges[i].second->j)
            || (edges[right].first->j >= edges[i].first->j && edges[right].second->j <= edges[i].second->j)) {
            this->selectable[right] = false;
        }
        right++;
    }
} 

// requires that e.first->i = f.first->i and e.second->i = f.second->i            
bool state::consistent(Edge& e, Edge& f){
    if (e.first->j == f.first->j && e.second->j == f.second->j) { 
        return true; // edges e and f are equal
    } else if ((e.first->j <= f.first->j && e.second->j >= f.second->j) ||
               (e.first->j >= f.first->j && e.second->j <= f.second->j)) {
        return false;          
    } else {
        return true;
    }
}

bool state::hasEdge() {
	for (unsigned int i = 0; i < selectable.size(); i++) {
		if (selectable[i] == true)
			return true;
	}
	return false;
}

// functions for scoring

bool state::is_equal(Node& a, Node& b){
    if (a.i == b.i && a.j == b.j) {
        return true;
    } else {
        return false;
    }
}

void state::calculate_score(){ 
    score = 0;
    vector<bool> visited(selectedEdgeIndex.size(), false);

    for (unsigned int i = 0; i < selectedEdgeIndex.size(); i++) {
        if (visited[i] == false) { 
            unsigned int path_length = 1;
            Edge current_edge = edges[selectedEdgeIndex[i]];
            visited[i] = true;
            for (unsigned int j = i; j < selectedEdgeIndex.size(); j++) {
                if (is_equal(*current_edge.second, *edges[selectedEdgeIndex[j]].first)) {
                    current_edge = edges[selectedEdgeIndex[j]];
                    path_length++;
                    visited[j] = true;
                }
            }
            score += (pow(path_length, 2) + path_length) / 2;                            
        }            
    }
}

vector<bool> state::calcSuccessorStates() {
    vector<bool> indexSet;
    for (unsigned int i = 0; i < edges.size(); i++) {
        if (!selectedSubset.at(i) && selectable.at(i)) {
            selectedSubset.at(i) = true;
            successorStates.push_back(selectedSubset);
            selectedSubset.at(i) = false;
            indexSet.push_back(true);
        }else {
            indexSet.push_back(false);
            
        }
    }
    return indexSet;
  
}
            
       
