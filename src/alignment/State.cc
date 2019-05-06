#include "State.h"
#include "Edge.h"
#include "Node.h"
#include "Graph.h"
#include <vector>

using namespace std;

state::state(Graph& graph){
    for (unsigned int i = 0; i < graph.getEdgesVector().size(); i++) {
        this->selectedSubset.push_back(false);
        this->selectable.push_back(true);
    }
    this->edges = graph.getEdgesVector();
    this->score = 0;
}

state::state(vector <Edge> e){
    for(int i=0;i<e.size();i++){
        this->selectedSubset.push_back(false);
        this->selectable.push_back(true);
    }
    this->edges=e;
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
    int right = i;
    while (left != -1 && edges[left].first.i == edges[i].first.i) { 
        if ((edges[left].first.j < edges[i].first.j && edges[left].second.j > edges[i].second.j) 
            || (edges[left].first.j > edges[i].first.j && edges[left].second.j < edges[i].second.j)) {
            this->selectable[left] = false;
        }
        left--;
    }
    while (right<this->edges.size() && edges[right].first.i == edges[i].first.i) {
        if((edges[right].first.j < edges[i].first.j && edges[right].second.j > edges[i].second.j)
            || (edges[right].first.j > edges[i].first.j && edges[right].second.j < edges[i].second.j)){
            this->selectable[right] = false;
        }
        right++;
    }
} 

// functions for scoring

void state::find_path(vector<unsigned int>& path, vector<Edge>& scoring_edges, Graph& graph){
    for (unsigned int i = 0; i < scoring_edges.size(); i++) {
        if (graph.getNodeList()[path.back()].index == scoring_edges[i].first.index) { 
            path.push_back(scoring_edges[i].second.index);
            find_path(path, scoring_edges, graph);         
            break;
        }      
    }
}

void state::calculate_score(Graph& graph){ 

    vector<Edge> scoring_edges; // all selected edges

    for (unsigned int i = 0; i < graph.getEdgesVector().size(); i++) {
        if (selectedSubset[i])
            scoring_edges.push_back(graph.getEdgesVector()[i]);
    }
    vector<bool> visited(graph.getNodeList().size(), false);

    for (unsigned int i = 0; i < graph.getNodeList().size(); i++) {
        if (visited[i] == false) {       
            vector<unsigned int> path;
            path.push_back(graph.getNodeList()[i].index); // push_back the startnode
            find_path(path, scoring_edges, graph);   
/*       
            // print path
            for (unsigned int p = 0; p < path.size(); p++) {
                cout << "(" << graph.getNodeList()[path[p]].i << ", " << graph.getNodeList()[path[p]].j << ") ";
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
