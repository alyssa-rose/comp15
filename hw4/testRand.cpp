#include <iostream>
#include <gtest/gtest.h>

#include "BinarySearchTree.h"

using namespace std;

int main(){
	BinarySearchTree bst;
	int values[]  = {4, 2, 11, 15, 9};
	int numValues = sizeof(values) / sizeof(int);


	for (int i = 0; i < numValues; i++) {
		bst.insert(values[i]);
	}

	EXPECT_TRUE(bst.contains(9));
	// root
	EXPECT_TRUE(bst.contains(4));
	// leaf
	EXPECT_TRUE(bst.contains(14));
	// checking if it will return false;
	EXPECT_FALSE(bst.contains(99));
	return 0;
}