/*
* FSTreeTraversal.cpp
* Comp15 Proj2
* Alyssa Rose
* 07-April-2019
*/

#include "FSTree.h"
#include "DirNode.h"
#include <iostream>
#include <string>

using namespace std;

void recurseDirectory(DirNode* node, int level, string outDir);


int main(int argc,  char* argv[]){
	if (argc == 1)
		cerr << "Error: input directory" << endl;
	else {
		string str(argv[1]);
		FSTree fs(str);

		DirNode *trav = fs.getRoot();
		recurseDirectory(trav, 0, "");
	}
	return 0;
}

void recurseDirectory(DirNode *node, int level, string outDir){
	/*
	* Making sure the root has
	* subdirectories to traverse
	* through
	*/
	//string outDir;
	if (node -> hasSubDir()){
		int numSub = node -> numSubDirs();
		for (int i = 0; i < numSub; i++){
			if (level == 0)
				recurseDirectory(node -> getSubDir(i), level + 1, outDir + node -> getName());
			else {
				recurseDirectory(node -> getSubDir(i), level + 1, outDir + "/" + node -> getName());
			}
		}
	}
	/*s
	* Dealing with subdirectories
	* of the node
	*/
	if (node -> hasFiles()){
		for (int i = 0; i < node -> numFiles(); i++){
			if (level == 0)
				cout << node -> getName() << "/" << node -> getFile(i) << endl;
			else {
				cout <<  outDir << "/" << node -> getName() << "/" << node -> getFile(i) << endl;
			}
		}
	}
}