#include "State.h"
#include "Edge.h"
#include "Node.h"
#include "Graph.h"
#include <vector>
#include <iostream>

using namespace std;

state::state(Graph& graph){
    vector<bool> tempSelectedSubset(graph.getEdges().size(), false);
    vector<bool> tempSelectable(graph.getEdges().size(), true);
    this->selectedSubset = tempSelectedSubset;
    this->selectable = tempSelectable;
    this->edges = graph.getEdges();
    this->score = 0;
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
    if(this->selectable[i] == true){
        this->selectedSubset[i] = true;
        this->selectable[i] = false;
        this->updateSelectability(i);
    }
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

// functions for scoring

bool state::is_equal(Node& a, Node *b){
    if (a.i == b->i && a.j == b->j) {
        return true;
    } else {
        return false;
    }
}

void state::find_path(vector<unsigned int>& path, vector<Edge>& scoring_edges, Graph& graph){
    for (unsigned int i = 0; i < scoring_edges.size(); i++) {
        if (is_equal(graph.getNodes()[path.back()], scoring_edges[i].first)) { 
            for (unsigned int j = path.back() + 1; j < graph.getNodes().size(); j++) {
                if(is_equal(graph.getNodes()[j], scoring_edges[i].second)) {
                    path.push_back(j);
                    break;
                }                 
            }
            find_path(path, scoring_edges, graph);         
            break;
        }      
    }
}

void state::calculate_score(Graph& graph){ 
    score = 0;
    vector<Edge> scoring_edges; // all selected edges

    for (unsigned int i = 0; i < graph.getEdges().size(); i++) {
        if (selectedSubset[i])
            scoring_edges.push_back(graph.getEdges()[i]);
    }
    vector<bool> visited(graph.getNodes().size(), false);

    for (unsigned int i = 0; i < graph.getNodes().size(); i++) {
        if (visited[i] == false) {       
            vector<unsigned int> path;
            path.push_back(i); // push_back the startnode
            find_path(path, scoring_edges, graph);   
/*       
            // print path
            for (unsigned int p = 0; p < path.size(); p++) {
                cout << "(" << graph.getNodes()[path[p]].i << ", " << graph.getNodes()[path[p]].j << ") ";
            }
            cout << endl;
*/
            // update visited + calculate score
            for (unsigned int i = 0; i < path.size(); i++) {
                visited[path[i]] = true;
                score += i;
            }
        }        
    }
}

bool state::consistent(Edge& e, Edge& f){
    if ((e.first->j <= f.first->j && e.second->j >= f.second->j)
        || (e.first->j >= f.first->j && e.second->j <= f.second->j)) {
        return false;
    } else {
        return true;
    }
}
