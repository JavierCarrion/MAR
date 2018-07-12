/**
 * @file Graph.hpp
 *
 *
 * Implentation of a directed Graph. A Graph is considered to be a set of vertices plus the ability
 * to add directed edges that connect these vertices.
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
#include <list>
#include <map>
#include <time.h>
#include "Utilities.hpp"
#include "DFS.hpp"
using namespace std;



/**
 * A class to represent a Graph. A Graph is considered to be a vector of vertices plus the ability
 * to modify the edges that connect these vertices (i.e. to modify the vertices' adjacency lists) and a
 * DFS algorthm.
 *
 * The operations are:
 * -Create an empty Graph.
 *
 * -Create a Graph with a preset of vertices.
 *
 * -Add a new vertex to the Graph.
 *
 * -Add a new edge to the Graph.
 *
 * -Check if the Graph is cyclic.
 *
 * -Obtain the total number of vertices.
 *
 * -Check if exists an edge that goes from the vertex A to the vertex B
 *
 * -Obtain a Topological Sort of the Graph (only if the Graph is acyclic).
 *
 * -Generate the Transposed Graph of the main Graph.
 *
 * -Obtain the Strongly-Connected-Components of the Graph (only if the Graph is cyclic).
 *
 * -Print the Graph.
 *
 */
class Graph
{

	friend class DFS;

public:

	Graph();

	/**
	* A constructor that generates a Graph with a preset of vertices.
	* @param ids The vector with all the vertices' ids.
	*/
	Graph(vector<Id> ids);

	~Graph();

	/**
	 * Adds a new vertex with an identifier.
	 * @param id The vertex's id.
	 */
	void addVertex(Id id);

	/**
	 * Adds a directed edge that goes from vertex A to vertex B.
	 * @param A Origin vertex.
	 * @param B Destination vertex.
	 */
	void addEdge(Id A, Id B);

	/**
	 * Adds a directed edge that goes from the vertex at the position A to an other vertex in the position B
	 * @param a Position of the origin vertex.
	 * @param b Position of the destination vertex.
	 */
	void addEdge(int a, int b);

	/**
	 * Check if the Graph has a cycle.
	 * @return True if the Graph has a cycle, False otherwise.
	 */
	bool isCyclic();

	/**
	 * @return The number of vertex.
	 */
	int size();

	/**
	 * @return the number of edges.
	 */
	int edges();

	/**
	 * Check if exist a directed edge that goes from the vertex at the position A to other vertex at the position B.
	 * @param a Position of the origin vertex.
	 * @param b Position of the destination vertex.
	 * @return True if that edge exists, False otherwise.
	 */
	bool existEdge(int a, int b);

	/**
	 * @return A list with one Topological Sort.
	 */
	list<Vertex> topologicalSort();

	/**
	 * Generates the Transposed Graph of the main Graph.
	 * @return The Transposed Graph.
	 */
	Graph transpose();

	/**
	 * @param ts Variable que sirve para calcular el tiempo que se tarda en procesar las cfc.
	 * @return the Graph's Strongly-Connected-Components.
   	 */
	vector<vector<Vertex>> stronglyConnectedComponents(clock_t& ts);

	/**
	 * Print the Graph.
	 * @return A string that represents the Graph.
	 */
	string print();


private:

	/**
	 * The algorithm Depth First Search.
	 */
	DFS* dfs;

	/**
	 * All the Graph's vertices.
	 */
	vector<Vertex> vertices;

	/**
	 * A map that matches an id of a vertex with its possition in the vertices' vector.
	 */
	map<Id, int> index_table;

	/**
	 * The number of Edges of the Graph.
	 */
	int nEdges;
};