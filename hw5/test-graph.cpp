/*
* Filename: test-graph.cpp
* Comp15 HW5
* Alyssa Rose
* 31-March-2019
*/

#include <iostream>
#include<fstream>

#include "Graph.h"
#include "Actor.h"
#include "SixDegrees.h"
#include "Stack.h"
#include "Queue.h"
#include "LinkedList.h"
#include "NodeType.h"

/*** Six Degrees Class ***/
void test_populate_graph_test();
void test_BFS();
void test_report_path();
void test_run();

/*** Actor Class ***/
void test_insert();
void test_inMovie();
void test_connect();
void test_equal_overload();
void test_not_equal_overload();
void test_print_overload();

/*** Graph Class ***/
void test_is_vertex();
void test_add_edge();
void test_get_edge();
void test_get_to_vertices();


int main(){
	/*** Six Degrees Class ***/
	test_populate_graph_test();
	test_BFS();
	test_report_path();
	test_run();

	/*** Actor Class ***/
	test_insert();
	test_inMovie();
	test_connect();
	test_equal_overload();
	test_not_equal_overload();
	test_print_overload();
	
	/*** Graph Class ***/
	test_is_vertex();
	test_add_edge();
	test_get_edge();
	test_get_to_vertices();
	return 0;
}

/*****************************************************************************/
	/***Testing the SixDegrees Class***/
/*****************************************************************************/
/*
* Function: Function to test the abiity of the 
* populate_graph() func to work
*/
void test_populate_graph_test(){
	Graph<Actor> g(500);

	ifstream infile;
	infile.open("actors.txt");
	string thisActor = "";
	string prev = "*";
	int actCount = 0;
	
	Actor *vert = g.returnVertex();

	while (getline(infile, thisActor)){
		Actor j(thisActor);
		if (thisActor != "*"){
			//(j.movieList).is_empty();
			cerr << "Creating new actor: " << thisActor << endl;
			actCount++;
		}
		while(getline(infile, thisActor)){
			if (thisActor == "*")
				break;
			cerr << thisActor << endl;
			j.insert(thisActor);
		}
		g.add_vertex(j);
		vert[actCount].printMovieList();
	}
	//cerr << (vert[123].movieList).is_empty() << endl;
	cerr << actCount << endl;
	vert[168].printMovieList();
	cerr << vert[168] << endl;
    for (int i = 0; i < g.num_Vertices(); i++){
        for (int j = 0; j < g.num_Vertices(); j++){
            g.add_edge(vert[i], vert[j], 
                vert[i].connect(vert[j]));
        }
    }

}



/*
* tests the BFS function using the small 
* case of Meryl Streep and Stanley Tucci
*/
void test_BFS(){
	Graph<Actor> g(500);

	ifstream infile;
	infile.open("actors.txt");
	string thisActor = "";
	string prev = "*";
	int actCount = 0;
	
	Actor *vert = g.returnVertex();

	while (getline(infile, thisActor)){
		Actor j(thisActor);
		if (thisActor != "*"){
			//(j.movieList).is_empty();
			cerr << "Creating new actor: " << thisActor << endl;
			actCount++;
		}
		while(getline(infile, thisActor)){
			if (thisActor == "*")
				break;
			cerr << thisActor << endl;
			j.insert(thisActor);
		}
		g.add_vertex(j);
		vert[actCount].printMovieList();
	}
    for (int i = 0; i < g.num_Vertices(); i++){
        for (int j = 0; j < g.num_Vertices(); j++){
            g.add_edge(vert[i], vert[j], 
                vert[i].connect(vert[j]));
        }
    }

	g.clear_marks();
	g.initialize_path();

/***************************************/
    // changed to Actor//
	Queue<Actor> Neighbor;
	Queue<Actor> Primary;

	Actor a("Meryl Streep");
	Actor b("Stanley Tucci");
	Primary.enqueue(a);

	Actor curr;
	Actor neighbor;
	while (!Primary.is_empty()){
		Primary.dequeue(curr);
		if (!g.is_marked(curr)){
			g.mark_vertex(curr);
			g.get_to_vertices(curr, Neighbor);
			while (!Neighbor.is_empty()){
				Neighbor.dequeue(neighbor);
				g.update_predecessor(curr, neighbor);
				if (neighbor == b)
					break;
				else {
					Primary.enqueue(neighbor);
				}
			}
		}
	}
}




/*
* test the report path function
*/
void test_report_path(){
	/*************************************************/
		/***making graph object***/
	/************************************************/
	Graph<Actor> g(500);

	ifstream infile;
	infile.open("actors.txt");
	string thisActor = "";
	string prev = "*";
	int actCount = 0;
	
	Actor *vert = g.returnVertex();

	while (getline(infile, thisActor)){
		Actor j(thisActor);
		if (thisActor != "*"){
			//(j.movieList).is_empty();
			cerr << "Creating new actor: " << thisActor << endl;
			actCount++;
		}
		while(getline(infile, thisActor)){
			if (thisActor == "*")
				break;
			cerr << thisActor << endl;
			j.insert(thisActor);
		}
		g.add_vertex(j);
		// making sure vertices added properly
		vert[actCount].printMovieList();
	}
	for (int i = 0; i < g.num_Vertices(); i++){
		for (int j = 0; j < g.num_Vertices(); j++){
			g.add_edge(vert[i], vert[j], 
				vert[i].connect(vert[j]));
		}
	}

	g.clear_marks();
	g.initialize_path();


	/*************************************************/
		/***BFS on Meryl Streep and John Goodman***/
	/************************************************/
    // changed to Actor//
	Queue<Actor> Neighbor;
	Queue<Actor> Primary;

	// ***Prints as Expected
	Actor a("Anjelica Huston");
	Actor b("Steve Martin");
	Primary.enqueue(a);

	Actor curr;
	Actor neighbor;
	
	while (!Primary.is_empty()){
		Primary.dequeue(curr);
		if (!g.is_marked(curr)){
			g.mark_vertex(curr);
			g.get_to_vertices(curr, Neighbor);
			while (!Neighbor.is_empty()){
				Neighbor.dequeue(neighbor);
				g.update_predecessor(curr, neighbor);
				if (neighbor == b)
					break;
				else {
					Primary.enqueue(neighbor);
				}
			}
		}

	}
	if (!Neighbor.is_empty() or curr == b)
		g.report_path(cerr, a, b);
	else {
		cerr << a << " and " << b << ": No connection" << endl;
	}


	Queue<Actor> Neighbor2;
	Queue<Actor> Primary2;

	// ***Prints as Expected
	Actor c("Meryl Streep");
	Actor d("John Goodman");
	Primary2.enqueue(c);

	bool i = false;
	Actor curr2;
	Actor neighbor2;
	while (!Primary2.is_empty()){
		Primary2.dequeue(curr2);
		if (!g.is_marked(curr2)){
			g.mark_vertex(curr2);
			g.get_to_vertices(curr2, Neighbor2);
			while (!Neighbor2.is_empty()){
				Neighbor2.dequeue(neighbor2);
				g.update_predecessor(curr2, neighbor2);
				if (neighbor2 == d){
					i = true;
					break;
				}
				else {
					Primary2.enqueue(neighbor2);
				}
			}
		}
	}
	if (i)
		g.report_path(cerr, c, d);
	else {
		cerr << c << " and " << d << ": No connection" << endl;
	}


	Queue<Actor> Neighbor3;
	Queue<Actor> Primary3;

	// ***Prints as Expected
	Actor e("Allison Janney");
	Actor f("Jamie Foxx");
	Primary3.enqueue(e);

	Actor curr3;
	Actor neighbor3;
	while (!Primary3.is_empty()){
		Primary3.dequeue(curr3);
		if (!g.is_marked(curr3)){
			g.mark_vertex(curr3);
			g.get_to_vertices(curr3, Neighbor3);
			while (!Neighbor3.is_empty()){
				Neighbor3.dequeue(neighbor3);
				g.update_predecessor(curr3, neighbor3);
				if (neighbor3 == f)
					break;
				else {
					Primary3.enqueue(neighbor3);
				}
			}
		}
	}
	if (!Neighbor3.is_empty() or curr3 == f) 
		g.report_path(cerr, e, f);
	else {
		cerr << e << " and " << f << ": No connection" << endl;
	}
}



/*
* tests run func in SixDegrees
*/
void test_run(){

    Graph<Actor> g(500);

	ifstream infile;
	infile.open("actors.txt");
	string thisActor = "";
	string prev = "*";
	int actCount = 0;
	
	Actor *vert = g.returnVertex();

	while (getline(infile, thisActor)){
		Actor j(thisActor);
		if (thisActor != "*"){
			//(j.movieList).is_empty();
			cerr << "Creating new actor: " << thisActor << endl;
			actCount++;
		}
		while(getline(infile, thisActor)){
			if (thisActor == "*")
				break;
			cerr << thisActor << endl;
			j.insert(thisActor);
		}
		g.add_vertex(j);
		// making sure vertices added properly
		vert[actCount].printMovieList();
	}
	for (int i = 0; i < g.num_Vertices(); i++){
		for (int j = 0; j < g.num_Vertices(); j++){
			g.add_edge(vert[i], vert[j], 
				vert[i].connect(vert[j]));
		}
	}
	infile.close();

	ifstream in;
	in.open("test_input.txt");

    string actorOne, actorTwo;
    cerr << "Enter two actor names separated by" <<
    " a new line.\nPress ctrl-D to quit" << endl;
    while (getline(in, actorOne)){
        Actor actOne(actorOne);
        if (!g.is_vertex(actOne)){
        	cerr << "Actor 2 DNE" << endl;
            cerr << "Sorry, " << actOne <<
            " is not in the list\n";
            cerr << "\n";
        }
        else{
            getline(in, actorTwo);
            Actor actTwo(actorTwo);
            if (!g.is_vertex(actTwo)){
            	cerr << "Actor 2 DNE" << endl;
                bool k = false;
                while(k == false){
                    cerr << "Sorry, " << actTwo <<
                    " is not in the list\n";
                    cerr << "\n";
                    getline(in, actorTwo);
                    Actor actTwo(actorTwo);
                    k = g.is_vertex(actTwo);
                    if (k){
                        cerr << "Will run BFS" << endl;
                        break;
                    }
                }
            }
            else{
                cerr << "Will run BFS" << endl;
            }
        }
    }
}
/*****************************************************************************/
	/***Testing the Actor Class***/
/*****************************************************************************/

/*
* Function: func to test the insert func of the actor class
*/
void test_insert(){
	// makes parametrized Actor object
	Actor j("Joan Cusack");

	//should return 1
	cerr << j.insert("Grosse Pointe Blank") << endl;
	cerr << j.insert("The Perks of Being a Wallflower") << endl;
	cerr << j.insert("Say Anything") << endl;
	cerr << j.insert("Runaway Bride") << endl;
	// should return 0
	cerr << j.insert("Grosse Pointe Blank") << endl;
	// make sure it prints out all movies
	j.printMovieList();
}

/*
* Function: tests the inMovie function of Actor class
*/
void test_inMovie(){
	Actor e("Emma Watson");
	e.insert("The Perks of Being a Wallflower");
	e.insert("Harry Potter");
	e.insert("Colonia");

	Actor j("Joan Cusack");
	j.insert("Grosse Pointe Blank");
	j.insert("The Perks of Being a Wallflower");
	j.insert("Say Anything");
	j.insert("Runaway Bride");

	// prints 1
	cerr << e.inMovie("The Perks of Being a Wallflower") << endl;
	// prints 0
	cerr << e.inMovie("Runaway Bride") << endl;
	//prints 0
	cerr << j.inMovie("Harry Potter") << endl;
	//prints 1
	cerr << j.inMovie("Say Anything") << endl;
}

/*
* Function: tests the connect function of the Actor class
*/
void test_connect(){
	Actor e("Emma Watson");
	e.insert("The Perks of Being a Wallflower");
	e.insert("Harry Potter");
	e.insert("Colonia");

	Actor j("Joan Cusack");
	j.insert("Grosse Pointe Blank");
	j.insert("The Perks of Being a Wallflower");
	j.insert("Say Anything");
	j.insert("Runaway Bride");

	Actor m("Meryl Streep");
	m.insert("Julie and Julia");

	Actor v("John Malkovich");
	v.insert("Red");
	v.insert("Harry Potter");
	v.insert("Colonia");

	// prints Perks of Being a Wallflower
	cerr << e.connect(j) << endl;
	// prints empty string
	cerr << e.connect(m) << endl;
	// prints either Colonia or Harry Potter
	cerr << v.connect(e) << endl;
}

/*
* Function: tests the overload operator
*/
void test_equal_overload(){
	Actor d("Daniel Radcliffe");
	Actor v("John Malkovich");
	Actor j("Daniel Radcliffe");
	Actor h("daniel radcliffe");

	// prints 0
	cerr << (d == v) << endl;
	// prints 1
	cerr << (d == j) << endl;
	// prints 0
	cerr << (j == h) << endl;
	// prints 1
	cerr << (d == d) << endl;
}

/*
* Function: tests the operator !=
*/
void test_not_equal_overload(){
	Actor k("Kate Blanchet");
	/*
	* insert done here to check for
	* memory leaks in the movieList
	* once the destructor is run
	*/
	k.insert("some movie");
	Actor i("Don Cheadle");
	Actor y("Don Cheadle");
	y.insert("some movie");
	Actor u("don cheadle");

	//prints 1
	cerr << (k != i) << endl;
	//prints 0
	cerr << (i != y) << endl;
	//prints 1
	cerr << (y != u) << endl;
}

/*
* Function: tests the print overload
*/
void test_print_overload(){
	Actor k("Kate Blanchet");
	Actor i("Don Cheadle");
	Actor y("Don Cheadle");
	Actor u("don cheadle");

	// prints "Kate Blanchet"
	cerr << k << endl;
	// prints "Don Cheadle"
	cerr << i << endl;
	// prints "Don Cheadle"
	cerr << y << endl;
	// prints "don cheadle"
	cerr << u << endl;

}



/*****************************************************************************/
	/***Testing the Graph Class***/
/*****************************************************************************/

/*
* Function: checks is_vertex function
*/
void test_is_vertex(){
	Graph<Actor> g(500);

	ifstream infile;
	infile.open("actors.txt");
	string thisActor = "";
	string prev = "*";
	Actor j;
	int actCount = 0;
	while(getline(infile, thisActor, '\n')){
		//cerr << thisActor << endl;
		if (prev == "*"){
			Actor j(thisActor);
			g.add_vertex(thisActor);
			actCount++;
		}
		else {
			j.insert(thisActor);
		}
		prev = thisActor;
	}

	// cerr << g.curr_vertex << endl;
	Actor k("Edward Norton");
	Actor e("Emma Watson");
	Actor a("George Clooney");
	Actor f("George clooney");

	// prints 1
	cerr << g.is_vertex(k) << endl;
	// prints 1
	cerr << g.is_vertex(e) << endl;
	// prints 1
	cerr << g.is_vertex(a) << endl;
	//prints 0
	cerr << g.is_vertex(f) << endl;
}

/*
* Function to add edge
*/
void test_add_edge(){
	Graph<Actor> g(5);

	Actor e("Emma Watson");
	e.insert("Harry Potter and the Prisoner of Azkaban");
	e.insert("Beauty and the Beast");
	e.insert("The Perks of Being a Wallflower");
	g.add_vertex(e);

	Actor j("Joan Cusack");
	j.insert("The Perks of Being a Wallflower");
	j.insert("Sixteen Candles");
	g.add_vertex(j);

	Actor w("Will Smith");
	w.insert("Wild Wild West");
	w.insert("Men in Black");
	g.add_vertex(w);

	Actor s("Salma Hayek");
	s.insert("Wild Wild West");
	s.insert("The Perks of Being a Wallflower");
	s.insert("Beauty and the Beast");
	g.add_vertex(s);

	cerr << g.add_edge(e, j, e.connect(j)) << endl;
	cerr << g.add_edge(j, w, j.connect(w)) << endl;
	cerr << g.add_edge(s, e, s.connect(e)) << endl;
	g.print_matrix(cout);




}
/*
* Function to get edge 
*/
void test_get_edge(){
	Graph<Actor> g(5);

	Actor e("Emma Watson");
	e.insert("Harry Potter and the Prisoner of Azkaban");
	e.insert("Beauty and the Beast");
	e.insert("The Perks of Being a Wallflower");
	g.add_vertex(e);

	Actor j("Joan Cusack");
	j.insert("The Perks of Being a Wallflower");
	j.insert("Sixteen Candles");
	g.add_vertex(j);

	Actor w("Will Smith");
	w.insert("Wild Wild West");
	w.insert("Men in Black");
	g.add_vertex(w);

	Actor s("Salma Hayek");
	s.insert("Wild Wild West");
	s.insert("The Perks of Being a Wallflower");
	s.insert("Beauty and the Beast");
	g.add_vertex(s);

	cerr << g.add_edge(e, j, e.connect(j)) << endl;
	cerr << g.add_edge(j, w, j.connect(w)) << endl;
	cerr << g.add_edge(s, e, s.connect(e)) << endl;

	//Beauty and the Beast or Perks
	cerr << g.get_edge(e,s) << endl;
	// empty string
	cerr << g.get_edge(j,w) << endl;
	// null
	cerr << g.get_edge(e,w) << endl;
	// Perks
	cerr << g.get_edge(e,j) << endl;
}

/*
* Test get to vertices func, error
* statements put into original function also
*/
void test_get_to_vertices(){
	Graph<Actor> g(175);

	ifstream infile;
	infile.open("actors.txt");
	string thisActor = "";
	string prev = "*";
	int actCount = 0;
	
	Actor *vert = g.returnVertex();

	while (getline(infile, thisActor)){
		Actor j(thisActor);
		if (thisActor != "*"){
			//(j.movieList).is_empty();
			cerr << "Creating new actor: " << thisActor << endl;
			actCount++;
		}
		while(getline(infile, thisActor)){
			if (thisActor == "*")
				break;
			cerr << thisActor << endl;
			j.insert(thisActor);
		}
		g.add_vertex(j);
		vert[actCount].printMovieList();
	}

	for (int i = 0; i < g.num_Vertices(); i++){
        for (int j = 0; j < g.num_Vertices(); j++){
            g.add_edge(vert[i], vert[j], 
                vert[i].connect(vert[j]));
        }
    }
    /*
    * Error statements added throughout get
    * to vertices so that it would print out
    * the two vertices with a similar movie title
    * and the movie title they had in common
    */
	cerr << vert[123] << endl;
	g.print_matrix(cerr);
	Queue<Actor> Neighbor;
	Actor e("Emma Watson");
	cerr << "before get vertices" << endl;
	g.get_to_vertices(e, Neighbor);
}