/*
 * ArrayList.h
 * COMP15
 * Spring 2019 
 *
 * Interface for Array of Pirates, matey
 */

#include "Pirate.h"

#ifndef ARRAY_H_
#define ARRAY_H_

const int MAX_PIRATES = 100;

class ArrayList
{
public:
    // Default constructor
    ArrayList();
    ~ArrayList();
    // The basic operations:
    // Insert, Delete, and Find
    Pirate find(Pirate, bool &) const;
    void insert(Pirate);
    void remove(Pirate);
    Pirate getNext();

    // Start over at the beginning of the list
    void makeEmpty();
    void resetArray();

    // Return some basic info
    //rem
    //bool isFull() const;
    int getLength() const;

    // Print the array
    void print(ostream& os) const;

private:
    // Shrinks to 1/2 capacity if
    // length < (capacity / 2)
    void shrink();
    // Expands to 2 * capacity if
    // length = capacity + 1
    void expand();
    int length;
    Pirate* pirates;
    int currPos;
    int capacity;
};

#endif
