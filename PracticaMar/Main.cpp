/**
 * @file Main.cpp
 * 
 * Proyect of the subject "Métodos Algorítmos en Resolución de Problemas"
 * Facultad de Informática
 * Universidad Complutense
 *
 * Implement in Java or C++ an algorithm, which, given a directed graph,
 * detects whether it has cycles or not. If it is acyclical, it must list
 * its vertices in Topological order. If there is more than one possible,
 * it can be listed in any of them. If it is cyclical, it must list its
 * Strongly-Connected Components (each one is a set of vertices).
 * The algorithm for this second part can be seen in Chapter 22 of the Cormen (2001, second edition).
 *
 * @author Javier Carrión García
 * 
 */


#include <iostream>
#include <random>
#include <time.h>
#include <fstream>
#include "Graph.hpp"

using namespace std;



#define INIT_SIZE 300
#define INIT_EDGES 300


void store(ofstream& f, int size, clock_t t) {
	double ms = ((double)(t) / CLOCKS_PER_SEC) * 1000;

	f << size;
	f << " ";
	f << ms << endl;
}

void addEdge(Graph& g) {
	int a, b;
	int n = g.size();
	srand(time(NULL));
	do {
		a = rand() % n;
		b = rand() % n;
	} while (g.existEdge(a, b));
	g.addEdge(a, b);
}

void topoAux(Graph& g, clock_t& tp) {
	bool cyclic;
	//this time is for the Topological Sort
	tp = clock();
	cyclic = g.isCyclic();
	tp = clock() - tp;

	if (!cyclic) {
		// This method is just a "getter" the time for the Topological Sort is calculated above.
		g.topologicalSort();
	}
}

void topo(Graph& g, clock_t& tp) {
	clock_t tp1, tp2, tp3;
	ofstream topoFile("Topological Sort.dat");

	for (int i = 0; i < INIT_SIZE; i++) {
		Id id = to_string(i);
		g.addVertex(id);
	}
	for (int i = 0; i < INIT_EDGES; i++)
		addEdge(g);

	int maxSize;
	cout << "EJECUCION DEL ORDEN TOPOLOGICO" << endl << endl;
	cout << "Inroduce el numero maximo de nodos del grafo (se aconseja 7000): ";
	cin >> maxSize;

	for (int i = 600; i < maxSize; i += 300) {
		for (int k = 0; k < 300; k++) {
			Id id = to_string((i - 300) + k);
			g.addVertex(id);
			srand(time(NULL));
			int r = rand() % 7;
			//add 0, 1,..., 6 edges
			for (int j = 0; j <= r; j++) {
				addEdge(g);
			}
		}
		cout << i << endl;
		//cout << g.print() << endl;
		topoAux(g, tp1);
		topoAux(g, tp2);
		topoAux(g, tp3);
		tp = (tp1 + tp2 + tp3) / 3;
		store(topoFile, i + g.edges(), tp);
	}
	topoFile.close();
}

void strongAux(Graph& g, clock_t& ts) {
	bool cyclic;
	cyclic = g.isCyclic();

	if (cyclic) {
		g.stronglyConnectedComponents(ts);
	}
}

void strong(Graph& g, clock_t& ts) {
	clock_t ts1, ts2, ts3;
	ofstream compoFile("Strongly Connected Components.dat");

	for (int i = 0; i < INIT_SIZE; i++) {
		Id id = to_string(i);
		g.addVertex(id);
	}
	for (int i = 0; i < INIT_EDGES; i++)
		addEdge(g);

	int maxSize;
	cout << "EJECUCION DE LAS COMPONENTES FURETEMENTE CONEXAS" << endl << endl;
	cout << "Inroduce el numero maximo de nodos del grafo (se aconseja 7000): ";
	cin >> maxSize;

	for (int i = 600; i < maxSize; i += 300) {
		for (int k = 0; k < 300; k++) {
			Id id = to_string((i - 300) + k);
			g.addVertex(id);
			srand(time(NULL));
			int r = rand() % 7;
			//add 0, 1,..., 6 edges
			for (int j = 0; j <= r; j++) {
				addEdge(g);
			}
		}
		cout << i << endl;
		//cout << g.print() << endl;
		strongAux(g, ts1);
		strongAux(g, ts2);
		strongAux(g, ts3);
		ts = (ts1 + ts2 + ts3) / 3;
		store(compoFile, i + g.edges(), ts);
	}
	compoFile.close();
}


int main() {
	Graph gt, gs;
	clock_t tp, ts;

	topo(gt, tp);
	strong(gs, tp);

	////
	// GNU-PLOT
	////

	ofstream TOPO_PLT("Topological Sort.plt");
	ofstream COMPO_PLT("Strongly Connected Componnents.plt");

	TOPO_PLT << "set style line 1 lc rgb '#0b9e9' lt 1 lw 2 pt 7 ps 1.5" << endl;
	TOPO_PLT << "plot 'Topological Sort.dat' with linespoints ls 1";

	COMPO_PLT << "set style line 1 lc rgb '#0b9e9' lt 1 lw 2 pt 7 ps 1.5" << endl;
	COMPO_PLT << "plot 'Strongly Connected Components.dat' with linespoints ls 1";

	TOPO_PLT.close();
	COMPO_PLT.close();
	system("PAUSE");
	return 0;
}