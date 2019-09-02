/*
* StringProcessing.cpp
* Alyssa Rose
* Comp15 Proj2
* 07-April-2019
*/

#include <string>
#include <iostream>

using namespace std;
string condense(string s);
bool isCondense(char c);

int main(){

	string str;
	while (getline(cin, str)){
		cout << "Original: " << str << endl;
		cout << "Condensed: "<< condense(str) << endl;
	}

	return 0;
}

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

bool isCondense(char c){
	if ((c >= 48 and c <= 57) or
		(c >= 65 and c <= 90) or
		(c >= 97 and c <= 122))
		return true;
	return false;
}


