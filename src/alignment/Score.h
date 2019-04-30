#ifndef score_H_ 
#define score_H_

#include "Edge.h"
#include "Node.h"
#include <vector>

void find_path(std::vector<Node>& path, std::vector<Edge>& edgesVector); ///< recursive function that find a path
unsigned int calculate_score(std::vector<Node>& nodeList, std::vector<Edge>& edgesVector); ///< calculate the score of a given set of edges and nodes
bool is_equal(Node& a, Node& b); ///< compare the indices of two Nodes 

#endif //score_H_ 
