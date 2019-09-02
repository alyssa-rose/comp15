/*
 * Array.cpp
 * COMP15
 * Spring 2019
 *
 * Implementation for Arrrrrrray of Pirates
 */

#include "ArrayList.h"

// Default constructor
// Length and current position default to 0
ArrayList::ArrayList()
{
    length = 0;
    curr_pos = 0;
}

// Function find_pirate
// Inputs: Pirate object, bool by reference
// Returns: Pirate object
// Does: Looks for pirate in the array, modifies bool if found
//       Returns the object from the list and not the passed one
//       (In case they're different.)
Pirate ArrayList::find_pirate(Pirate p, bool &found) const
{
    int location = 0;

    while ((location < length) && !found)
    {
        if (p == pirates[location])
        {
            found = true;
            p = pirates[location];
            break;
        }
        location++;
    }
    return p;
}

// Function insert_pirate
// Inputs: Pirate object
// Returns: Nothing
// Does: Adds Pirate to end of array, increases length
void ArrayList::insert_pirate(Pirate p)
{
    pirates[length] = p;
    length++;
}

// Function delete_pirate
// Inputs: Pirate object
// Returns: Nothing
// Does: Deletes pirate, shifts everything else over
void ArrayList::delete_pirate(Pirate p)
{
    int location = 0;

    while (location < length)
    {
        if (p == pirates[location])
            break;
        else
            location++;
    }

    // Once you've found the pirate, shift
    // everything over to the left by one
    while (location < (length-1))
    {
       pirates[location] = pirates[location+1];
       location++;
    }
    length--;
}

// Function get_next_pirate
// Input: None
// Returns: Pirate object
// Does: Returns pirate at curr_pos
//       Increments curr_pos, but wraps around
Pirate ArrayList::get_next_pirate()
{
    Pirate p = pirates[curr_pos];
    curr_pos = (curr_pos + 1) % length;
    return p;
}

// Function make_empty
// Input: none
// Returns: none
// Does: sets length to 0 (memory not modified)
void ArrayList::make_empty()
{
    length = 0;
}

// Function reset_array
// Input: none
// Returns: none
// Does: sets curr_pos to 0
void ArrayList::reset_array()
{
    curr_pos = 0;
}

// Function print
// Input: none, const
// Returns: none
// Does: Prints array from 0 to length
void ArrayList::print() const
{
    for (int i = 0; i < length; i++)
        pirates[i].print();
}

// Function is_full
// Input: none, const
// Returns: bool
// Does: Compares actual length to capacity
bool ArrayList::is_full() const
{
    return (length >= MAX_PIRATES);
}

// Function get_length
// Input: none, const
// Returns: int
// Does: returns the current value in length attribute
int ArrayList::get_length() const
{
    return length;
}
