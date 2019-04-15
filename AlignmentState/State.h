#ifndef STATE_H
#define STATE_H

#include <iostream>
#include <vector>
#include <array>

class state{
	public:
	state(std::vector <std::array<int,3>> e);//array wobei 1. Eintrag der index der i. sequence ist, 2. Eintrag index des k-mer in i. sequenz, 3. Eintrag index des k-mer in i+1. sequenz
	state();
	~state();
	std::vector <std::array<int,3>> edges; 
	std::vector <bool> consistentSubset; //shows whether edge is selected in current subset (true=selected)
	std::vector <bool> selectable; //shows whether edge is selectable in the current subset (true=selectable)
	void select(std::array<int,3> egde); //selects edge if selectable (does nothing otherwise)
	void possibleActions(); //updates state after selecting an edge
};
#endif
