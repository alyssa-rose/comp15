/*
* Index.h
* header file for the index class
* Comp15 Proj2
* Alyssa Rose
* 10-April-2019
*/

#ifndef INDEX_H
#define INDEX_H

#include "FSTree.h"
#include "DirNode.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <functional>
#include <sstream>

using namespace std;

const double LOAD_FACTOR = 0.75;

class Index {
public:
	// paramterized constructor
	Index(string directory);
	// destructor 
	~Index();
	// calls the process file functions
	// and insert word to initialize the table
	void makeTable();
	// queries on the word and gets the lines
	// where the word appears
	void query(string diesesWort, ofstream &out);
	// queries on case insensitive
	void queryLower(string diesesWort, ofstream& out);
	// helper function to convert the word to 
	// lower case
	string lowerCase(string query);

	void test_processFile(string fullPath);
	FSTree test_fs;	

private:
	/**********************************************************/
	// vectors to store the full lines and the paths
	vector<string> paths;
	vector<string> fileLines;
	/*********************************************************/
	// opens the file and gets the lines of the files
	// and the words in each of the lines
	void processFile(string fullPath);
	// expands the hashtable by (int) 1.7
	void expand();
	// removes the following and leading 
	// non alpha numeric characters from 
	// a string
	string condense(string s);
	// returns true if alpha numeric character 
	// and false otherwise
	bool isCondense(char c);
	// inserts the word into the hashtable; stores the
	// word (upper and lowercase), the line number,
	// the index of the full line and the index of
	// the path
	bool insertWord(string word, int line, int thisLine, 
		int pathIndex);
	// function to recurse through the directory node
	void recurseDirectory(DirNode *node, int level, string outDir);

	// struct to hold the original and
	// lower case forms of a word,
	// its key (value after being hashed)
	// the pathkey, lineNum and the fullLine
	struct hashNode {
		string word;
		string lower;
		int key;
		int pathKey;
		int lineNum;
		int fullLine;
	};
	// tracks the current file
	int fileTrack;
	// pointer to dynamic array that 
	// contains vectors of hashnodes
	vector<hashNode>* HashTable;
	// contains the number of elements
	// in the hashtable
	int numElems;
	// number of "bins" of 
	// the hashtable
	int currSize;
	
	// hash funtion from the standard
	// library
	hash<string> hasher;

	// root of directory tree
	FSTree fs;	
};

#endif