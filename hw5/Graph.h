/*
 * Filename: Graph.h
 * Contains: Interface of the template Graph class 
 * Part of: Homework 5 assignment "Graph Traversal" for Comp 15 Spring 2019
 *
 */

#include "Queue.h"
#include "Actor.h"
#include "Stack.h"
#include <iostream>
#include <ostream>

#ifndef GRAPH_H_
#define GRAPH_H_

// A good way to handle errors is with exceptions
// This class has a couple of them for common errors
// In this case we have one when there is no memory to 
// allocate and when someone does an invalid operation 
class FullGraph : public exception {
public:
  const char *what() const throw() { return "My graph is full";}
};

class EmptyGraph : public exception {
public:
  const char *what() const throw() { return "My graph is empty";}
};

const string NULL_EDGE = "\0";
const int NULL_PRED = -1;

// wrapper functions
template<class Vertex>
int index_is(Vertex *vertices, Vertex v);

template<class Vertex>
class Graph
{
public:
    //Constructor functions
    Graph();
    Graph(int);


    //*****Big Three*****//
    //Destructor
    ~Graph();
    //Copy constructor
    Graph(const Graph<Vertex> &source);
    //Assignment overload
    Graph<Vertex> &operator =(const Graph<Vertex> &source);


    // Functions needed to modify the graph
    void initialize_graph(int);         //allocates space for vertices
    void add_vertex(Vertex);            //adds a single vertex to the graph
    bool add_edge(Vertex, Vertex, string); //adds an edge to the graph


    void print_matrix(ostream &) const; //reports the edges of the graph


    // Helpers functions for implementing BFS and DFS
    bool is_vertex(Vertex) const;                        //checks if exists
    void get_to_vertices(Vertex, Queue<Vertex> &) const; //enqueues neighbors
    void clear_marks();                                  //clears all marks
    void mark_vertex(Vertex);                            //marks a vertex
    bool is_marked(Vertex) const;                        //checks if marked
    void initialize_path();                              //clears path info
    void update_predecessor(Vertex, Vertex);             //stores predecessor
    void report_path(ostream &, Vertex, Vertex) const;   //reports path

    string get_edge(Vertex a, Vertex b) const;
    int num_Vertices() const;
    Vertex* returnVertex() const;
    int* returnPath() const;
    bool *returnMarks() const;
    string** returnEdges() const; 
private:
    Vertex *vertices;
    // number of vertices of the graph
    int num_vertices;

    //****changed to string*****//
    string **edges;         // weighted 2-D array to store edges 


    int *path;              // array used to store a path
    int curr_vertex;        // variable to track current vertex in DFS
    bool *marks;            // boolean used to mark when a vertex has been visited
};

#endif


