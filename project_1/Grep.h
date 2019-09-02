/*
* Alyssa Rose
* Comp15 Proj 1
* 1 - Mar - 2019
*/

#ifndef GREP_H_
#define GREP_H_

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

class Grep {
public:
	// std constructor
	Grep();
	// std destructor
	~Grep();
	
	// reads commands/seq from file
	void readFile(ifstream &infile, ofstream &outfile);
	// prints the tree
	void print(ofstream &outfile);
	// returns number of nodes
	void numNodes(ofstream &outfile);
	// calculates similarity between strings
	int percentMatch(string orig, string news);
	// public version of in_tree
	 bool in_tree(string s);
	// public version of prefix
	void prefix(string s, ofstream &outfile);
	// public remove
	bool remove(string seq, ofstream &outfile);
	// public query func
	void query(string s, ofstream &outfile);


private:
	struct trieNode {
		trieNode* children[4];
		bool end;
	};

	/*** required functions ***/

	//prints the tree
	void print(trieNode* root, vector<char> &s, int lvl, ofstream &outfile);
	// insert a new sequence into the trie tree
	void insert(trieNode* trie, string s, int len, ofstream &outfile,
		string orig);
    // deletes the entire tree
	void deleteTrie(trieNode* root);
	// finds all sequences with the specified
	// prefix
	void prefix(string s, trieNode* node, ofstream &outfile);
	// removes sequence from the tree
	bool remove(trieNode *root, string s, int lvl, ofstream &outfile);
	// find most similar sequence
	void query(string s, trieNode *node, ofstream &outfile);
	

	/*** helper functions ***/

	// converts char to int
	int get_Indx(char c);
	//converts int to char
	char get_Char(int i);
	// prints the sequences that have
	// the specified prefix
	void prefix_helper(trieNode* traverse, string s, vector<char> &pref, 
		int lvl, ofstream &outfile);
	// checks if seq already in tree
	bool in_tree(string s, trieNode* node, int len);
	// returns newly initialized trieNode
	trieNode *getNode();
	// gets closest string
	string query_helper(trieNode *trav, int ind);
	// gets the best match for the query function
	string getQuery(string one, string two);


	/*** variables ***/

	// root of the tree
	trieNode *root;
	// max length of sequences
	int max_Len;
	// keeps track of number nodes in tree
	int nodeNum;
	ofstream *out;
};

#endif