#include "Node.h"
#include<string>

using namespace std;

Node::Node(unsigned int i, unsigned int j, string kmer) {
    this->i = i;
    this->j = j;
    this->kmer = kmer;
        }
