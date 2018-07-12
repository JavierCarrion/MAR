/**
* @file DFS.hpp
*
*
* Implementation of Deph-First-Search algorithm. This implementation is based of the one
* seeing in "Introduction to Algorithms, 2nd ed., (T. H. Cormen et al 2001)".
*
* Proyect of the subject "Métodos Algorítmos en Resolución de Problemas"
* Facultad de Informática
* Universidad Complutense
*
* @author Javier Carrión García
*
*/


#pragma once

#include <vector>
#include "Graph.hpp"

using namespace std;



/**
* A class that implements the Deph-First-Seach algorithm. This algorithm will be used to generate the
* Topological Order of its vertices if the Graph is acyclical, and the Strongly-Connected-Components if
* the Graph has a cycle.
*
* The operations are:
*
* -Initialize the class with a given Graph.
*
* -Perform the main algrithm Depth-First-Search.
*
* -Check if the Graph is cyclical.
*
* -Obtain the Topological Order of the Garph.
*
* -Obtain the Strongly-Connected-Components of the Graph.
*
*/
class DFS
{

	friend class Graph;

public:

	DFS();

	/**
	 * A constructor that initialize the algorithm.
	 * @param g The graph upon which the algorithm is applied.
	 */
	DFS(Graph* g);

	~DFS();

	/**
	 * The main Depth First Search Algorithm.
	 */
	void searchDfs();

	/**
	 * Just returns a value that says if the Graph is cyclic or not.
	 * @return True if the Graph has a Cycle. False otherwise.
	 */
	bool isCyclic();

	/**
	 * Returns the topological order of the Graph.
	 * @return A list with the Graph's vertices in Topological order.
	 */
	list<Vertex> getTopo();

	/**
	 * Returns the Strongly-Connected Components.
	 * @return A vector of vectors with the Strongly-Connected-Components of the Graph.
	 */
	vector<vector<Vertex>> getScc();

private:

	/**
	 * A method used by searchDfs
	 * @param id The vertex' identification upon which the seacrh is applied.
	 */
	void visit(Id id);


	////
	//METHODS USED ONLY BY THE TRANSPOSE OF A GRAPH
	////

	/**
	 * A special DFS that calculates the Strongly-Connected-Components
	 * @param timeOrderedVector The vertices upon which this search are applied.
	 */
	void specialDfs(list<Vertex> timeOrderedVector);

	/**
	 * A method used only by specialDfs
	 * @param id The vertex upon which the search is applied.
	 * @param set One Strongly-Connected-Component.
	 */
	void specialVisit(Id id, vector<Vertex>& set);



	/**
	 * The Graph.
	 */
	Graph* g;

	/**
	 * The number of vertex.
	 */
	int numVertices;

	/**
	 * An enum used by serach and specialDfs.
	 */
	typedef enum color { WHITE, BLACK, GRAY };

	/**
	 * Represents the color of all the vertex(White-> hasn't been visited, Gray-> it's being visited, Black-> has been visited).
	 */
	vector<color> marks;

	/**
	 * The Topological Order of the Graph(it could be just a list ordered by finished times if the Graph has a cycle).
	 */
	list<Vertex> topological_order;

	/**
	 * Says if the Graph is Cyclic or not.
	 */
	bool hasCycle;

	/**
	 * The Strongly-Connected-Components of the Graph.
	 */
	vector<vector<Vertex>> stronglycc;
};