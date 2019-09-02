/*
 * planet-driver.cpp
 * COMP15
 * Fall 2018
 *
 * Driver for the Linked List of Planets
 */

#include "LinkedList.h"
#include <iostream>
using namespace std;

// Function to reverse a linked list
void reverse_list(LinkedList &, LinkedList &);

// User string to stop entering planets
const string STOP = "done";

int main()
{
    // Make a list of planets and prompt user for names
	LinkedList planets,planets_inverse;
	string name;
	cout << "PART 1: Inserting at the front of the queue\n";
	do
	{
		cout << "Enter a planet (or \"done\" to stop)\n";
		cin >> name;
        cout << endl;

		if(name != STOP)
		{
			Planet p(name);
			planets.insert_planet(p);
		}
	} while (name != STOP);


    // Print in default order (backwards)
    cout << "List of planets, default:\n";
    planets.print(cout);	


    /*****************************************************/
    /* YOUR CODE HERE                                    */
    /* MAKE A SECOND LIST                                */
    /* AND CALL YOUR REVERSE FUNCTION                    */
    /* AND PRINT                                         */
    /*****************************************************/
    reverse_list(planets, planets_inverse);
    cout << "List of planets, correct order: \n";
    planets_inverse.print(cout);


	cout << "PART 2: Inserting at the back of the queue\n";
    cout << "This time with insert_planet_at_back\n";
	do
	{
		cout << "Enter a planet (or \"done\" to stop)\n";
		cin >> name;
        cout << endl;

		if(name != STOP)
		{
			Planet p(name);
			planets_inverse.insert_planet_at_back(p);
		}
	} while (name != STOP);


    // Print in default order (backwards)
    cout << "List of planets. We inserted at the back, so should be in correct order already\n";
    planets_inverse.print(cout);	


    return 0;	
}

// YOUR CODE HERE
// This function should take the elements of l
// and put them in reverse order into l2
// No need to return anything; both are passed by reference
void reverse_list(LinkedList &list1, LinkedList &list2)
{
	for (int i = 0; i < (list1.get_length()); i++){
		list2.insert_planet(list1.get_next_planet());
	}


}
