/*
 *      CircularSequence.cpp 
 *      PartyPlaylist 
 *      Comp 15 Lab 3
 *
 *      2016-09-16 Created by Yennie Jun
 *      2016-09-20 Documentation added by Mark A. Sheldon, Tufts University
 */

#include <iostream>
#include <stdexcept>

#include "CircularSequence.h"


using namespace std;


/*
 * Return the index of the next element in the sequence.
 * Wraps around!
 */
int CircularSequence::nextIndex(int index)
{
        if (index == (capacity - 1)){
            index = 0;
            return index;
        }
        return index + 1;
}


/* Default Constructor */
CircularSequence::CircularSequence()
{
        init(INIT_CAPACITY);
}

/* 
 * Overloaded Constructor for a sequence with a hint for an initial
 * capacity. 
 */
CircularSequence::CircularSequence(int initialCapacity)
{
        init(initialCapacity);
}

/*
 * Initialize a new, empty sequence with an initial capacity.
 */
void CircularSequence::init(int initialCapacity)
{
        capacity      = initialCapacity;
        sequenceArray = new ElementType[capacity];
        currentSize   = 0;
        front         = 0;
        back          = 0;
}

/*
 * Destructor:  recycles the dynamically allocated array containing
 * the data.
 */
CircularSequence::~CircularSequence()
{
        delete [] sequenceArray;
}

/* 
 *  Add given element to the back of the list 
 *  Return true if element is successfully added.
 */
bool CircularSequence::addAtBack(ElementType elem) 
{
        if (currentSize == capacity) {
                expand();
        }
        sequenceArray[back] = elem;
        back                = nextIndex(back);
        currentSize++;

        return true;
}

/* 
 *  Add given element to the front of the list 
 *  Return true if element is successfully added.
 */
bool CircularSequence::addAtFront(ElementType elem)
{
        if (currentSize == capacity)
            expand();
        if (front == 0){
            sequenceArray[capacity - 1] = elem;
            currentSize++;
            front = capacity - 1;
            return true;
        }
        sequenceArray[(front - 1)] = elem;
        front = front - 1;
        currentSize++;
        return true;
}
                
/*
 * Remove the element at the back of the list 
 * and return it.
 */
ElementType CircularSequence::removeFromBack() 
{
        if (currentSize == 0)
            return NULL;
        ElementType k = sequenceArray[back - 1];
        back = (back - 1) % (capacity);
        currentSize--;
        return k;
}
 
/*
 * Remove the element at the front of the list 
 * and return it.
 */
ElementType CircularSequence::removeFromFront()
{
         if (currentSize == 0)
            return NULL;
        ElementType k = sequenceArray[front];
        front = (front + 1)%(capacity);
        currentSize--;
        return k;
}

/*
 * Expand the capacity of the array by a factor of 2.
 */
void CircularSequence::expand() 
{
        ElementType *newArr = new ElementType[capacity * 2];
        int j = front;
        for (int i = 0; i < capacity; i++){
            newArr[i] = sequenceArray[j];
            j = nextIndex(j);
        }
        front = 0;
        back = capacity;
        capacity = capacity * 2;
        delete [] sequenceArray;
        sequenceArray = newArr;
}

/*
 * Print the contents of the sequence, one element per line.
 */
void CircularSequence::printSequence() 
{
        int currIndex = front;
        for (int i = 0; i < currentSize; i++) {
                cout << sequenceArray[currIndex] << endl;
                currIndex = nextIndex(currIndex);
        }
}
// only time back is not empty is when array is full
