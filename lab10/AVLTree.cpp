/*
 * Filename: AVLTree.cpp
 * Contains: Implementation of AVL Trees for COMP15
 * Part of: Lab assignment "AVL Trees" for Comp 15
 *
 */

#include <iostream>
#include "AVLTree.h"

using namespace std;


/* 
 * Input: data (the value to store), height of the node, left and 
 *       right child pointers
 * Returns: avl tree node.
 * Does: creates a new node with values given as input parameter
*/
static Node *newNode(int data, int height, Node *left, Node *right)
{
        Node *np = new Node();
    
        np->data  = data;
        np->height = height;
        np->left  = left;
        np->right = right;

        return np;
} 


/* 
 * Input: data (the value to store)
 * Returns: avl tree node.
 * Does: calls a helper function to create a new nodewith default
 *        values parameter
*/
static Node *newNode(int data)
{
        return newNode(data, 0, NULL, NULL);
}



/* 
 * Input: the node to be deleted.
 * Returns: N/A
 * Does: Set node contents to predictable, "deleted" node values
 *       and then recycle the node.
*/
static void deleteNode(Node *np)
{
        np->height = -1;  /* Something that couldn't be in a real node */
        np->data  = -1;  /* Arbitrary value                           */
        np->left  = np->right = NULL;
        delete 
        np;
}



/* 
 * Input: N/A
 * Returns: AVL class object
 * Does: Sets the root node to NULL
*/
AVLTree::AVLTree()
{
        root = NULL;
}

/* 
 * Input: N/A
 * Returns: N/A
 * Does: Deletes the AVL tree clears the memory used. Resets the root pointer
*/
AVLTree::~AVLTree()
{
        /* walk tree in post-order traversal and delete */
        post_order_delete(root);
        root = NULL;   /* not really necessary, since the tree is going 
                        away, but might want to guard against someone
                        using a pointer after deleting */
}


/* 
 * Input: a node of an AVL tree
 * Returns: N/A
 * Does: Deletes the AVL tree of node in a post order manner.
*/
void AVLTree::post_order_delete(Node *node)
{
        if (node != NULL) {
                post_order_delete(node->left);
                post_order_delete(node->right);
                deleteNode(node);
        }
}


/* 
 * Input: an integer value to be inserted in the AVL tree
 * Returns: N/A
 * Does: Calls a helper function to insert the given value in the tree.
*/
void AVLTree::insert(int value)
{
        root = insert(root, value);
}


/* 
 * Input: Node np - a node of the avl tree. value - an integer value to 
 *         be inserted in the AVL tree
 * Returns: the updated subtree of np.
 * Does: Inserts within a AVL tree the given value, while maintaining the 
 *        AVL invarient 
*/
Node *AVLTree::insert(Node *np, int value)
{
        /* BST insertion start */
        if (np == NULL) {
                return newNode(value);

        } else if (value < np->data) {
                np->left = insert(np->left, value);
        
        } else if (value > np->data) {
                np->right = insert(np->right, value);
        } else if (value == np->data) {
        	return np;
        }
        /* BST insertion ends */

        /* AVL maintenance start */
        np->height = 1 + max(nodeHeight(np->left), nodeHeight(np->right));
        np = balance (np);
        /* AVL maintenace end */

        return np;
}

/* 
 * Input: Node np - a node of the avl tree.
 * Returns: the balanced subtree of np.
 * Does: If unbalanced, balances the subtree of node.
*/
Node *AVLTree::balance(Node *np) 
{
        if (heightDiff(np) > 1){
            cerr << "Height diff left: " << heightDiff(np ->left) << endl;
            cerr << "Node height left: " << nodeHeight(np -> left) << endl;
            cerr << "Node height right: " << nodeHeight(np -> right) << endl;
            cerr << "height diff > 1" << endl;
            if (heightDiff(np -> left) >= 1){
                cerr << "height on left > 1" << endl;
                np = rightRotate(np);
                cerr << "right rotate 1" << endl;
                return np;
            }
            else{
                cerr << "height diff on left < -1" << endl;
                np -> left = leftRotate(np -> left);
                cerr << "left rotate 1" << endl;
                np = rightRotate(np);
                cerr << "right rotate 1" << endl;
                return np;
            }
        }

        if (heightDiff(np) < -1){
            cerr << "height diff < -1" << endl;
            if (heightDiff(np -> right) <= -1 ){
                cerr << "height on right < -1" << endl;
                np = leftRotate(np);
                cerr << "left rotate 2" << endl;
            }
            else {
                cerr << "height diff on right > 1" << endl;
                np -> right = rightRotate(np -> right);
                cerr << "right rotate 2" << endl;
                np = leftRotate(np);
                cerr << "left rotate 2" << endl;
            }
        }
        return np; //This line is in here so that the code compiles
                   //Remove it if not needed when implementing 
}

/* 
 * Input: Node np - a node of the avl tree.
 * Returns: newly rooted node.
 * Does: left rotate subtree rooted with np  
*/
Node *AVLTree::rightRotate(Node *np) 
{ 
    // left subtree right child
    // and left subtree/ left child
    //Node *parent = np -> right;
    //Node *switchNode = parent -> left;
    Node *switchNode = np -> left;
    np -> left = switchNode -> right;
    switchNode -> right = np;
    np->height = 1 + max(nodeHeight(np->left), nodeHeight(np->right));
    switchNode->height = 1 + max(nodeHeight(switchNode->left), nodeHeight(switchNode->right));
    return switchNode;

} 
  
/* 
 * Input: Node np - a node of the avl tree.
 * Returns: newly rooted node.
 * Does: left rotate subtree rooted with np  
*/
Node *AVLTree::leftRotate(Node *np) 
{ 
    // right subtree left child
    // right subtree right child
   //Node *parent =  np -> left;
   Node *switchNode = np -> right;
   np -> right = switchNode -> left;
   switchNode -> left = np;
   np->height = 1 + max(nodeHeight(np->left), nodeHeight(np->right));
   switchNode->height = 1 + max(nodeHeight(switchNode->left), nodeHeight(switchNode->right));
   return switchNode;

} 



/* 
 * Input: Node np - a node of the avl tree.
 * Returns: integer value signifying the height difference.
 * Does: calculates the difference in the height of the left and child 
 *       subtree of np
*/
int AVLTree::heightDiff(Node *np)
{
        int l_height = nodeHeight (np->left);
        int r_height = nodeHeight (np->right);

        int b_factor= l_height - r_height;
        return b_factor;
}



/* 
 * Input: Node np - a node of the avl tree.
 * Returns: integer denoting the height attribute
 * Does: a getter to get the value of the height attribute.
*/
int AVLTree::nodeHeight(Node *node) 
{ 
        if (node == NULL) 
                return -1; 
        return node->height; 
} 


/* 
 * Input: value to be removed from the avl tree
 * Returns: bool signifying the success of the function.
 * Does: removes the given node value form the avl tree
 *       with the help of a helper function.
*/
bool AVLTree::remove(int value)
{
        return remove(root, value);
}

/* 
 * Input: Node np - a node of the avl tree. value to be removed 
 * from the avl tree
 * Returns: bool signifying the success of the function.
 * Does: removes the given node value form the avl tree
*/
bool AVLTree::remove(Node *node, int value)
{
        return true;
}


/* 
 * Input: N/A
 * Returns: N/A
 * Does: uses a helper function to print a pretty tree.
*/
void AVLTree::print_tree() const
{
        printPretty(root, 1, 0, std::cout);
}
