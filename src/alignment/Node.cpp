#include "Node.h"

using namespace std;

Node::Node() {
    this->i = 0;
    this->j = 0;
    this->kmer = "";
}

Node::Node(unsigned int i, unsigned int j, unsigned int index, string kmer) {
    this->i = i;
    this->j = j;
    this->index = index;
    this->kmer = kmer;
}


