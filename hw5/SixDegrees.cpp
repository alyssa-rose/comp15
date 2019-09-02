/*
* Filename: SixDegrees.cpp
* Implementation file for SixDegrees class
* Comp15 HW5
* Alyssa Rose
* 30-March-2019
*/

#include <iostream>
#include <fstream>
#include <string>
#include "SixDegrees.h"

const int MAX_ACTORS = 500;

// std constructor
SixDegrees::SixDegrees(){
	g.initialize_graph(MAX_ACTORS);
}

// std destructor
// no memory to release
SixDegrees::~SixDegrees(){

}

void SixDegrees::run(istream &in, ostream &out){
    populate_graph();
    string actorOne, actorTwo;
    out << "Enter two actor names separated by" <<
    " a new line.\nPress ctrl-D to quit" << endl;
    while (getline(in, actorOne)){
        Actor actOne(actorOne);
        if (!g.is_vertex(actOne)){
            out << "Sorry, " << actOne <<
            " is not in the list\n";
            out << "\n";
        }
        else{
            getline(in, actorTwo);
            Actor actTwo(actorTwo);
            if (!g.is_vertex(actTwo)){
                bool k = false;
                while(k == false){
                    out << "Sorry, " << actTwo <<
                    " is not in the list\n";
                    out << "\n";
                    getline(in, actorTwo);
                    Actor actTwo(actorTwo);
                    k = g.is_vertex(actTwo);
                    if (k){
                        BFS(actOne, actTwo, out);
                        out << "\n";
                        break;
                    }
                }
            }
            else{
                BFS(actOne, actTwo, out);
                out << "\n";
            }
        }
    }
}
/*
* Function: populate_graph(char* j)
* Parameter: char* (file name)
* Output: none
* Does: populates the graph with actors from
*	input files as vertices and edges are formed
*	from the first instance that two actors are
*	in the same movie
*/
void SixDegrees::populate_graph(){
	ifstream infile;
	infile.open("actors.txt");
	string thisActor = "";
	string prev = "*";
    Actor *vert = g.returnVertex();
    int actCount = 0;

    while (getline(infile, thisActor)){
        Actor j(thisActor);
        if (thisActor != "*"){
            actCount++;
        }
        while(getline(infile, thisActor)){
            if (thisActor == "*")
                break;
            j.insert(thisActor);
        }
        g.add_vertex(j);
    }
    for (int i = 0; i < g.num_Vertices(); i++){
        for (int j = 0; j < g.num_Vertices(); j++){
            g.add_edge(vert[i], vert[j], 
                vert[i].connect(vert[j]));
        }
    }
    infile.close();
}

/*
* Function: BFS(Actor a, Actor b, ostream &out)
* Parameter: two Actor objects, and ostream to write
*	path to
* Output: none
* Does: finds shortest path between Actor a and Actor
*	b using breadth first search
*/
void SixDegrees::BFS(Actor a, Actor b, ostream &out){
    g.clear_marks();
    g.initialize_path();

    Queue<Actor> Neighbor;
    Queue<Actor> Primary;
    Primary.enqueue(a);

    Actor curr;
    Actor neighbor;
    bool i = false;
    while (!Primary.is_empty()){
        Primary.dequeue(curr);
        if (!g.is_marked(curr)){
            g.mark_vertex(curr);
            g.get_to_vertices(curr, Neighbor);
            while (!Neighbor.is_empty()){
                Neighbor.dequeue(neighbor);
                g.update_predecessor(curr, neighbor);
                if (neighbor == b){
                    i = true;
                    break;
                }
                else {
                    Primary.enqueue(neighbor);
                }
            }
        }
    }
    if (i)
        g.report_path(out, a, b);
    else {
        out << a << " and " << b << ": No connection" << endl;
    }
}