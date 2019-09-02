/*
* Alyssa Rose
* Comp 15 Proj 1
* 1 - Mar - 2019
*/

#include "Grep.h"
#include <fstream>
#include <iostream>

using namespace std;

void test_readFile();
void test_print_Trie();
void test_numNodes();
void test_Percent_Match();
void test_in_Tree();
void test_Prefix();
void test_Query(); 

int main(){
	test_readFile();
	test_print_Trie();
	test_Percent_Match();
	test_in_Tree();
	test_Prefix();
	test_numNodes();
	test_Query();

	return 0;
}

/*
* Purpose: tests the read file function
* insert function was commented out and
* cout was used to print "insert" in order
* to assure the func iterated through every
* line in the file and the lines of the file
* were printed out
*/
void test_readFile(){
	Grep gg;
	ifstream infile;
	infile.open("testQueryFile.txt");
	cerr << "opening file" << endl;

	ofstream outfile;
	outfile.open("out.txt");
	cerr << "reading file" << endl;
	gg.readFile(infile, outfile);
	cerr << "file done" << endl;
}

/*
* Purpose: tests the print function by printing to 
* standard out; uses readfile (and insert by extension).
* to assure errors only come from the print portion, the 
* readfile and insert were tested before this one
*/
void test_print_Trie(){
	Grep gg;
	ifstream infile;
	infile.open("testQueryFile.txt");
	ofstream outfile;
	outfile.open("out.txt");
	gg.readFile(infile, outfile);
	gg.print(outfile);
}

/*
* Purpose: checks if the percentMatch helper
* function works by comparing calculated values to 
* the expected values.
*/
void test_Percent_Match(){
	Grep gg;
	ifstream infile;
	infile.open("testQueryFile.txt");
	ofstream outfile;
	outfile.open("out.txt");
	gg.readFile(infile, outfile);

	// edge case: same words
	int k = gg.percentMatch("test", "test");
	if (k == 100)
		cerr << "Correct value: same string (100%)" << endl;

	// edge case: no letters in common
	int j = gg.percentMatch("paraguay", "arabic");
	if (j == 0)
		cerr << "Correct value: different (0%)" << endl;

	// case: some letters in common
	int i = gg.percentMatch("paraguay", "parachute");
	if (i == 44)
		cerr << "Correct values: some letters (44%)" << endl;

}

/*
* Purpose: tests in_tree function to determine if
* a sequence is already present in the tree
*/
void test_in_Tree(){
	Grep gg;
	ifstream infile;
	infile.open("testQueryFile.txt");
	ofstream outfile;
	outfile.open("out.txt");
	gg.readFile(infile, outfile);

	bool j = gg.in_tree("CACGA");
	if (j)
		cerr << "in_tree: in the tree" << endl;
	j = gg.in_tree("AGATA");
	if (j)
		cerr << "in_tree: in the tree" << endl;
	j = gg.in_tree("CAG");
	if (j)
		cerr << "in_tree: in the tree" << endl;

	bool k = gg.in_tree("KHDF");
	if (!k)
		cerr << "in_tree: not in tree" << endl;
}

/* Purpose: checks if the prefix function
* prints all the sequences in the tree that 
* have that prefix. The sequences with the
* prefix were printed to std out and checked
* manually for expected sequences
*/
void test_Prefix(){
	Grep gg;
	ifstream infile;
	infile.open("testQueryFile.txt");
	ofstream outfile;
	outfile.open("out.txt");
	gg.readFile(infile, outfile);

	// returns same, AA in tree
	gg.prefix("AA", outfile);
	// returns C
	gg.prefix("CACCC", outfile);
	// returns TAT
	gg.prefix("TATA", outfile);
}

/* Purpose: checks if the node count function
* is working. Was tested by modify the input
* text file and hand calculating the number
* of nodes based on the inserted elements
* of the file. 
*/
void test_numNodes(){
	Grep gg;
	ifstream infile;
	infile.open("testQueryFile.txt");
	ofstream outfile;
	outfile.open("out.txt");
	gg.readFile(infile, outfile);

	gg.numNodes(outfile);
}

/* Purpose: tests the query function */
void test_Query(){
	Grep gg;
	ifstream infile;
	infile.open("testQueryFile.txt");
	ofstream outfile;
	outfile.open("out.txt");
	gg.readFile(infile, outfile);

	// 20% match
	gg.query("AGATA", outfile);
	// 50% match
	gg.query("GGC", outfile);
	// 0% match
	gg.query("TTT", outfile);
	// 50% match
	gg.query("GAG", outfile);
}