/*
* Index.cpp
* implementation file for
* the index class
* Alyssa Rose
* Comp15 Proj2
* 10-April-2019
*/

#include "FSTree.h"
#include "DirNode.h"
#include "Index.h"

#include <sstream>
#include <iostream>
#include <functional>
#include <cmath>
#include <math.h>
#include <cstdlib>
#include <vector>
#include <sstream>

using namespace std;
const int ARRAY_SIZE = 50000;

// std constructor
Index::Index(string directory){
	numElems = 0;
	currSize = 	ARRAY_SIZE;
	HashTable = new vector<hashNode>[ARRAY_SIZE];

	fs = FSTree(directory);
	test_fs = FSTree(directory);
	fileTrack = 0;
}

// std destructor
Index::~Index(){
	delete [] HashTable;
	HashTable = NULL;
	fs.burnTree();
}


/*
* Function: processFile(ifstream &in)
* Parameters: reference to ifstream object
* Returns: nothing
* Does: process the files to put objects
* 		into the hashTable
*/
void Index::processFile(string fullPath){
	paths.push_back(fullPath);
	int pathIndex = ((int)paths.size()) - 1;
	ifstream in;
	in.open(fullPath);

	string get;
	string word;
	int line = 0;
	while (getline(in, get)){
		line++;
		fileLines.push_back(get);
		stringstream iss(get);
		while (iss >> word){
			insertWord(word, line, fileTrack, pathIndex);
		}
		fileTrack++;
	}
	in.close();
}
/*
* Function: expand()
* Parameters: none
* Returns: none
* Does: resizes the array and updates 
	currSize in the event the array
	is over the load factor
*/
void Index::expand(){
	int newSize = round(1.7 * currSize);
	vector<hashNode>* aux = HashTable;
	HashTable = new vector<hashNode>[newSize];
	hashNode k;
	for (int i = 0; i < currSize; i++){
		if (aux[i].size() != 0) {
			for (int j = 0; j < (int)aux[i].size(); j++){
				k.word = (aux[i].at(j)).word;
				k.key = (aux[i].at(j)).key;
				k.pathKey = (aux[i].at(j)).pathKey;
				k.lineNum = (aux[i].at(j)).lineNum;
				k.fullLine = (aux[i].at(j)).fullLine;
				HashTable[(k.key) % newSize].push_back(k);
			}
		}
	}
	delete [] aux;
	currSize = newSize;
}

/*
* Function: makeTable()
* Parameters: none
* Returns: none
* Does: uses the structure of FSTreeTraversal to process
*		the files of the root directory calling on process
*		file; main function of the index class
*/
void Index::makeTable(){
	DirNode *trav = fs.getRoot();
	recurseDirectory(trav, 0, "");
}

/*
* Function: insertWord()
* Parameters: string word, int line, string file
* Returns: bool
* Does: inserts the word into the hashTable and returns
*		true given that it was done sucessfully
*/
bool Index::insertWord(string newWord, int line, int thisLine, 
	int pathIndex){
	hashNode k;
	newWord = condense(newWord);
	k.lower = lowerCase(newWord);
	int hashed = hasher(k.lower);
	hashed = abs(hashed);
	k.word = newWord;
	k.key = hashed;
	k.lineNum = line;
	k.pathKey = pathIndex;
	k.fullLine = thisLine;

	if (numElems/currSize > LOAD_FACTOR){
		expand();
	}
	(HashTable[hashed % currSize]).push_back(k);
	return true;
}

/*
* Function: recurseDirectory
* Parameters: DirNode *node, int level, string outDir
* Returns: nothing
* Does: traverses through the directory and calls process
		file at each new file in order to build the hash table
*/
void Index::recurseDirectory(DirNode *node, int level, 
	string outDir){
	/*
	* Making sure the root has
	* subdirectories to traverse
	* through
	*/
	if (node -> hasSubDir()){
		int numSub = node -> numSubDirs();
		for (int i = 0; i < numSub; i++){
			if (level == 0)
				recurseDirectory(node -> getSubDir(i), level + 1, 
					outDir + node -> getName());
			else {
				recurseDirectory(node -> getSubDir(i), level + 1, 
					outDir + "/" + node -> getName());
			}		
		}
	}
	/*
	* Dealing with subdirectories
	* of the node
	*/
	string passPath = "";
	if (node -> hasFiles()){
		for (int i = 0; i < node -> numFiles(); i++){
			if (level == 0){
				passPath = node -> getName() + "/" + 
				node -> getFile(i);
				processFile(passPath);
			}
			else {
				passPath = outDir + "/" + node -> getName() + "/" + 
				node -> getFile(i);
				processFile(passPath);
			}
		}
	}
}


/*
* Function: printOut(string word)
* Parameters: the querying word
* Returns: nothing
* Does: prints out all locations of the queried word
*/
void Index::query(string diesesWort, ofstream& out){
	int indx = hasher(lowerCase(diesesWort));
	indx = abs(indx);
	int getIndex = indx % currSize;
	if (HashTable[getIndex].size() == 0){
		out << "query not found" << endl;
		return;
	}
	else {
		for (int i = 0; i < (int)HashTable[getIndex].size(); i++){
			if (((HashTable[getIndex]).at(i)).word == diesesWort){
				out << paths.at(((HashTable[getIndex]).at(i)).pathKey
					) << ":"
				<< ((HashTable[getIndex]).at(i)).lineNum << ": "
				<< fileLines.at(((HashTable[getIndex]).at(i)).
					fullLine) << endl;
			}
		}
	}

}


/*
* Function: queryLower(string diesesWort)
* Parameters: string to query on
* Returns: nothing
* Does: queries on a case insensitive basis
*/
void Index::queryLower(string diesesWort, ofstream& out){
	string queryOn = lowerCase(diesesWort);
	int indx = hasher(queryOn);
	indx = abs(indx);
	int getIndex = indx % currSize;
	if (HashTable[getIndex].size() == 0){
		out << "query not found" << endl;
		return;
	}
	else {
		for (int i = 0; i < (int)HashTable[getIndex].size(); i++){
			if (((HashTable[getIndex]).at(i)).lower == queryOn){
				out << 
				paths.at(((HashTable[getIndex]).at(i)).pathKey) 
				<< ":"
				<< ((HashTable[getIndex]).at(i)).lineNum << ": "
				<< fileLines.at(((HashTable[getIndex]).at(i)).
					fullLine) << endl;
			}
		}
	}

}

/*
* Function: lowerCase(string query)
* Parameters: string to convert to case
*		insensitive
* Returns: string
* Does: converts the query string to its
*		lower case form
*/
string Index::lowerCase(string query){
	string newQuery = "";
	for (int i = 0; i < (int)query.length(); i++){
		newQuery += tolower(query[i]);
	}
	return newQuery;
}

/*
* Function: string condense(string s)
* Parameters: string
* Returns: a string
* Does: removes the leading and trailing
*	non alpha numeric characters
*/
string Index::condense(string s){
	if (((int)s.length() == 1) and (!isCondense(s[0])))
		return "";
	if (!isCondense(s[0])){
		return condense(s.substr(1 , (int)s.length() - 1));
	}
	else {
		bool k = true;
		int index = 0;
		for (int i = 0; i < (int)s.length(); i++) {
			if (isCondense(s[i])){
				index = 0;
				k = true;
			}
			else {
				if (k){
					index = i;
					k = false;
				}
			}
		}
		if (index == 0)
			return s;
		else {
			return s.substr(0, index);
		}

	}
}

/*
* Function: isCondense(char c)
* Parameters: character
* returns: bool
* Does: true if the character is alpha
*	numeric and false otherwise
*/
bool Index::isCondense(char c){
	if ((c >= 48 and c <= 57) or
		(c >= 65 and c <= 90) or
		(c >= 97 and c <= 122))
		return true;
	return false;
}


/**************TESTING PURPOSES******************/
/*
* Function: test_processFile(ifstream &in)
* Parameters: reference to ifstream object
* Returns: nothing
* Does: process the files to put objects
* 		into the hashTable
*/
void Index::test_processFile(string fullPath){
	ifstream in;
	in.open(fullPath);
	paths.push_back(fullPath);
	int index = ((int)paths.size()) - 1;

	string get;
	string word;
	int line = 0, entireLine = 0;
	while (getline(in, get)){
		fileLines.push_back(get);
		entireLine = line + fileTrack;
		line++;
		fileTrack++;
		stringstream iss(get);
		while (iss >> word){
			insertWord(word, line, entireLine, index);
		}
	}
	in.close();
}