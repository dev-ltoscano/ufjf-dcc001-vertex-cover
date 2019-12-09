/*
*	An�lise e Projeto de Algoritmos - Problema da Cobertura de V�rtices
*	Allan Carlos Amaral Ribeiro (201465551C), Jefferson Amar� (201765125A), Luis Augusto T. Guimar�es (201365165AC)
*/

#ifndef GRAPHVERTEX_H
#define GRAPHVERTEX_H

#include <unordered_map>
#include "GraphEdge.h"

using namespace std;

/*
*	Classe que representa um v�rtice do grafo
*/
class GraphVertex
{
private:
	// Id do v�rtice
	int id;

	// Guarda as arestas do v�rtice
	unordered_map<int, GraphEdge*> edgeList;
public:
	GraphVertex(int idVertice);

	// Retorna o Id do v�rtice
	int getId();

	// Adiciona uma aresta ao v�rtice
	void addEdge(GraphEdge *edge);

	// Retorna a aresta a partir do Id
	GraphEdge* getEdge(int idEdge);

	// Retorna a lista de arestas do v�rtice
	unordered_map<int, GraphEdge*> getEdgeList();

	// Remove a aresta do v�rtice
	void removeEdge(int idEdge);

	// Retorna o grau do v�rtice
	int getDegree();
};

#endif