/*
 * LinkedList.h
 * COMP15
 * Fall 2018
 *
 * Interface for Linked List of Planets
 *
 * What is an astronaut's favorite candy bar?
 *
 * A milky way!
 */

#include "Planet.h"
#include <fstream>

#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

class LinkedList
{
public:
    // Default constructor
    LinkedList();

    // Default Destructor
    //~LinkedList();
    // Assignment Operator
    LinkedList & operator = (const LinkedList &);

    // Inserts a planet (at the front of the list)
    void insert_planet(Planet);

   // Inserts a planet (at the front of the list)
    void insert_planet_at_back(Planet);
 
    //Advances the pointer of curr_pos and returns the name of next Planet
    Planet get_next_planet();

    // Return some basic info
    int get_length() const;

    // Print the list
    void print(ostream &) const;

private:
    int length;
    NodeType *head;
    NodeType *curr_pos;
};

#endif
