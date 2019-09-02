/*
* Filename: SixDegrees.h
* Header file for SixDegrees class
* Comp15 HW5
* Alyssa Rose
* 30-March-2019
*/

#include <iostream>
#include <string>
#include "Actor.h"
#include "Graph.h"

using namespace std;

#ifndef SIXDEGREES_H_
#define SIXDEGREES_H_

class SixDegrees{
public:
	SixDegrees();
	~SixDegrees();
	void run(istream &in, ostream &out);
	void BFS(Actor a, Actor b, ostream &out);
private:
	Graph<Actor> g;
	
	// populates the graph
	void populate_graph();

};
#endif