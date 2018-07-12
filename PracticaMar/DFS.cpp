/**
 * @file DFS.cpp
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


#include <iterator>
#include "DFS.hpp"



DFS::DFS() {}

DFS::DFS(Graph* g) {
	this->g = g;
	this->numVertices = g->vertices.size();
	this->marks = vector<color>(numVertices);
	this->topological_order = list<Vertex>();
	this->stronglycc = vector<vector<Vertex>>();
}

DFS::~DFS() {}

void DFS::searchDfs() {
	marks = vector<color>(g->vertices.size());
	for (unsigned int i = 0; i < g->vertices.size(); i++){
		marks[i] = WHITE;
	}
	hasCycle = false;
	for (unsigned int i = 0; i < g->vertices.size(); i++){
		if (marks[i] == WHITE){
			visit(g->vertices[i].id);
		}
	}
}

void DFS::visit(Id id) {
	marks[g->index_table[id]] = GRAY;
	vector<Id> adj = g->vertices[g->index_table[id]].adjacencyList;

	for (unsigned int i = 0; i < adj.size(); i++){
		int next = g->index_table[adj[i]];
		if (marks[next] == WHITE)
			visit(g->vertices[next].id);
		else if (marks[next] == GRAY)
			hasCycle = true;
	}

	//If I insert the node at the end of a list, then I'll get the Topological Order (when the graph is acyclical).
	topological_order.push_front(g->vertices[g->index_table[id]]);
	marks[g->index_table[id]] = BLACK;
}

void DFS::specialDfs(list<Vertex> timeOrderedVector) {
	for (unsigned int i = 0; i < g->vertices.size(); i++){
		marks[i] = WHITE;
	}
	//
	//Pag 469 del cormen dice que tiene que recorrerse en
	//orden decreciente en tiempo de finalización...
	//
	list<Vertex>::iterator it = timeOrderedVector.end();
	it--;
	for(it; it != timeOrderedVector.begin(); it--){
		if(marks[g->index_table[it->id]] == WHITE){
			vector<Vertex> set = vector<Vertex>();
			set.push_back(*it);
			specialVisit(it->id, set);
			stronglycc.push_back(set);
		}
	}
}

void DFS::specialVisit(Id id, vector<Vertex>& set) {
	marks[g->index_table[id]] = GRAY;
	vector<Id> adj = g->vertices[g->index_table[id]].adjacencyList;

	for (unsigned int i = 0; i < adj.size(); i++){
		int next = g->index_table[adj[i]];
		if (marks[next] == WHITE){
			set.push_back(g->vertices[next]);
			specialVisit(g->vertices[next].id, set);
		}
	}
	marks[g->index_table[id]] = BLACK;
}

vector<vector<Vertex>> DFS::getScc() {
	return stronglycc;
}

bool DFS::isCyclic() {
	return hasCycle;
}

list<Vertex> DFS::getTopo() {
	return topological_order;
}