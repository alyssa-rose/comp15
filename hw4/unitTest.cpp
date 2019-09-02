/*
* unitTest.cpp
* file for testing the BinarySearchTree class
* Alyssa Rose
* 22-Feb-2019
* Comp15 HW4
*/

#include <vector>
#include <limits>
#include <gtest/gtest.h>
#include "BinarySearchTree.h"

class BSTtests : public ::testing:Test {
protected:
	const std::vector<int> testdata;
	BSTtests()
		: testdata{258,  579,  814, -566, -686, -3,  -600,
                       382,  -562, -55, -768, 172,  252, 397,
                       -155, -898, 430, -520, 154,  255} {}

//testing the 
//testing the find min function(s)
TEST_F(BSTtests, find_min){
	BinarySearchTree bst;
	constexpr int errorVal = std::numeric_limits<int>::min();
	constexpr int testdataMin = -898;

	EXPECT_EQ(bst.find_min(), errorVal)
		<< "find_min on an empty tree should"
		   " return INT_MIN";

	bst.insert(0);
	EXPECT_EQ(bst.find_min(), 0);

	for (int num : testdata)
		bst.insert(num);

	EXPECT_EQ(bst.find_min(), testdataMin);
}



//testing the find man function(s)
TEST_F(BinarySearchTree, find_max){

	BinarySearchTree bst;
	constexpr int errorVal = std::numeric_limits<int>::max();
	constexpr int testdataMax = 814;
	
	EXPECT_EQ(bst.find_max(), errorVal)
		<< "find_max on an empty tree should"
		   " return INT_MAX";

	bst.insert(19);
	EXPECT_EQ(bst.find_max(), 19);
	
	for (int num : testdata) {
		bst.insert(num);
	}
	EXPECT_EQ(bst.find_max(), testdataMax);
}



testing remove function
TEST(BinarySearchTree, remove){
	BinarySearchTree bst;
	int values[]  = {4, 2, 11, 15, 9, 1, -6, 5, 3, 15, 2, 5, 13, 14};
	int numValues = sizeof(values) / sizeof(int);


	for (int i = 0; i < numValues; i++) {
		bst.insert(values[i]);
	}
	// leaf
	EXPECT_EQ((bst.remove(5)).node_count(), 10);
	// middle of the tree
	EXPECT_EQ((bst.remove(15)).node_count(), 9);
	// the root node
	EXPECT_EQ((bst.remove(4)).node_count(), 8);
	
}



//
TEST(BinarySearchTree, node_count){
	BinarySearchTree bst;
	int values[]  = {4, 2, 11, 15, 9, 1, -6, 5, 3, 15, 2, 5, 13, 14};
	int numValues = sizeof(values) / sizeof(int);


	for (int i = 0; i < numValues; i++) {
		bst.insert(values[i]);
	}

	EXPECT_EQ(bst.node_count(), 11);
}



//
TEST(BinarySearchTree, count_total){
	BinarySearchTree bst;
	int values[]  = {4, 2, 11, 15, 9, 1, -6, 5, 3, 15, 2, 5, 13, 14};
	int numValues = sizeof(values) / sizeof(int);


	for (int i = 0; i < numValues; i++) {
		bst.insert(values[i]);
	}

	EXPECT_EQ(bst.count_total(), 93);
}



//
TEST(BinarySearchTree, tree_height){
	BinarySearchTree bst;
	int values[]  = {4, 2, 11, 15, 9, 1, -6, 5, 3, 15, 2, 5, 13, 14};
	int numValues = sizeof(values) / sizeof(int);


	for (int i = 0; i < numValues; i++) {
		bst.insert(values[i]);
	}

	EXPECT_EQ(bst.tree_height(), 4);
}


//
TEST(BinarySearchTree, contains){
	BinarySearchTree bst;
	int values[]  = {4, 2, 11, 15, 9, 1, -6, 5, 3, 15, 2, 5, 13, 14};
	int numValues = sizeof(values) / sizeof(int);


	for (int i = 0; i < numValues; i++) {
		bst.insert(values[i]);
	}

	// middle of tree
	EXPECT_TRUE(bst.contains(9));
	// root
	EXPECT_TRUE(bst.contains(4));
	// leaf
	EXPECT_TRUE(bst.contains(14));
	// checking if it will return false;
	EXPECT_FALSE(bst.contains(99));
}