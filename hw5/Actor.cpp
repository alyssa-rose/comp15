/*
* Filename: Actor.cpp
* Comp15 HW5
* 30-March-2019
* Alyssa Rose
*/

#include <iostream>
#include "Actor.h"

using namespace std;

/*
* Function: Actor()
* Parameter: none
* Output: none
* Does: std constructor
*/
Actor::Actor(){
	name = "";
	movieList.make_empty();
}

Actor::Actor(string thisName){
	name = thisName;
	movieList.make_empty();
}
/*
* Function: ~Actor()
* Parameter: none
* Output: none
* Does: std destructor
*/
Actor::~Actor(){
	movieList.make_empty();
}

/*
* Function: assignment overload (==)
* Parameter: name of other actor
* Output: bool
* Does: if *this and b have same name,
* 	returns true, false otherwise
*/
bool operator ==(Actor a, Actor b){
	if (a.name == b.name)
		return true;
	return false;
}

/*
* Function: assignment overload (!=)
* Parameter: name of other actor
* Output: bool
* Does: if *this and b dont' have same name,
* 	returns true, false otherwise
*/
bool operator !=(Actor a, Actor b){
	if (a.name != b.name)
		return true;
	return false;
}

/*
* Function: assignment d (<<)
* Parameter: none
* Output: none
* Does: prints name of *this Actor
*/
ostream &operator <<(ostream &out, const Actor &a){
	out << a.name;
	return out;
}

/*
* Function: insert
* Parameter: movie name (string)
* Output: bool
* Does: inserts the movie into the
*	actor's movie list and returns
*	true if successful
*/
bool Actor::insert(string movie){
	if (!alreadyListed(movie)){
		movieList.insert(movie);
		return true;
	}
	return false;
}

/*
* Function: alreadyListed(string movie)
* Parameter: string of movie title
* Output: bool
* Does: returns true is already in movie list
*/
bool Actor::alreadyListed(string movie){
	bool found = false;
	movieList.find(movie, found);
	return found;
}

/*
* Function: inMovie(string movie)
* Parameter: string of movie title
* Output: bool
* Does: returns true if actor was in movie
*/
bool Actor::inMovie(string movie){
	return alreadyListed(movie);
}

/*
* Function: connect(Actor costar)
* Parameter: Actor object
* Output: string of movie title *this and
*	costar have in common
* Does: finds a movie in common with *this
*	and costar
*/
string Actor::connect(Actor costar){
	int thisLen = movieList.get_length();
	bool found = false;
	string k = "";

	for (int i = 0; i < thisLen; i++){
		k = movieList.get_value_at(i);
		found = costar.inMovie(k);
		if (found)
			return k;
	}
	return "\0";
}

void Actor::emptyList(){
	movieList.make_empty();
}
/*
* TESTING PURPOSES ONLY
* prints the movies in the movie list
*/
void Actor::printMovieList(){
	movieList.print(cout);
}

/*
* TESTING PURPOSES ONLY
* checks if the movie list
* is empty, returns 1 if
* it is
*/
bool Actor::isEmpty(){
	return movieList.is_empty();
}
