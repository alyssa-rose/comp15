/* 
 * Planet.cpp
 * COMP15
 * Fall 2018
 *
 * Interface for a Planet class
 */

#include "Planet.h"

Planet::Planet()
{
    name = "Earth";
}

Planet::Planet(string n)
{
    name = n;
}

void Planet::print(ostream &out) const
{
    out << name;
}

bool operator == (const Planet &p1, const Planet &p2)
{
    return (p1.name == p2.name);
}

