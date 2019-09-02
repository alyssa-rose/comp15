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

    // The basic operations:
    // Insert, Delete, and Find
    Pirate find_pirate(Pirate, bool &) const;
    void insert_pirate(Pirate);
    void delete_pirate(Pirate);
    Pirate get_next_pirate();

    // Start over at the beginning of the list
    void make_empty();
    void reset_array();

    // Return some basic info
    bool is_full() const;
    int get_length() const;

    // Print the array
    void print() const;

private:
    int length;
    Pirate pirates[MAX_PIRATES];
    int curr_pos;
};

#endif
