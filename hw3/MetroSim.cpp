/*
* MetroSim.cpp
* Implementation file for MetroSim
* Alyssa Rose
* Comp15 HW3
* 18-Feb-2019
*/

#include "MetroSim.h"
#include <iostream>
#include <fstream>
#include <vector>

MetroSim::MetroSim(){
	numPass = 1;
	currStat = 0;
	dir = 1;
}

MetroSim::~MetroSim(){

}


// Function: read_stat(ifstream& infile)
// Input: text file
// Return: nothing
// Does: reads stat file into structs
void MetroSim::read_stat(ifstream& infile){
	string statName = "";
	int count = 1;
	while (getline(infile, statName)) {
		Station s;
		s.name = statName;
		s.id = count;
		stat.push_back(s);
		count++;
	}
	currStat = 1;
}


// Function: print_map()
// Input: nothing
// Return: nothing
// Does: prints the structs of the stations
// and the passengers
void MetroSim::print_map(){
	print_train();
	for (int i = 0; i < (int)stat.size(); i++){
		if (currStat == i + 1)
			cout << "TRAIN: ";
		else {
			cout << "       ";
		}
		cout << "[" << i + 1 << "] " <<
		stat[i].name << " ";
		if ((int)((stat[i]).pass).size() == 0)
			cout << "{}" << endl;
		else {
			for (int j = 0; j < ((int)((stat[i]).pass)
				.size()); j++){
				if (j == 0)
					cout << "{";
				cout << "[" << ((stat[i]).pass[j]).id 
				<< ", " << ((stat[i]).pass[j]).arrive <<
				"->" << ((stat[i]).pass[j]).depart << "]";
				if (j == ((int)((stat[i]).pass).size()) - 1)
					cout << "}" << endl;
			}
		}
	}
}


// Function: command(string comm)
// Input: string containing the command
// Return: nothing
// Does: calls helper functions for all the 
// possible commands
void MetroSim::command(char* two){
	ofstream outfile;
	outfile.open(two);
	string pass;
	int k = 0;
	char c1 = 'c';
	print_map();

	while (k == 0){
		cout << "Command : ";
		cin >> c1;
		if (c1 == 'f'){
			getline(cin, pass);
			outfile.close();
			ofstream outfile;
			string passFile;
			passFile = pass.substr(2, pass.length());
			outfile.open(passFile.c_str());
			if (!outfile.is_open()){
				cerr << "Error: could not open file " 
				<< passFile << endl;
				return;
			}
		}
		else{
			if (c1 == 'p'){
				int c2, c3;
				cin >> c2;
				cin >> c3;
				Passenger p;
				p.id = numPass;
				p.arrive = c2;
				p.depart = c3;
				((stat[(p.arrive) - 1]).pass).push_back(p);
				numPass++;
			}
			if (c1 == 'm'){
				char c2;
				cin >> c2;
				if (c2 == 'm')
					move_train(outfile);
				if (c2 == 'f')
					k = 1;
			}
		}
		print_map();
	}
}
void MetroSim::commandFile(char* two, char* three){
	ofstream outfile;
	outfile.open(two);
	int k = 0;
	char c1 = 'c';
	string pass;
	ifstream commFile;
	commFile.open(three);
	string comm;
	print_map();
	while (k == 0){
		commFile >> c1;
		if (c1 == 'f'){
			getline(cin, pass);
			outfile.close();
			ofstream outfile;
			string passFile;
			passFile = pass.substr(2, pass.length());
			outfile.open(passFile.c_str());
			if (!outfile.is_open()){
				cerr << "Error: could not open file " << 
				passFile << endl;
				return;
			}
		}
		else {
			if (c1 == 'p'){
				int c2, c3;
				commFile >> c2;
				commFile >> c3;
				Passenger p;
				p.id = numPass;
				p.arrive = c2;
				p.depart = c3;
				((stat[(p.arrive) - 1]).pass).push_back(p);
				numPass++;
			}
			if (c1 == 'm'){
				char c2;
				commFile >> c2;
				if (c2 == 'm')
					move_train(outfile);
				if (c2 == 'f')
					k = 1;
			}
		}
		print_map();
	}	
}




// Function: move_train()
// Input: none
// Return: nothing
// Does: function to handle passenger info if the train moves
void MetroSim::move_train(ofstream& out){
	// checking if passengers need to be put into
	// the train vector
	int k = (int)((stat[currStat - 1].pass).size());
	if (k != 0) {
		cerr << k << endl;
		for (int i = 0; i < k; i++){
			Passenger m = stat[currStat - 1].pass[i];
			train.push_back(m);
		}
		for (int i = 0; i < k; i++)
			(stat[currStat - 1].pass).pop_back();
	}
	if (((currStat == 1) and dir == -1) or 
		(currStat%(int)stat.size()) == 0)
		dir *= -1;
	if (dir == 1)
		currStat++;
	if (dir == -1)
		currStat--;
	if ((int)train.size() != 0){
		for (int i = 0; i <(int)train.size() ; i++){ 
			Passenger p = train[i];
			if (p.depart == currStat){
				out << "Passenger " << p.id 
				<< " left train at station " 
				<< p.depart << '\n';
				train.erase(train.begin() + i);
			}
		}
	}
}

// Function: print_train()
// Input: none
// Return: none
// Does: helper function for print_map()
void MetroSim::print_train(){
	cout << "Passengers on the train: ";
	if ((int)train.size() == 0)
		cout << "{}" << endl;
	for (int i = 0; i < (int)train.size(); i++){
		if (i == 0)
			cout << "{";
		cout << "[" << (train[i]).id << ", " 
		<< (train[i]).arrive <<"->" << 
		(train[i]).depart << "]";
		if (i == ((int)train.size() - 1))
			cout << "}" << endl;
	}
}