/*
* Alyssa Rose
* Comp15 Proj 1
* 1 - Mar - 2019
*/


#include "Grep.h"
#include <iostream>
#include <string>
#include <cmath>
#include <vector>

const string INSERT = "i";
const string QUERY = "q";
const string PREFIX = "pq";
const string REMOVE = "r";
const string NODES = "n";
const string PRINT = "p";
const string DELETE = "d";
const string PASS = "f";

using namespace std;

// std constructor
Grep::Grep(){
	root = NULL;
	max_Len = 0;
	nodeNum = 0;
}


// std destructor
Grep::~Grep(){
	deleteTrie(root);
	root = NULL;
}

/* Function: readFile(ifstream &infile)
* Parameters: reference to file
* Returns: nothing
* Does: iterates through each line of the file
* 	to read in commands that then call all
	relevant helper functions
*/
void Grep::readFile(ifstream &infile, ofstream &outfile){
	out = &outfile;
	string comm = "zzzz"; 
	string second = "zzzzz";
	while (infile >> comm) {
		if (comm == INSERT){
			infile >> second;
			insert(root, second, second.length(), outfile, second);
		}
		if (comm == QUERY){
			infile >> second;
			query(second, outfile);
		}
		if (comm == PREFIX){
			infile >> second;
			prefix(second, outfile);
		}
		if (comm == REMOVE){
			infile >> second;
			remove(second, outfile);
		}
		if (comm == NODES)
			numNodes(outfile);
		if (comm == PRINT)
			print(outfile);
		if (comm == DELETE){
			deleteTrie(root);
			root = NULL;
			nodeNum = 0;
			numNodes(outfile);
		}
		if (comm == PASS){
			infile >> second;
			outfile.close();
			outfile.open(second.c_str());
			out = &outfile;
			outfile << "Output file has been changed to "
			<< second << endl;
		}
	}
}



/* Function: insert(trieNode* trie, string s, int len)
* Parameters: ptr to trieNode, seq to insert, length
* 	of the string
* Returns: nothing
* Does: inserts the seq into the tree using recursion
*/
void Grep::insert(trieNode* trie, string s, int len, 
	ofstream &outfile, string orig){
	 if (in_tree(orig)){
	 	outfile << orig << " was previously inserted" << endl;
	 	return;
	 }
	int indx;
	if (len > max_Len)
		max_Len = len;
	if (s == "\0"){
		trie -> end = true;
		outfile << orig << " inserted" << endl; return;
	}
	indx = get_Indx(s[0]);
	if (trie == NULL){
		nodeNum++;
		trie = getNode();
		if (root == NULL)
			root = trie;
	}
	if (!trie -> children[indx]){
		trie -> children[indx] = getNode();
		nodeNum++;
	}
	int new_len = len - 1;
	if (indx == 0){
		return insert(trie -> children[0], s.substr(1, len), new_len, 
			outfile, orig);
	}
	if (indx == 1){
		return insert(trie -> children[1], s.substr(1, len), new_len, 
			outfile, orig);
	}
	if (indx == 2){
		return insert(trie -> children[2], s.substr(1, len), new_len, 
			outfile, orig);
	}
	if (indx == 3){
		return insert(trie -> children[3], s.substr(1, len), new_len, 
			outfile, orig);
	}
}


/* Function: query(string s)
* Parameters: string representing the string
*	we want to compare to
* Returns: nothing
* Does: finds sequence that most closely
*	resembles the sequence s and calculates
*	how similar the sequences are
*/
void Grep::query(string s, ofstream &outfile){
	if (root == NULL){
		outfile << s << ": No match found" << endl;
		return;
	}
	int idx = get_Indx(s[0]);
	if (!root -> children[idx]){
		outfile << s << ": No match found" << endl;
		return;
	}
	if (in_tree(s)){
		outfile << "Match found: "<< s << " 100%" << endl;
		return;
	}

	query(s, root, outfile);
}


/* Function: query(string s)
* Parameters: string representing the string
*	we want to compare to
* Returns: nothing
* Does: finds sequence that most closely
*	resembles the sequence s and calculates
*	how similar the sequences are
*/
void Grep::query(string s, trieNode *node, ofstream &outfile){
	int i = 0;
	int k;
	string common = "";
	trieNode *trav = node;
	for(i = 0; i < (int)s.length(); i++){
		k = get_Indx(s[i]);
		if (trav -> children[k]){
			common += s[i];
			trav = trav -> children[k];
		}
		else
			break;
	}
	k = get_Indx(s[i-1]);
	string qqq = common + query_helper(trav, k).substr(1);
	outfile << "Match found: " << qqq << " " <<
	percentMatch(s, qqq) << "%" << endl;
}


/* Function: query_helper(string s, trieNode *node, outfile)
* Parameters: ptr to trieNode, string s, file to print to
* Returns: nothing
* Does: finds the string that most closely resembles
*	the string s
*/
string Grep::query_helper(trieNode *trav, int ind){
	if (trav -> end == true){
		char c = get_Char(ind);
		string ret(1, c);
		return ret;
	}
	string temp = "";
	string bestMatch = "";
	for (int i = 0; i < 4; i++){
		if (trav -> children[i]){
			temp = query_helper(trav -> children[i], i);
			bestMatch = getQuery(bestMatch, temp);
		}
	}
	string j(1, get_Char(ind));
	j += bestMatch; return j;
}
/* Function: prefix(string s)
* Parameters: string of prefix 
* Returns: nothing
* Does: calls private prefix func
*	starting at root node
*/
void Grep::prefix(string s, ofstream &outfile){
	if (root == NULL)
		return;
	prefix(s, root, outfile);
}


/* Function: prefix(string s, trieNode* node)
* Parameters: string representing the prefix,
*	node that traversal starts at
* Returns: nothing
* Does: calls helper function to find
*	all sequences in the tree that have the
*	specified prefix
*/
void Grep::prefix(string s, trieNode* node, ofstream &outfile){
	trieNode *traverse = node;
	if (root == NULL){
		outfile << s << ": No match found" << endl;
		return;
	}
	if (!(root -> children[get_Indx(s[0])])){
		outfile << s << ": No match found" << endl;
		return;
	}
	for (int i = 0; i < (int)s.length(); i++){
		int ind = get_Indx(s[i]);
		if (traverse -> children[ind])
			traverse = traverse -> children[ind];
		else {
			outfile << s << ": No match found" << endl;
			return;
		}
	}
	vector<char> pref(max_Len);
	prefix_helper(traverse, s, pref, 0, outfile);
}


/* Function: prefix_helper(trieNode* traverse, string s, 
*	vector<char> &pref, int lvl)
* Parameters: starting node, prefix string, a vector of char
*	and an integer
* Returns: nothing
* Does: copies code from print to print all sequences that
*	have the prefix specified by s. The tree is traversed starting
*	at the children nodes after traversing through the nodes
*	associated to s
*/
void Grep::prefix_helper(trieNode* traverse, string s, 
	vector<char> &pref, int lvl, ofstream &outfile){
	if (traverse -> end == true){
		outfile << s;
		for (int i = 0; i < lvl; i++){
			outfile << pref[i];	
		}
		outfile << '\n';	
	}

	for (int i = 0; i < 4; i++){
		if (traverse -> children[i]){
			pref[lvl] = get_Char(i);
			prefix_helper(traverse -> children[i], s, pref, 
				lvl + 1, outfile);
		}
	}

}


/* Function: remove(string seq)
* Parameters: string of sequence to
*	be removed
* Returns: true if removed, false otherwise
* Does: calls private remove functions to 
*	remove the sequence s
*/
bool Grep::remove(string seq, ofstream &outfile){
	if (root == NULL){
		return false;
	}
	remove(root, seq, 0, outfile);
	outfile << seq << " removed" << endl; return true;
}


/* Function: remove(trieNode *node, string s, int lvl)
* Parameters: ptr to a trienode, string s representing
*	thing to remove and current lvl
* Returns: bool representing whether or not the
*	seq was removed
* Does: removes the sequence s
*/
bool Grep::remove(trieNode *node, string s, int lvl, ofstream &outfile){
	if (!in_tree(s)){
		outfile << s << ": No match found" << endl;
		return false;
	}
	if (lvl == (int)s.length()){
		if (node -> end)
			node -> end = false;
		int check = 0;
		for (int i = 0; i < 4; i++){
			if (node -> children[i])
				check++;
		}
		if (check == 0){
			delete node;
			node = NULL;
			nodeNum--; return true;
		}
	}
	if (node -> end == false){
		int count = 0;
		for (int i = 0; i < 4; i++){
			if (node -> children[i])
				count++;
		}
		if (count == 0){
			delete node;
			node = NULL;
			nodeNum--; return true;
		}
	}
	int ind = get_Indx(s[lvl]);
	remove(node -> children[ind], s, lvl + 1, outfile);
	return true;
}


/* Function: print()
* Parameters: none
* Returns: nothing
* Does: calls the private print function
	to print out all sequences in the
	trie tree
*/
void Grep::print(ofstream &outfile){
	if (root == NULL){
		return;
	}
	vector<char> s(max_Len);
	print(root, s, 0, outfile);
}


/* Function: print(trieNode* trie, vector<char> &s, int lvl)
* Parameters: pointer to trieNode, a vector of char
	and an int representing the level (indx of char
	about to be inserted)
* Returns: nothing
* Does: prints out all sequences in the trie tree
*/
void Grep::print(trieNode* trie, vector<char> &s, int lvl, 
	ofstream &outfile){
	if (trie -> end == true){
		for (int i = 0; i < lvl; i++){
			outfile << s[i];	
		}
		outfile << '\n';	
	}

	for (int i = 0; i < 4; i++){
		if (trie -> children[i]){
			s[lvl] = get_Char(i);
			print(trie -> children[i], s, lvl + 1, outfile);
		}
	}
}


/* Function: deleteTrie(trieNode* node, outfile)
* Parameters: ptr to a trieNode
* Returns: nothing
* Does: deletes trieTree
*/
void Grep::deleteTrie(trieNode* node){
	if (root == NULL){
		nodeNum = 0;
		return;
	}
	if (node == NULL){
        return;
	}
    deleteTrie(node -> children[0]);
    deleteTrie(node -> children[1]);
    deleteTrie(node -> children[2]);
    deleteTrie(node -> children[3]);
    delete node;
}


/* Function: in_tree(string s)
* Parameters: string s (seq thats being
*	checked to see if in tree)
* Returns: bool
* Does: calls private function in_tree and 
*	checks base condition (root null)
*/
 bool Grep::in_tree(string s){
 	if (root == NULL)
 		return false;
 	return in_tree(s, root, s.length());
	
 }


/* Function: in_tree(string s, trieNode* node, int len)
* Parameters: string (seq checking for if in tree), ptr
*	to a trieNode, and the length of string
* Returns: bool
* Does: iterates through tree to check if string has
*	previously been inserted
*/
 bool Grep::in_tree(string s, trieNode* node, int len){
 	if (s == ""){
 		if (node == NULL)
 			return false;
 		if ((node -> end) == true)
 			return true;
 		return false;
 	}
 	if (node == NULL)
 	 	return false;
 	int new_len = len--;
 	int ind = get_Indx(s[0]);
 	if (ind == 20)
 		return false;
 	return in_tree(s.substr(1, len), node -> children[ind], 
 		new_len);
 }


/* Function: getNode()
* Parameters: none
* Returns: ptr to a trieNode
* Does: creates and initializes a new trieNode
*/
Grep::trieNode *Grep::getNode(){
	trieNode *new_node = new trieNode;
	new_node -> end = false;
	for (int i = 0; i < 4; i++){
		new_node -> children[i] = NULL;
	}
	return new_node;
}


/* Function: get_Indx(char c)
* Parameters: char representing DNA
* Returns: int
* Does: converts letter of the seq
*	to an index value either:
*	0, 1, 2, or 3
*/
int Grep::get_Indx(char c){
	if (c == 'A')
		return 0;
	if (c == 'C')
		return 1;
	if (c == 'G')
		return 2;
	if (c == 'T')
		return 3;
	return 20;
}


/* Function: get_Char(int i)
* Parameters: int representing index
* Returns: char
* Does: converts index number to
	the corresponding char; either
	A, C, G, or T
*/
char Grep::get_Char(int i){
	if (i == 0)
		return'A';
	if (i == 1)
		return 'C';
	if (i == 2)
		return 'G';
	if (i == 3)
		return 'T';
	return 'Z';
}


/* Function: numNodes()
* Parameters: none
* Returns: int representing num
* 	of nodes
* Does: returns private variable nodeNum
*/
void Grep::numNodes(ofstream &outfile){
	if (root == NULL)
		nodeNum =  0;
	outfile << "There are " << nodeNum << " nodes in the database" 
	<< endl;
	return;
}


/* 
* Function: percentMatch(string orig, string news)
* Parameters: 2 strings (to be compared)
* Returns: int representing % similarity
* Does: iterates through each string to find
*	the number of letters in common 
*/
int Grep::percentMatch(string orig, string news){
	double origLen = orig.length();
	double newsLen = news.length();
	if (orig[0] != news[0])
		return 0;
	if (origLen == newsLen){
		double count = 0;
		for (int i = 0; i < origLen; i++){
			if (orig[i] == news[i])
				count++;
		}
		return round((count/origLen) * 100);
	}

	if (origLen < newsLen){
		int count = 0;
		for (int i = 0; i < origLen; i++){
			if (orig[i] == news[i])
				count++;
		}
		return round((count/newsLen) * 100);
	}
	if (newsLen < origLen){
		int count = 0;
		for (int i = 0; i < newsLen; i++){
			if (news[i] == orig[i])
				count++;
		}
		return round((count/origLen) * 100);
	}
	return 1000;
}

/* 
* Function: getQuery(string one, string two)
* Parameters: string one, string two
* Returns: smallest string (if same, alphabetical)
* Does: gets query string
*/
string Grep::getQuery(string one, string two){
	int oneLen = (int)one.length();
	int twoLen = (int)two.length();
	string bad = "ZZZZZ";
	if (oneLen == 0)
		return two;
	if (twoLen == 0)
		return one;
	if (oneLen < twoLen)
		return one;
	if (twoLen < oneLen)
		return two;
	for (int i = 0; i < oneLen; i++){
		int k = get_Indx(one[i]);
		int j = get_Indx(two[i]);
		if (k < j)
			return one;
		if (j < k)
			return two;
	}
	return bad;
}
