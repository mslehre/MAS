#pragma once
#include "Node.h"
#include<string>
#include<utility>

using std::string;

class Edge {
    public:
        Edge();

        std::pair<Node*, Node*> edge;
};
