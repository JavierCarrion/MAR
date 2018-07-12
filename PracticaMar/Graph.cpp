/**
 * @file Graph.cpp
 *
 *
 * Implentation of a directed Graph. A Graph is considered to be a set of vertices plus the ability
 * to modify the edges that connect these vertices.
 * 
 * Proyect of the subject "Métodos Algorítmos en Resolución de Problemas"
 * Facultad de Informática
 * Universidad Complutense
 *
 * @author Javier Carrión García
 * 
 */


#include "Graph.hpp"



Graph::Graph() {
	vertices = vector<Vertex>();
	this->dfs = new DFS(this);
	nEdges = 0;
}

Graph::Graph(vector<Id> ids) {
	for (unsigned int i = 0; i < ids.size(); i++) {
		addVertex(ids[i]);
	}
	this->dfs = new DFS(this);
}

Graph::~Graph() {}

void Graph::addVertex(Id id) {
	Vertex v = { id };
	vertices.push_back(v);
	index_table.insert(pair<string, int>(id, vertices.size() - 1));
}

void Graph::addEdge(Id A, Id B) {
	int a = index_table.at(A);
	int b = index_table.at(B);
	Id e = vertices[b].id;
	vertices[a].adjacencyList.push_back(e);
	nEdges++;
}

void Graph::addEdge(int a, int b) {
	Id e = vertices[b].id;
	vertices[a].adjacencyList.push_back(e);
	nEdges++;
}

bool Graph::existEdge(int a, int b) {
	vector<Id>::const_iterator it;
	for (it = vertices[a].adjacencyList.cbegin(); it != vertices[a].adjacencyList.cend(); it++)
		if (it->data() == vertices[b].id)
			return true;
	return false;
}

bool Graph::isCyclic() {
	dfs->searchDfs();
	return dfs->isCyclic();
}

int Graph::size() {
	return vertices.size();
}

int Graph::edges() {
	return nEdges;
}

list<Vertex> Graph::topologicalSort() {
	//you can't call this method before checking if the Graph is cyclic
	if(dfs->isCyclic())
		return list<Vertex>();
	return dfs->getTopo();
}

Graph Graph::transpose() {
	Graph tr = Graph();
	tr.vertices = vector<Vertex>();

	for (unsigned int i = 0; i < this->vertices.size(); i++){
		tr.addVertex(this->vertices[i].id);
	}

	vector<Id>::iterator it;
	for(unsigned int i = 0; i < this->vertices.size(); i++){
		Vertex v = vertices[i];
		for(it = v.adjacencyList.begin(); it != v.adjacencyList.end(); it++){
			tr.addEdge(it->data(), v.id);
		}
	}
	return tr;
}

vector<vector<Vertex>> Graph::stronglyConnectedComponents(clock_t& ts) {
	list<Vertex> topo = list<Vertex>();
	topo = this->dfs->getTopo();

	Graph tr = this->transpose();
	tr.dfs = new DFS(&tr);
	ts = clock();
	tr.dfs->specialDfs(topo);
	ts = clock() - ts;
	return tr.dfs->getScc();
}

string Graph::print() {
	string r;
	for (unsigned int i = 0; i < vertices.size(); i++) {
		r += vertices[i].id + " --> ";
		for (unsigned int j = 0; j < vertices[i].adjacencyList.size(); j++)
			r += vertices[i].adjacencyList[j] + " ";
		r += "\n";
	}
	return r;
}