#include "Node.h"

using namespace std;

Node::Node() {
    this->i = 0;
    this->j = 0;
    this->kmer = "";
}

Node::Node(unsigned int i, unsigned int j, string kmer) {
    this->i = i;
    this->j = j;
    this->kmer = kmer;
}

bool Node::operator ==(const Node& a){
     return a.i == this->i && a.j == this->j;     
}
