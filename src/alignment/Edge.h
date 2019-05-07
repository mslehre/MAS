#pragma once
#include "Node.h"
#include<string>
#include<utility>

using std::string;

class Edge {
    public:
        Edge();             ///< default constructor Edge
        Node* first;         ///< first node of the edge
        Node* second;        ///< second node of the edge
};
