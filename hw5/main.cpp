/*
 * Filename: main.cpp
 * Contains: Driver for homework 5 
 * Part of: Homework 5 assignment "Graph Traversal" for Comp 15 Spring 2019
 *
 */

#include <iostream>
#include <fstream>
#include <cstdlib>
#include "SixDegrees.h"

using namespace std;

int main(int argc, char* argv[]) 
{
    SixDegrees sd;
    if (argc == 1)
    	sd.run(cin, cout);
    if (argc == 2){
    	ifstream infile;
    	infile.open(argv[1]);
    	sd.run(infile, cout);    
    	infile.close();
    }
 
    return 0;
}
