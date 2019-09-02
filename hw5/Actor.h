/*
* Filename: Actor.h
Contains: Interface of the Actor class
Comp15 HW5
Alyssa Rose
*/

#include <iostream>
#include "LinkedList.h"

using namespace std; 

#ifndef ACTOR_H_
#define ACTOR_H_

class Actor{
public:
	Actor();
	Actor(string name);
	~Actor();
	friend bool operator ==(Actor a, Actor b);
	friend bool operator !=(Actor a, Actor b);
	friend ostream& operator <<(ostream &out, const Actor &a);
	
	//returns name of movie that *this and
	// other actor obj share in common
	string connect(Actor costar);
	//inserts movie into the the
	//list of movies actor is in
	bool insert(string movie);
	//actor name
	string name;
	//determines if actor was in movie
	bool inMovie(string movie);
	// empties the list
	void emptyList();

	/*****testing only*****/
	void printMovieList();
	bool isEmpty();
private:
	//LL of movie titles
	LinkedList<string> movieList;

	//checks if movie already in list
	bool alreadyListed(string movie);
	
};
#endif