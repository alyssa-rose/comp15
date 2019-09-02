/*
* Alyssa Rose
* Comp 15 Proj 1
* 1 - Mar - 2019
*/

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include "Grep.h"

using namespace std;

int main(int argc, char* argv[]){
	Grep grep;
	(void) argc;
	char* in = argv[1];
	char* out = argv[2];

	ifstream infile;
	infile.open(in);

	ofstream outfile;
	outfile.open(out);

	if ((!infile.is_open()) or (!outfile.is_open())){
		cerr << "ERROR: File cannot be opened " << endl;
		return 0;
	}
	grep.readFile(infile, outfile);

	return 0;
}