#include "Edge.h"
#include "Node.h"
#include "Score.h"
#include <vector>
#include <iostream>

using namespace std;

/** 
 * \param a is a Node
 * \param b is a Node
 * \return TRUE if a and b have the same indices
 */

bool is_equal(Node& a, Node& b){
    if (a.i == b.i && a.j == b.j) {
        return true;
    } else {
        return false;
    }
}

/**
 * This is a recursiv function that find a path for given nodes and edges. 
 * \param path is the path found so far
 * \param edgesVector is a vector with all edges
 */

void find_path(vector<Node>& path, vector<Edge>& edgesVector){
    for (unsigned int i = 0; i < edgesVector.size(); i++) {
        if (is_equal(path.back(), edgesVector[i].first)) { 
            path.push_back(edgesVector[i].second);
            find_path(path, edgesVector);         
            break;
        }      
    }
}

/** 
 * \param nodeList is the vector with all nodes
 * \param edgesVector is a vector with all edges
 * \return a score of all possible paths between the nodes
 */

unsigned int calculate_score(vector<Node>& nodeList, vector<Edge>& edgesVector){

    vector<bool> visited(nodeList.size(), false);
    unsigned int score = 0;

    for (unsigned int i = 0; i < nodeList.size(); i++) {
        if (visited[i] == false) {       
            vector<Node> path;
            path.push_back(nodeList[i]);
            find_path(path, edgesVector);
/*          
            // print all paths
            for (unsigned int p = 0; p < path.size(); p++) {
                cout << "(" << path[p].i << ", " << path[p].j << ") ";
            }
            cout << endl;
*/
            // update visited
            for (unsigned int j = 0; j < path.size(); j++) {
                for (unsigned int k = 0; k < nodeList.size(); k++) {
                    if (is_equal(path[j], nodeList[k])){
                        visited[k] = true;
                        break;
                    }
                }
            }

            // calculate score
            for (unsigned int s = 1; s < path.size(); s++) {
                score += s;
            }
        }        
    }

    return score;        
}
