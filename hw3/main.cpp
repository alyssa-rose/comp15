/*
* main.cpp
* driver for MetroSim (no pun intended)
* Alyssa Rose
* Comp15 HW3
* 18-Feb-2019
*/

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include "MetroSim.h"
using namespace std;

int main(int argc, char* argv[]){
	MetroSim metro;
	int input = argc;
	char* one = argv[1];
	char* two = argv[2];
	if ((input < 3) or (input > 4)){
		cerr << "Usage: MetroSim stationsFile passFile [commands]" << endl;
		return 0;
	}
	else {
		ifstream infile1;
		infile1.open(one);
		metro.read_stat(infile1);
		infile1.close();
		
		if (argv[3] == NULL){
			metro.command(two);
		}

		if (argv[3] != NULL){
			char* three = argv[3];
			metro.commandFile(two, three);
		}

		cout << "Thanks for playing MetroSim. Have a nice day!" << endl;
	}
	return 0;
}
