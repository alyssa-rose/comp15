/* 
 * Station.cpp
 * Alyssa Rose
 * COMP15
 * Fall 2019
 *
 * Implementation of the Station class for homework 2
 */

#include "Station.h"

// Constructor
Station::Station(){
	name = "NoName";
    access = false;
}

// Parameterized Constructor
Station::Station(string input_name, bool input_access){
    name = input_name;
    access = input_access;
}

// Function: isEqual
// Input: Station onject
// Returns: boolean
// Does: determines if two stations are the
// 		 same and returns true if they are
bool Station::isEqual(Station s){
    if ((s.name == name) and (s.access == access))
    	return true;
    return false;
}

// Function: print
// Input: reference to ostream object
// Returns: nothing
// Does: prints the station name and accessibility
//       status with either A (available) or U
//       unavailable
void Station::print(ostream &outfile){
	char k;
	if (access == true)
		k = 'A';
	else
		k = 'U';
    outfile << name << " " << k;
}


