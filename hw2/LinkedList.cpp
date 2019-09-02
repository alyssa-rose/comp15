/*
 * LinkedList.cpp
 * Alyssa Rose
 * COMP15
 * Spring 2019
 * 
 * Implementation for Linked List of Green Line Extension Stations
 */

#include "LinkedList.h"
#include <iostream>
using namespace std;

// Default constructor
LinkedList::LinkedList(){
    length = 0;
    head = NULL;
    currPos = NULL;
    curr = 0;
}

// Destructor
LinkedList::~LinkedList() {
    makeEmpty();
}

// Assignment operator
LinkedList & LinkedList::operator = (const LinkedList &l){
    NodeType *temp;
    while (head != NULL){
        temp = head;
        head = head -> next;
        delete temp;
    }
    length = l.length;
    currPos = NULL;
    if (l.head == NULL)
        head = NULL;
    else{
        head = new NodeType;
        head->info = l.head->info;
        head->next = NULL;
        NodeType *curr = head;
        NodeType *orig = l.head;
        while (orig->next != NULL){
            curr->next = new NodeType;
            curr->next->info = orig->next->info;
            curr->next->next = NULL;
            orig = orig->next;
            curr = curr->next;
        }
    }
    return *this;
}

// Input: nothing
// Returns: the length
// Does: returns the length of the LL
int LinkedList::getLength() const{
    return length;
}

// Input: nothing
// Returns: true if currPos is NULL
// Does: determines if currPos is NULL or not
bool LinkedList::isCurrPosNull() const{
    return currPos == NULL;    
}

// Input: object of Station class
// Returns: nothing
// Does: inserts station into head of the list
void LinkedList::insertStation(Station s){
    NodeType *temp;
    temp = head;
    NodeType *curr = new NodeType;
    curr -> next = temp;
    curr -> info = s;
    head = curr;
    length++;
}

// Input: object of Station class
// Returns: nothing
// Does: deletes first instance of Station s
void LinkedList::removeStation(Station s){
    NodeType *curr;
    NodeType *back;
    back = head;
    if (head == NULL)
        return;
    if (s.isEqual(back -> info)){
            head =  back -> next;
            delete back;
            length--;
            return;
    }
    if (getLength() >= 2){
            curr = back -> next;
            for (int i = 0; i < getLength() - 1; i++){
                if (!(s.isEqual(curr -> info))){
                    back = curr;
                    curr = curr -> next;
                }
                else {
                    back -> next = curr -> next;
                    delete curr;
                    length--;
                    break;
                }
            }
        }
    }


// Input: none
// Returns: object of Station class
// Does: returns the current station and
//       updates currPos to the next station
Station LinkedList::getNextStation(){
    NodeType *temp;
    if (isCurrPosNull())
        currPos = head;
    if (currPos -> next == NULL){
        temp = currPos;
        currPos = NULL;
        return temp -> info;
    }
    temp = currPos;    
    currPos = currPos -> next;
    curr++;
    return temp -> info;
}

// Input: none
// Returns: none
// Does: sets currPos to NULL
void LinkedList::resetCurrPos(){
   currPos = NULL;
}

// Input: none
// Returns: none
// Does: deletes all elements in the
//       linked list
void LinkedList::makeEmpty(){
    if (head == NULL)
        return;
    NodeType *curr = head;
    NodeType *forward = curr -> next;
    while (forward != NULL){
        delete curr;
        curr = forward;
        forward = forward -> next;
    }
    head = NULL;
    delete curr;
}

// Input: reference to ostream object
// Returns: none
// Does: prints all stations in order
void LinkedList::print(ostream &out){
    resetCurrPos();
    curr = 0;
    Station k;
    for (int i = 0; i < getLength(); i++){
        k = getNextStation();
        k.print(out); 
        out << " " << getLength() - i - 1;
        if (i != getLength() - 1)
            out <<  " == ";
        if (i == (getLength() - 1))
            out << "\n";
    }
}



