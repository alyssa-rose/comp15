/*
 * Pirate.cpp
 * Alyssa Rose
 * 26-Jan-2019
 * COMP15
 * Spring 2019
 *
 * Implarrrrrrmentation of a Pirate
 */


#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include "Pirate.h"
using namespace std;

int Pirate::pirate_count = 0;

// Default Constructor
Pirate::Pirate(){
    pirateId = -1;
    name = "Cap'n Hook";
}

// Parameterized Constructor
// Input: Pirate's name
Pirate::Pirate(string n){
    assignPirateId();
    name = n;
}

// Input: nothing
// Returns: nothing
// Does: prints pirate ids and names, space separated
void Pirate::print(ostream& os) const{
    os << pirateId << " "
       << name;
}

// Input: ifstream istream source by reference, random range
// Returns: nothing
// Does: Based on file and range, selects random name to be
//       pirate's name
void Pirate::generatePirateName(ifstream &infile, int range){
    string pname;
    int rando = rand() % range;
    int count = 0;

    infile.clear();
    infile.seekg(0, ios::beg);    
    while (getline(infile, pname)){
        if (count == rando){
            name = pname;
            break;
        }
        count++;
    }
}

void Pirate::generateNextPirate(ifstream &infile){ 
    string pname;
    getline(infile, pname);
    name = pname;
    pirateId = pirate_count;
}

void Pirate::assignPirateId(){
    pirateId = pirate_count++;
}

bool operator == (const Pirate &p1, const Pirate &p2){
    return (p1.pirateId == p2.pirateId);
}

