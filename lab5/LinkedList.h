/*
 * LinkedList.h
 * COMP15
 * Spring 2019
 * Google Test Lab
 *
 * Interface for LinkedList class
 *
 * Author: Kevin Destin
 * Date: 2/2/2019
 */

#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_
#include <initializer_list>
#include <iostream>

class LinkedList {
public:
        /* A typedef allows a type to be refered to by a different name.
         * In this case, ElementType is a Synonym for int. They can be used
         * interchangeably
         *
         * Allows code to be written more genericly. For example, this class
         * can be used with another type by changing the typedef. This idea
         * will be explored more in the future with Templates.
         */
        typedef int ElementType;

private:
        struct Node {
                ElementType info;
                Node *      next;

                /**
                 * @brief Parameterized Node Constructor
                 *
                 * @param i Data to store in node
                 * @param n Pointer to next node in list
                 */
                Node(const ElementType &i, Node *n) : info(i), next(n) {}

                /**
                 * @brief Returns a deep copy of node. Node pointed to by this
                 *        node is also deep copied
                 *
                 * @return Node* head to deep copied list of nodes
                 */
                Node *deepCopy() const {
                        return new Node(info, (next == nullptr)
                                                  ? nullptr
                                                  : next->deepCopy());
                }
        };

        bool  remove(Node *&, const ElementType &);
        Node *reverse(Node *, Node *newNode);

        int   size;
        Node *head;

public:
        LinkedList();
        ~LinkedList();
        LinkedList(const LinkedList &);
        LinkedList &operator=(const LinkedList &);

        // Parameterized Constructor. Allows LinkedList to be initialiazed as
        // LinkedList l = {a, b, c, d}
        LinkedList(const std::initializer_list<ElementType> &data);

        // Inserts element at front of list
        void push_front(const ElementType &);

        // Removes an instance of requested element from list. Returns whether
        // element was present before deletion
        bool remove(const ElementType &);

        // Checks if element is in list
        bool find(const ElementType &);

        // Returns ElementType at position i
        ElementType at(int i);

        // Empties the list
        void clear();

        // Returns the length of the list
        int length() const;

        // Print the list of ElementTypes, i.e
        // LinkedList ll;
        // cout << ll;
        friend std::ostream &operator<<(std::ostream &, const LinkedList &);
};

#endif
