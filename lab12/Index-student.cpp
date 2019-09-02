/*
 * Filename: Index-student.cpp
 * Contains: Implementation of the Index class
 *           Each Index object contains a vector of filenames it has parsed
 *           and an unordered map that uses words as keys and a vector of 
             Entry objects as values.
 * Part of: Lab 12 for Comp15 - Spring 2019
 *
 */

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "DirNode.h"
#include "FSTree.h"
#include "Index.h"

using namespace std;

/**
 * Function: query
 * Parameters: string to query, ostream object to print matches to
 * Returns: void
 * Does: searches the Index object to see if it contains any instances of the 
 * word to be queried... prints out all the Entry objects which describe unique 
 * locations of particular instances of the word.
 * 
 */
void Index::query(const string &toQuery, ostream &out) const {
        for (int i = 0; i < (int)entries.size(); i ++){
            if (entries[i].string == toQuery)
                reportMatch(entries[i], out);
        }
}

/**
 * Function: parseFile
 * Parameters: name(a string) of file to be parsed
 * Returns: void
 * Does: parses every word of every line of a particular file and accounts for
 * every instance of a word by creating a unique Entry object and storing said 
 * object in the Index (note: a word which appears several times in a line is 
 * only included once in the Index object).
 *
 */
void Index::parseFile(const string &filename) {
        ifstream  infile(filename);
        string    line, word;
        streampos position;    // This a way of remembering positions in a file
        unsigned  lineno = 0;  // Current line number
        size_t    fileno = files.size();  // Current file index in files array

        if (!infile)
                throw runtime_error("Could not open " + filename);

        // Save position of infile (to remember where current line starts),
        // then get the line
        // Uses comma operator : https://en.wikipedia.org/wiki/Comma_operator
        while (position = getPosition(infile), getline(infile, line)) {
                stringstream ss(line);
                lineno++;

                // Get each word in line
                while (ss >> word) {
                    word = cleanString(word);
                    Entry e(word, lineno, position, fileno);
                    vector<Entry> EntryList;
                    if (shouldAdd(EntryList, e))
                        EntryList.push_back(e);               
                }
        }

        files.push_back(filename);
}

