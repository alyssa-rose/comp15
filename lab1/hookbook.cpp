/*
* Alyssa Rose
* 16-Jan-2019
* hookbook.cpp
* Comp 15 Lab 1
*/

#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include "Pirate.h"
#include "ArrayList.h"
using namespace std;

void get_pirate(ArrayList array);
int main()
{
	Pirate a("Alice");
	Pirate b("Barry");
	Pirate c("Chuck");
	Pirate d("Dave");
	Pirate e("Eugene");

	ArrayList array;

	array.insert_pirate(a);
	array.insert_pirate(b);
	array.insert_pirate(c);
	array.insert_pirate(d);
	array.insert_pirate(e);

	array.print();
	get_pirate(array);

}
void get_pirate(ArrayList array)
{
	ifstream infile;
	infile.open("pirate_names.txt");
	if(infile.fail())
		cerr << "File is defective" << endl;
	else {
		for (int i = 0; i < 200; i++) {
			if (i == 95){
				cerr << "Cannot add more than 100 pirates"<< endl;
				break;
			}
			Pirate k;
			k.generate_pirate_name(infile, 10);
			k.assign_pirate_id();
			k.print();
			array.insert_pirate(k);
		}
		array.print();
	}

}