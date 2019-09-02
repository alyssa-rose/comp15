/*
* BinarySearchTree-unittest.cpp
* file for testing the BinarySearchTree class
* Alyssa Rose
* 22-Feb-2019
* Comp15 HW4
*/

#include <gtest/gtest.h>
#include "BinarySearchTree.h"


//testing the find min function(s)
TEST(BSTtests, find_min){
	BinarySearchTree bst;
	constexpr int errorVal = std::numeric_limits<int>::min();
	constexpr int testdataMin = -898;

	int values[]  = {258,  579,  814, -566, -686, -3,  -600,
                       382,  -562, -55, -768, 172,  252, 397,
                       -155, -898, 430, -520, 154,  255};
    int numValues = sizeof(values) / sizeof(int);

	EXPECT_EQ(bst.find_min(), errorVal)
		<< "find_min on an empty tree should"
		   " return INT_MIN";

	bst.insert(0);
	EXPECT_EQ(bst.find_min(), 0);

	for (int i = 0; i < numValues; i++) {
        bst.insert(values[i]);
    }

	EXPECT_EQ(bst.find_min(), testdataMin);
}



//testing the find man function(s)
TEST(BSTtests, find_max){

	BinarySearchTree bst;
	constexpr int errorVal = std::numeric_limits<int>::max();
	constexpr int testdataMax = 814;
	
	int values[]  = {258,  579,  814, -566, -686, -3,  -600,
                       382,  -562, -55, -768, 172,  252, 397,
                       -155, -898, 430, -520, 154,  255};
    int numValues = sizeof(values) / sizeof(int);

	EXPECT_EQ(bst.find_max(), errorVal)
		<< "find_max on an empty tree should"
		   " return INT_MAX\n";

	bst.insert(19);
	EXPECT_EQ(bst.find_max(), 19)
		<< "19 should be max as it is the"
			" only value\n";
	
	for (int i = 0; i < numValues; i++) {
        bst.insert(values[i]);
    }
	EXPECT_EQ(bst.find_max(), testdataMax)
		<< "Max should be 814\n";
}


// //testing remove function
TEST(BSTtests, remove){
	BinarySearchTree bst;
/*
	values = {258,  579,  814, -566, -686, -3,  -600,
                      382,  -562, -55, -768, 172,  252, 397,
                      -155, -898, 430, -520, 154,  255}*/
	EXPECT_FALSE(bst.remove(3))
		<< "Cannot remove on an empty tree\n";
	//int numValues = sizeof(values) / sizeof(int);
	int values[]  = {258,  579,  814, -566, -686, -3,  -600,
                       382,  -562, -55, -768, 172,  252, 397,
                       -155, -898, 430, -520, 154,  255};
    int numValues = sizeof(values) / sizeof(int);

	for (int i = 0; i < numValues; i++) {
        bst.insert(values[i]);
    }
	// middle of the tree
/*	EXPECT_EQ((bst.remove(-562)).node_count(), 19)
		<< "Node count should decrement\n";*/
	EXPECT_EQ(bst.contains(5), false);
	EXPECT_EQ(bst.contains(-562), true)
		<< "Shouldn't find value that was just"
			" removed from the tree\n";
}



// counting the number of nodes
TEST(BSTtests, node_count){
	BinarySearchTree bst;

	// empty tree should have zero nodes
	EXPECT_EQ(bst.node_count(), 0)
		<< "empty tree should have zero nodes\n";
	int values[]  = {258,  579,  814, -566, -686, -3,  -600,
                       382,  -562, -55, -768, 172,  252, 397,
                       -155, -898, 430, -520, 154,  255};
    int numValues = sizeof(values) / sizeof(int);

	for (int i = 0; i < numValues; i++) {
        bst.insert(values[i]);
    }

	EXPECT_EQ(bst.node_count(), 20)
		<< "Full tree should have 20 nodes\n";
}



// summation of all data vals of nodes
TEST(BSTtests, count_total){
	BinarySearchTree bst;

	EXPECT_EQ(bst.count_total(), 0)
		<< "Count total of empty tree"
			" is 0\n";
	int values[]  = {258,  579,  814, -566, -686, -3,  -600,
                       382,  -562, -55, -768, 172,  252, 397,
                       -155, -898, 430, -520, 154,  255};
    int numValues = sizeof(values) / sizeof(int);

	for (int i = 0; i < numValues; i++) {
        bst.insert(values[i]);
    }

	EXPECT_EQ(bst.count_total(), -1120)
		<< "Full tree should have count of"
			" -1120\n";

	bst.remove(-768);
	EXPECT_EQ(bst.count_total(), -352)
		<< "Value should be -352 after"
			" removing -768\n";
}



// determining the height of the tree
TEST(BSTtests, tree_height){
	BinarySearchTree bst;
	int values[]  = {258,  579,  814, -566, -686, -3,  -600,
                       382,  -562, -55, -768, 172,  252, 397,
                       -155, -898, 430, -520, 154,  255};
    int numValues = sizeof(values) / sizeof(int);

	EXPECT_EQ(bst.tree_height(), -1)
		<< "Tree without nodes has height"
			" of -1\n";
	bst.insert(1);
	EXPECT_EQ(bst.tree_height(), 0)
		<< "Tree with only root has height"
			" of 0\n";

	for (int i = 0; i < numValues; i++) {
        bst.insert(values[i]);
    }

	EXPECT_FALSE(bst.tree_height() == 2);

}


// seeing if a value exists in the tree
TEST(BSTtests, contains){
	BinarySearchTree bst;
	int values[]  = {258,  579,  814, -566, -686, -3,  -600,
                       382,  -562, -55, -768, 172,  252, 397,
                       -155, -898, 430, -520, 154,  255};
    int numValues = sizeof(values) / sizeof(int);

	EXPECT_FALSE(bst.contains(9))
		<< "Empty tree does not contain values\n";

	for (int i = 0; i < numValues; i++) {
        bst.insert(values[i]);
    }

	// middle of tree
	EXPECT_TRUE(bst.contains(-562));
	// leaf
	EXPECT_TRUE(bst.contains(255));
	// checking if it will return false;
	EXPECT_FALSE(bst.contains(99));
}