/*
* Alyssa Rose
* Driver for project 2/Index class
* Comp15 Proj2
* 10-April-2019
*/

#include "Index.h"
#include <sstream>
#include <iostream>
#include <ctime>
#include <chrono>

using namespace std;

string condense(string s);
bool isCondense(char c);

int main(int argc, char* argv[]){
	if (argc != 3){
		cerr << "usage: ./gerp input_directory output_directory" 
		<< endl;
	}
	string directory = argv[1], output = argv[2];
	ofstream out;
	out.open(output, ofstream::out | ofstream::trunc);
	Index ix(directory);
	ix.makeTable();
	string query = "", word = "";
	bool contQuery = true;
	while (contQuery){
		cerr << "Query? ";
		cin >> query;
		if (query == "@q" or query == "@quit"){
			cerr << "Goodbye! Thank you and have a nice day." 
			<< endl;
			contQuery = false;
		}
		else if ((query == "@i") or (query == "@insensitive")){
			getline(cin, query);
			stringstream ss(query);

			while (ss >> word){
				word = condense(word);
				ix.queryLower(word, out);
			}
		}
		else if (query == "@f"){
			cin >> word;		
			out.close();
			out.open(word, ofstream::out | ofstream::trunc);
			if (!out.is_open())
				cerr << "UNABLE TO OPEN FILE" << endl;
		}
		else {
			query = condense(query);
			ix.query(query, out);
			getline(cin, query);
			stringstream ss(query);
			while (ss >> word){
				query = condense(word);
				ix.query(word, out);
			}
		}
		cerr << "\n";
	}
	out.close();
}
/*
* Function: string condense(string s)
* Parameters: string 
* Returns: string 
* Does: removes leading and trailing non
*		alpha numeric characters
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

/*
* Function: isCondense(char c)
* Parameters: character
* Returns: a bool 
* Does: return true if the character is 
*		alphanumeric and false otherwise
*/
bool isCondense(char c){
	if ((c >= 48 and c <= 57) or
		(c >= 65 and c <= 90) or
		(c >= 97 and c <= 122))
		return true;
	return false;
}