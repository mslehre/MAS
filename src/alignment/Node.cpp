#include "Node.h"

using namespace std;

Node::Node(){}

Node::Node(unsigned int i, unsigned int j, unsigned int index, string kmer) {
    this->i = i;
    this->j = j;
    this->index = index;
    this->kmer = kmer;
}


