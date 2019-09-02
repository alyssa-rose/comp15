/*
* MetroSim.h
* header file for MetroSim
* Alyssa Rose
* Comp15 HW3
* 18-February-2019
*/

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

#ifndef _METROSIM_H_
#define _METROSIM_H_

struct Passenger
{
	int arrive;
	int depart;
	int id;
};

struct Station
{
	int id;
	string name;
	vector<Passenger> pass;
};

class MetroSim
{
public:
	MetroSim();

	// destructor not actually
	// used as vectors destroy themselves
	~MetroSim();
	
	// handles command if no command
	//file given
	void command(char* two);

	// handles command if command file 
	// given
	void commandFile(char* two, char* three);

	// reads in the station names
	void read_stat(ifstream& infile);
private:

	//vector of all the stations
	vector<Station> stat;
	// vector to keep track of the passengers
	// on the train
	vector<Passenger> train;

	// prints out the current map
	void print_map();

	//helper func for print_map()
	void print_train();

	// will deal with passFile
	void move_train(ofstream& out);

	// keeping track for pass id #
	int numPass;

	// determines current station train
	// is at
	int currStat;

	// keeps track of train direction
	int dir;

};

#endif