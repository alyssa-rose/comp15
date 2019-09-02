/*
 * Array.cpp
 * Alyssa Rose
 * 26-Jan-2019
 * COMP15
 * Spring 2019
 *
 * Implementation for Arrrrrrray of Pirates
 */

#include "ArrayList.h"
#include <iostream>
// Default constructor
// Length and current position default to 0
ArrayList::ArrayList(){
    pirates = new Pirate[MAX_PIRATES];
    length = 0;
    currPos = 0;
    capacity = MAX_PIRATES;
}
// Default Destructor
// Deallocates heap memory for pirates
ArrayList::~ArrayList(){
    delete [] pirates;
}

// Inputs: Pirate object, bool by reference
// Returns: Pirate object
// Does: Looks for pirate in the array, modifies bool if found
//       Returns the object from the list and not the passed one
//       (In case they're different.)
Pirate ArrayList::find(Pirate p, bool &found) const{
    int location = 0;

    while ((location < length) && !found){
        if (p == pirates[location]){
            found = true;
            p = pirates[location];
            break;
        }
        location++;
    }
    return p;
}

// Inputs: Pirate object
// Returns: Nothing
// Does: Adds Pirate to end of array, increases length
void ArrayList::insert(Pirate p){
    bool found = false;
    p = find(p ,found);
    if (!found){
        pirates[length] = p;
        length++;
    }
    if (length == (capacity)){
        expand();
    }
}

// Inputs: Pirate object
// Returns: Nothing
// Does: Deletes pirate, shifts everything else over
void ArrayList::remove(Pirate p){
    bool found = false;
    p = find(p, found);
    if (found){
        int cnt = 0;
        int find = 0;
        while (find == 0){
            if (pirates[cnt] == p){
                if (cnt != length){
                    for (int i = cnt + 1; i < length; i++)
                        pirates[i - 1] = pirates[i];
                }
                length = length - 1;
                find = 1;
            }
            cnt++;
        }
    }
    if (length < (capacity/2))
        shrink();
}

// Input: None
// Returns: Pirate object
// Does: Returns pirate at currPos
//       Increments currPos, but wraps around
Pirate ArrayList::getNext(){
    Pirate p = pirates[currPos];
    currPos = (currPos + 1) % length;
    return p;
}

// Input: none
// Returns: none
// Does: sets length to 0 (memory not modified)
void ArrayList::makeEmpty(){
    length = 0;
}

// Input: none
// Returns: none
// Does: sets currPos to 0 
void ArrayList::resetArray(){
    currPos = 0;
}

// Input: none, const
// Returns: none
// Does: Prints array from 0 to length
void ArrayList::print(ostream& os) const {
    for (int i = 0; i < length; i++){
        pirates[i].print(os);
        if (i != (length - 1))
            os << ", ";
    }

}

// Input: none, const
// Returns: int
// Does: Returns the value in length attribute
int ArrayList::getLength() const {
    return length;
}

// Input: none
// Returns: none
// Does: expands the array capacity
void ArrayList::expand(){
    cout << "Expand to " << capacity * 2 << endl;
    Pirate *newArr = new Pirate[capacity * 2];
    for (int i = 0; i < length; i++){
        newArr[i] = pirates[i];
    }
    delete [] pirates;
    pirates = newArr;
    capacity = capacity * 2;
}

// Input: none
// Returns: none
// Does: shrinks the size of the array
void ArrayList::shrink(){
    cout << "Contract to " << capacity / 2 << endl;
    Pirate *newArr = new Pirate[capacity / 2];
    for (int i = 0; i < length; i++){
        newArr[i] = pirates[i];
    }
    delete [] pirates;
    pirates = newArr;
    capacity = capacity / 2;
}
