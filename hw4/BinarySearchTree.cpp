/*
 * BinarySearchTree.cpp
 * Alyssa Rose
 * Comp15 HW$
 * 22 - Feb- 2019
 */

#include <iostream>
#include <climits>
#include <fstream>
#include <sstream>

#include "BinarySearchTree.h"

using namespace std;

// standard constructor
BinarySearchTree::BinarySearchTree()
{
    root = NULL;
}

// standard destructor
BinarySearchTree::~BinarySearchTree()
{
    // walk tree in post-order traversal and delete
    post_order_delete(root);
    root = NULL;  
}

/*
* Function: post_order_delete(Node *node)
* Inputs: pointer to a node
* Returns: nothing
* Does: deletes a tree using the method of
*   post order traversal
*/
void BinarySearchTree::post_order_delete(Node *node)
{
    if (node == NULL)
        return;
    post_order_delete(node -> left);
    post_order_delete(node -> right);
    delete node;
}

/*
* Function: parametrized constructor
* Inputs: reference to a tree
* Returns: 
* Does: uses pre order copy to copy
*   a tree into the root node
*/
BinarySearchTree::BinarySearchTree(const BinarySearchTree &source)
{
        // use pre-order traversal to copy the tree
    root = pre_order_copy(source.root);
}

/*
* Function: assignment overloader
* Inputs: reference to another tree
* Returns: reference to a tree
* Does: copies a tree into another using
*   the assignment operator
*/
BinarySearchTree &BinarySearchTree::operator= (const BinarySearchTree &source)
{
        // TODO: Students write code here
    if (this == &source)
        return *this;
    else {

        // delete current tree if it exists
        if (root != NULL)
            post_order_delete(root);
        // use pre-order traversal to copy the tree

        root = pre_order_copy(source.root);
        return *this;
    }
}

/*
* Function: pre_order_copy(Node *node)
* Inputs: pointer to a node
* Returns: ptr to a node
* Does: copies the tree using pre order traversal
*/
Node *BinarySearchTree::pre_order_copy(Node *node) const
{
    if (node == NULL)
        return NULL;
    Node *new_node = new Node();
    new_node -> data = node -> data;
    new_node -> count = node -> count;
    new_node -> left = pre_order_copy(node -> left);
    new_node -> right = pre_order_copy(node -> right);
    return new_node;

}

/*
* Function: find_min()
* Inputs: none
* Returns: integer(min value)
* Does: calls private find_min
*/
int BinarySearchTree::find_min() const
{
    if (root == NULL)
        return INT_MIN;
    return find_min(root)->data;
}

/*
* Function: find_min(Node *node)
* Inputs: pointer to a node
* Returns: ptr to a node
* Does: recurses through the left
*   subtrees to find the min
*/
Node *BinarySearchTree::find_min(Node *node) const
{
    if (node -> left == NULL)
        return node;
    return find_min(node -> left);
}

/*
* Function: find_max()
* Inputs: none
* Returns: integer(max val)
* Does: calls private find_max
*/
int BinarySearchTree::find_max() const
{
    if (root == NULL)
        return INT_MAX;
    return find_max(root)->data;
}

/*
* Function: find_max(Node *node)
* Inputs: pointer to a node
* Returns: ptr to a node
* Does: recurses through the right
*   subtrees to find the max
*/
Node *BinarySearchTree::find_max(Node *node) const
{
    if (node -> right == NULL)
        return node;
    return find_max(node -> right);
}

/*
* Function: contains(int value)
* Inputs: integer (val to be found)
* Returns: bool (true if found)
* Does: calls private contains func
*/
bool BinarySearchTree::contains(int value) const
{
    if (root == NULL)
        return false;
    return contains(root, value);
}

/*
* Function: contains(Node *node, int value)
* Inputs: ptr to a node and an integer value to
*   be searched for in the tree
* Returns: bool (true if the tree has the val)
* Does: uses recursion to search through all left 
*   and right subtrees to find the value if it
*   exists in the tree
*/
bool BinarySearchTree::contains(Node *node, int value) const
{
    if (node == NULL)
        return false;
    if ((node -> data) == value)
        return true;
    if ((node -> data) > value){
        return contains(node -> left, value);
    }
    return contains(node -> right, value);
}

/*
* Function: insert(int value)
* Inputs: integer (value to be inserted)
* Returns: nothing
* Does: calls private insert func
*/
void BinarySearchTree::insert(int value)
{
    insert(root, NULL, value);
}

/*
* Function: insert(Node *node, Node *parent, int value)
* Inputs: two nodes (a node and its parent) and
*   the integer val to be inserted into the tree
* Returns: nothing
* Does: inserts a value into the tree by use of
*   recursion
*/
void BinarySearchTree::insert(Node *node, Node *parent, int value)
{   
    if (node == NULL){
        Node *temp = new Node();
        temp -> data = value;
        temp -> count = 1;
        temp -> left = NULL;
        temp -> right = NULL;
        if (parent == NULL){
            root = temp;
            return;
        }

        if (value > (parent -> data))
            (parent -> right) = temp;
        if (value < (parent -> data))
           (parent -> left) = temp;
       return;
   }
   if ((node -> data) == value){
        (node -> count)++;
        return;
    }

   if (value > (node -> data)){
        insert(node -> right, node, value);
    }
    if (value < (node -> data)){
        insert(node -> left, node, value);
    }
}

/*
* Function: remove(int val)
* Inputs: integer
* Returns: bool; successful removal
*   or not
* Does: calls private remove func
*/
bool BinarySearchTree::remove(int value)
{
    // checking if tree exists
    if (root == NULL){
        return false;
    }
    // checking if the tree even has
    // the value to be removed
    if (!contains(root, value)){
        return false;
    }
    remove(root, NULL, value);
    return true;
}

/*
* Function: remove(Node *node, Node *parent, int value)
* Inputs: pointer to nodes (node and its parent) and
*   an integer value to be removed
* Returns: bool; successful removal or not
* Does: iterates through the tree using recursion
*   to find the node to be deleted. Calls helper func
*   to represent the 4 different cases to be dealt
*   with as a node is being deleted
*/
bool BinarySearchTree::remove(Node *node, Node *parent, int value)
{
    if ((node -> data) == value){
        if (node -> count > 1){
            (node -> count)--;
            return true;
        }
        else {
            if ((node -> left == NULL) and 
                (node -> right == NULL))
                no_kids(node, parent, value);
            else if (node -> left == NULL) 
                delete_right(node);
            else if (node -> right == NULL)
                delete_left(node);
            else {

                // finds max val of left subtree
                Node *replace = find_max(node -> left);
                node -> data = replace -> data;
                node -> count = replace -> count;
                replace -> count = 1;
                remove(node -> left, node, node -> data);

            }
            return true;
        }

    }
    if (value > (node -> data))
        return remove(node -> right, node, value);
    else
        return remove(node -> left, node, value);
}

/*
* Function: tree_height()
* Inputs: nothing
* Returns: nothing
* Does: calls the private tree_height
*/
int BinarySearchTree::tree_height() const
{
    if (root == NULL)
        return -1;
    if ((root -> left == NULL) and (root -> right == NULL))
        return 0;
    return tree_height(root);
}

/*
* Function: tree_height(Node *node)
* Inputs: pointer to a node
* Returns: an integer representing the
*   height of the tree
* Does: recurses through left and right 
*   subtrees to find the maximum height of 
*   the tree
*/
int BinarySearchTree::tree_height(Node *node) const
{
    if (node == NULL)
        return -1;
    // recursive step
    int rightIter = tree_height(node -> right);
    int leftIter = tree_height(node -> left);

    // returning the maximum height
    if (rightIter > leftIter)
        return rightIter + 1;
    else
        return leftIter + 1;
}

/*
* Function: node_count()
* Inputs: nothing
* Returns: integer
* Does: calls private node_count
*/
int BinarySearchTree::node_count() const
{
    if (root == NULL)
        return 0;
    return node_count(root);
}

/*
* Function: node_count(Node *node)
* Inputs: pointer to a node
* Returns: integer (number of nodes)
* Does: counts the number of nodes in a tree
*   by use of recursion (through all possible left
*   and right subtrees)
*/
int BinarySearchTree::node_count(Node *node) const
{
    if (node == NULL)
        return 0;
    return 1 + node_count(node -> right) + node_count(node -> left);

}

/*
* Function: count_total()
* Inputs: nothing
* Returns: integer 
* Does: calls the private count_total
*/
int BinarySearchTree::count_total() const
{
    if (root == NULL)
        return 0;
    return count_total(root);
}

/*
* Function: count_total(Node *node)
* Inputs: pointer to a node
* Returns: integer 
* Does: sums the values of the data aspect
*   of all nodes in the tree by use of recursing
*   through all possible left and right subtrees
*/
int BinarySearchTree::count_total(Node *node) const
{
    if (node == NULL)
        return 0;
    return (node -> data)*(node -> count) + 
    count_total(node -> right)+ count_total(node -> left);
}

/*
* Function: print_tree()
* Inputs: nothing
* Returns: nothing
* Does: calls printPretty to print in a 
*   formatted way
*/
void BinarySearchTree::print_tree() const
{
        printPretty(root, 1, 0, std::cout);
}

/*
* Function: find_parent(Node *node, Node *child)
* Inputs: pointer to two nodes
* Returns: pointer to the parent node
* Does: finds the parent of the child node
*/
Node *BinarySearchTree::find_parent(Node *node, Node *child) const
{
    if (node == NULL) return NULL;

        // if either the left or right is equal to the child,
        // we have found the parent
    if (node->left == child or node->right == child) {
        return node;
    }

        // Use the binary search tree invariant to walk the tree
    if (child->data > node->data) {
        return find_parent(node->right, child);
    } 
    else {
        return find_parent(node->left, child);
    }
}

/*
* Function: delete_right(Node *node)
* Inputs: pointer to a node
* Returns: nothing
* Does: Patricular case of remove() in which the
*   node being removed only has a right child
*/
void BinarySearchTree::delete_right(Node *node){
    node -> data = (node -> right) -> data;
    node -> count = (node -> right) -> count;
    delete node -> right;
    node -> right = NULL;
}

/*
* Function: delete_left(Node *node)
* Inputs: pointer to a node
* Returns: nothing
* Does: Patricular case of remove() in which the
*   node being removed only has a left child
*/
void BinarySearchTree::delete_left(Node *node){
    node -> data = (node -> left) -> data;
    node -> count = (node -> left) -> count;
    delete node -> left;
    node -> left = NULL;
}

/*
* Function: no_kids(Node *node, Node *parent, int value)
* Inputs: pointer to nodes (parent and node) and
*   an integer representing the value of a node
* Returns: nothing
* Does: Patricular case of remove() in which the
*   node being removed doesn't have children
*/
void BinarySearchTree::no_kids(Node *node, Node *parent, int value){
    if (value > parent -> data)
        parent -> right = NULL;
    else
        parent -> left = NULL;
    delete node;
}
