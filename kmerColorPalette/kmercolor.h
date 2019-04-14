
#ifndef kmercolor_H_ 
#define kmercolor_H_

#include <string>
#include "Graph.h"
#include <SFML/Graphics.hpp>
#include <vector>

sf::Color ColorBasedOnMapping(std::string kmer);
std::vector<std::vector<sf::Color>> ColorBasedOnGraph(Graph copiedGraph);

#endif //kmercolor_H_
