/*
 * Pirate.h
 * COMP15
 * Spring 2019
 *
 * Interface for a Pirate class
 * yo ho ho
 */

#include <fstream>
#include <string>
using namespace std;

#ifndef PIRATE_H_
#define PIRATE_H_


class Pirate
{
public:
    Pirate();
    Pirate(string);
    void print() const;
    void generate_pirate_name(ifstream &, int);
    void assign_pirate_id();
    friend bool operator == (const Pirate &, const Pirate &);
private:
    int pirate_id;
    string name;
    static int pirate_count;
};

#endif
