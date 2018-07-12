/**
 * @file Utilities.hpp
 *
 *
 * The representation of a Vertex in a Graph. A Vertex is consider to be a struct of an id and a list that
 * represent the directed edges that goes from this vertex to another.
 * 
 * Proyect of the subject "Métodos Algorítmos en Resolución de Problemas"
 * Facultad de Informática
 * Universidad Complutense
 *
 * @author Javier Carrión García
 * 
 */


#pragma once

#include <String>
#include <vector>
using namespace std;



 /**
  * A sysnomous use to make this representation more coherent.
  */
using Id = string;

/**
 * A Vertex is consider to be a struct of an identifier and a list that
 * represent the directed edges that goes from this vertex to another.
 */
typedef struct Vertex;


typedef struct Vertex {
	Id id;
	vector<Id> adjacencyList;
};