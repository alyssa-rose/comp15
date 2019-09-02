/*
* gerp-unittest.cpp
* unit testing file for proj2
* Comp15 proj2
* Alyssa Rose
* 12-April-2019
*/

#include "Index.h"
#include "DirNode.h"
#include "FSTree.h"
#include <math.h>
#include <functional>
#include <cmath>
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;
/*****GERP FUNCTIONS*****/
string test_commandLineInput(string query, string words);
void test_commandDriver();
void test_toLower();
string condense(string s);
bool isCondense(char c);
string toLower(string orig);

/*****INDEX CLASS*****/
void test_recurseFiles();
void recurseDirectory(DirNode *node, int level, 
	string outDir);
void test_processFiles(string filename);
void test_insertWord();
string lowerCase(string query);
void test_expand();

int main(){
	/*****GERP FUNCTIONS*****/
	cerr << "***TESTING COMMAND LINE INPUT***" << endl;
	test_commandDriver();
	cerr << "***TESTING TOLOWER***" << endl;
	test_toLower();

	/*****INDEX*****/
	cerr << "***TESTING RECURSE FILE***" << endl;
	test_recurseFiles();
	cerr << "***TESTING PROCESSFILES***" << endl;
	test_processFiles("testFile.txt");
	cerr << "***TESTING INSERT WORD***" << endl;
	test_insertWord();
	cerr << "***TESTING EXPAND***" << endl;
	test_expand();
	return 0;
}
/***************************************************************/

/* tests the ability of the
* gerp class to take in input
* correctly from the command file
*/
string test_commandLineInput(string query, string words){
	bool contQuery = true;
	string thisWord = "";
	while (contQuery){
		if (query == "@q" or query == "@quit"){
			contQuery = false;
			return "PROGRAM TERMINATED";
		}
		else if (query == "@i" or query == "@insensitive"){
		  // handle case insensitive
			stringstream ss(words);
			while (ss >> thisWord) {
				cerr << "CASE INSENSITIVE SEARCH" << endl;
				cerr << "ORIGINAL QUERY: " << thisWord<< endl;
				cerr << "QUERYING ON: " << toLower(thisWord) 
				<< endl;
			}
			return "CASE INSENSITIVE";

		}
		else if (query == "@f"){	
			cerr << "CHANGE OUTFILE" << endl;
			return "CHANGE OUTFILE";
		}
		else {
			cerr << "ORIGINAL QUERY: " << query << endl;
			query = condense(query);
			cerr << "QUERY CONDENSED: QUERYING ON: " 
			<< query << endl;

			stringstream ss(words);
			while (ss >> thisWord){
				cerr << "ORIGINAL QUERY: " << thisWord << endl;
				query = condense(thisWord);
				cerr << "QUERY CONDENSED: QUERYING ON: " 
				<< thisWord << endl;
			}
			return "STANDARD QUERY";
		}
	}
	return "FALSE";
}

/*
* automatically test the command line
* tester function
*/
void test_commandDriver(){
	if (test_commandLineInput("@q", "duck") == "STANDARD QUERY"){
		cerr << "***SUCCESS: STANDARD QUERY RECOGNIZED***" 
		<< endl;
	}
	if (test_commandLineInput("@f", "") == "CHANGE OUTFILE"){
		cerr << "***SUCCESS: CHANGE FILE RECOGNIZED***" 
		<< endl;
	}
	if (test_commandLineInput("@i", "wE aRe tHe CHAMPIONS")
		== "CASE INSENSITIVE"){
		cerr << "***SUCCESS: CASE INSENSITIVE RECOGNIZED***" 
	<< endl;
	}
	if (test_commandLineInput("@q", "") == "PROGRAM TERMINATED")
		cerr << "***SUCESS: QUIT RECOGNIZED***" << endl;
}
/*
* tests the toLower function 
*/
void test_toLower(){
	string queryOrig, queryNew = "";
	queryOrig = "WOR&D";
	for (int k = 0; k < (int)queryOrig.length(); k++)
		queryNew += tolower(queryOrig[k]);
	cerr << "ORIGINAL QUERY: " << queryOrig << endl;
	cerr << "CASE INSENSITIVE: " << queryNew << endl;
	cerr << "EXPECTED: wor&d" << endl;
	cerr << "\n";

	string queryOrig2, queryNew2 = "";
	queryOrig2 = "H@Shhhher";
	for (int k = 0; k < (int)queryOrig2.length(); k++){
		queryNew2 += tolower(queryOrig2[k]);
	}
	cerr << "ORIGINAL QUERY: " << queryOrig2 << endl;
	cerr << "CASE INSENSITIVE: " << queryNew2 << endl;
	cerr << "EXPECTED: h@shhhher" << endl;
	cerr << "\n";

	string queryOrig3, queryNew3 = "";
	queryOrig3 = "gerpy";
	for (int k = 0; k < (int)queryOrig3.length(); k++)
		queryNew3 += tolower(queryOrig3[k]);
	cerr << "ORIGINAL QUERY: " << queryOrig3 << endl;
	cerr << "CASE INSENSITIVE: " << queryNew3 << endl;
	cerr << "EXPECTED: gerpy" << endl;
}
/*
* removes leading and trailing
* non alpha numeric characters
* from the string
*/
string condense(string s){
	if (!isCondense(s[0]))
		return condense(s.substr(1 , (int)s.length()));
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

string toLower(string orig){
	string newStr = "";
	for (int i = 0; i < (int)orig.length(); i++)
		newStr += tolower(orig[i]);
	return newStr;
}
/*
* helper function for condensing
* the desired query
*/
bool isCondense(char c){
	if ((c >= 48 and c <= 57) or
		(c >= 65 and c <= 90) or
		(c >= 97 and c <= 122))
		return true;
	return false;
}



/*************************************************************/

/*
* tests the ability of the index class
* to recurse through folders/subfolders and files
*/
void test_recurseFiles(){

	string str = "/comp/15/files/extras/test-dirs/tinyData";
	Index testIx(str);
	DirNode *trav = (testIx.test_fs).getRoot();
	recurseDirectory(trav, 0, "");

}

/*
* function written for FSTreeTraversal to
* traverse through the folders/subfolder/files 
* root node
*/
void recurseDirectory(DirNode *node, int level, string outDir){
	/*
	* Making sure the root has
	* subdirectories to traverse
	* through
	*/
	if (node -> hasSubDir()){
		int numSub = node -> numSubDirs();
		for (int i = 0; i < numSub; i++){
			if (level == 0){
				recurseDirectory(node -> getSubDir(i), 
					level + 1, outDir + node -> getName());
			}
			else {
				recurseDirectory(node -> getSubDir(i), 
					level + 1, outDir + "/" + node -> getName());
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
					cerr << "PASSPATH: " << passPath << endl;
				}
				else {
					passPath = outDir + "/" + node -> getName() 
					+ "/" + 
					node -> getFile(i);
					cerr << "PASSPATH: " << passPath << endl;
				}
			}
		}
	}
}

/*
* tests the ability of the Index class
* to read and process files
*/
void test_processFiles(string filename){
	hash<string> hashTest;
	ifstream in;
	cerr << "FILENAME: " << filename << endl;
	in.open(filename);
	if (!in.is_open())
		cerr << "FILE NOT OPENED" << endl;

	string get;
	string word;
	int line = 0;
	while (getline(in, get)){
		line++;
		stringstream iss(get);
		while (iss >> word){
			cerr << "LINE NUMBER: " << line << ": " 
			"WORD: " << word;
			cerr << " HASHED: " << hashTest(word) 
			<< endl;
		}
	}
	in.close();
}

/*
* tests the insert word function of the 
* index class
*/
void test_insertWord(){
	cerr << "TEST_INSERTWORD" << endl;
	hash<string> hasher;
	vector<string> tester[23];
	string lower = "";
	int index;
	string inputRay[7] = {"penguins", 
	"harpseals", 
	"polarbears", 
	"seagulls", 
	"walruses",
	"articfoxes",
	"narwhals"};
	for (int i = 0; i < 7; i++){                            
		lower = lowerCase(inputRay[i]);
		cerr << "INSERTING WORD: " << lower << endl;
		int hashed = hasher(lower);
		hashed = abs(hashed);
		cerr << "HASHED: " << hashed << endl;
		index = hashed % 23;
		cerr << "INDEX: " << index << endl;
		(tester[index]).push_back(lower);
	}
	cerr << "tester[16].at(0): " << "EXPECTED: narwhals " 
	<< "Actual: " << tester[16].at(0) << endl;
	cerr << "tester[12].size(): " << "EXPECTED: 0 "
	<< "Actual: " << tester[12].size() << endl;
	cerr << "tester[9].at(0): " << "EXPECTED: polarbears " 
	<< "Actual: " << tester[9].at(0) << endl;

}

/*
* helper function to convert the query request 
* to lower case
*/
string lowerCase(string query){
	string newQuery = "";
	for (int i = 0; i < (int)query.length(); i++){
		newQuery += tolower(query[i]);
	}
	return newQuery;
}

/*
* tests the expand function
*/
void test_expand(){
	vector<string>* tester;
	vector<string>* aux;
	hash<string> hasher;

	tester = new vector<string>[23];
	string lower = "";
	int index;
	string inputRay[7] = {"penguins", 
	"harpseals", 
	"polarbears", 
	"seagulls", 
	"walruses",
	"articfoxes",
	"narwhals"};
	for (int i = 0; i < 7; i++){                            
		lower = lowerCase(inputRay[i]);
		int hashed = hasher(lower);
		hashed = abs(hashed);
		index = hashed % 23;
		(tester[index]).push_back(lower);
	}
	int newSize = (int)(1.7*23);
	cerr << "NEW SIZE: " << newSize << endl;
	aux = tester;
	tester = new vector<string>[newSize];

	for (int i = 0; i < 23; i++){
		if (aux[i].size() != 0){
			for (int j = 0; j < (int)aux[i].size(); j++){
				cerr << "WORD: " << aux[i].at(j) << endl;
				index = hasher(aux[i].at(j));
				index = abs(index);
				cerr << "HASHED: " << index << endl;
				cerr << "OLD INDEX: " << index % 23 
				<< " NEW INDEX: " << index%newSize << endl;
			}
		}
	}
	delete [] aux;
	delete [] tester;
}
