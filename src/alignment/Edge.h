#pragma once
#include "Node.h"
#include<string>
#include<utility>

using std::string;

class Edge {
    public:
        Edge();
        Node* first;
        Node* second;
        //std::pair<Node*, Node*> edge;
};
