/*
 * LinkedList.cpp
 * COMP15
 * Spring 2019
 * Google Test Lab
 *
 * Implementation for LinkedList class
 *
 * Author: Kevin Destin
 * Date: 2/2/2019
 */

#include "LinkedList.h"

/**
 * @brief Default Constructor
 */
LinkedList::LinkedList() : size(0), head(nullptr) {}

// Destructor
LinkedList::~LinkedList() {
        clear();
}

/**
 * @brief Assignment Operator
 */
LinkedList &LinkedList::operator=(const LinkedList &l) {
        if (this == &l)
                return *this;

        clear();

        if (l.head == nullptr)
                return *this;

        head = l.head->deepCopy();
        size = l.size;
        return *this;
}

/**
 * @brief      Parameterized Constructor
 *             Allows LinkedList to be initialized as follows:
 *                      LinkedList ll = {1, 2, 3, 4, 5};
 *
 * @param data List of elements to add to list
 *
 * @note:      Adding ": LinkedList()" after the parameter list makes this
 *             constructor first call the default constructor.
 */
LinkedList::LinkedList(const std::initializer_list<ElementType> &data)
    : LinkedList() {
        // For-each loop
        // Read as: For each ElementType d in data
        // More info: http://www.cplusplus.com/doc/tutorial/control/#rangefor
        for (ElementType d : data)
                push_front(d);

        head = reverse(head, nullptr);
}

/**
 * @brief         Reverses the list
 *
 * @param curr    The current node
 * @param newNext The current node's new next pointer
 *
 * @return        The new head of the list
 */
LinkedList::Node *LinkedList::reverse(Node *curr, Node *newNext) {
        // curr will only be nullptr if list is empty
        if (curr == nullptr)
                return nullptr;

        Node *temp = curr->next;
        curr->next = newNext;

        return (temp == nullptr) ? curr : reverse(temp, curr);
}

/**
 * @brief Copy Constructor
 *
 * @Note: Adding ": LinkedList()" after the parameter list makes to copy
 *        constructor call the default construct first.
 */
LinkedList::LinkedList(const LinkedList &l) : LinkedList() {
        if (l.head == nullptr)
                return;

        head = l.head->deepCopy();
        size = l.size;
}

/**
 * @brief Gets the length of the list
 */
int LinkedList::length() const {
        return size;
}

/**
 * @brief       Adds element to front of list
 *
 * @param toAdd Element to add to list
 */
void LinkedList::push_front(const ElementType &toAdd) {
        // Dynamically allocate a new node, intialized using Node constructor
        head = new Node(toAdd, head);
        size++;
}

/**
 * @brief          Helper function for recursive remove
 *
 * @param toRemove Element to Remove
 */
bool LinkedList::remove(const ElementType &toRemove) {
        return remove(head, toRemove);
}

/**
 * @brief         Checks whether element exists in list
 *
 * @param  toFind element to find
 *
 * @return        true if found
 *                false otherwise
 */
bool LinkedList::find(const ElementType &toFind) {
        Node *curr = head;

        while (curr != nullptr) {
                if (curr->info == toFind)
                        return true;
                curr = curr->next;
        }

        return false;
}

/**
 * @brief          Iterates through LinkedList recursively, and deletes a
 *                 single instance of requested element if it exists
 *
 * @param curr     Reference to current node pointer
 * @param toRemove Element to delete
 *
 * @return         true if element was found and deleted false otherwise
 */
bool LinkedList::remove(Node *&curr, const ElementType &toRemove) {
        if (curr == nullptr)
                return false;

        if (curr->info == toRemove) {
                // Store address of node we will delete
                Node *temp = curr;

                // Curr is pass by reference, so this will modify the variable
                // used as the parameter (i.e next pointer of previous node)
                curr = curr->next;

                // Deallocate node we removed from list
                delete temp;

                size--;

                return true;
        } else
                // Pass return value up the chain of recursive calls
                return remove(curr->next, toRemove);
}

/**
 * @brief Removes all elements from list.
 *        List is returned to its default state (size == 0)
 *
 */
void LinkedList::clear() {
    while (head != nullptr) {
        Node *temp = head -> next;
        delete head;
        head = temp;
    }
    size = 0;
}

/**
 * @brief Gets the element at position i in the list
 *
 * @param i The Index
 *
 * @throws logic_error if index is out of range, or if list is empty
 *
 * @return LinkedList::ElementType
 */
LinkedList::ElementType LinkedList::at(int i) {
        if (not(0 <= i and i < size))
                throw std::logic_error("Error: Index out of range\n");

        Node *temp = head;

        while (i-- != 0)
                temp = temp->next;

        return temp->info;
}

/**
 * @brief Prints list
 *
 * @param out
 */
std::ostream &operator<<(std::ostream &out, const LinkedList &l) {
        using Node = LinkedList::Node;  // == typedef LinkedList::Node Node

        if (l.head != nullptr) {
                // Print out the head
                out << l.head->info;

                // If there are more ElementTypes, print formatted output
                for (Node *tmp = l.head->next; tmp != nullptr; tmp = tmp->next)
                        out << " -> " << tmp->info;

                out << " -> ";
        }
        out << "NULL\n";

        return out;
}
