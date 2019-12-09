/*
*	Análise e Projeto de Algoritmos - Problema da Cobertura de Vértices
*	Allan Carlos Amaral Ribeiro (201465551C), Jefferson Amará (201765125A), Luis Augusto T. Guimarães (201365165AC)
*/

#ifndef GRAPHVERTEX_H
#define GRAPHVERTEX_H

#include <unordered_map>
#include "GraphEdge.h"

using namespace std;

/*
*	Classe que representa um vértice do grafo
*/
class GraphVertex
{
private:
	// Id do vértice
	int id;

	// Guarda as arestas do vértice
	unordered_map<int, GraphEdge*> edgeList;
public:
	GraphVertex(int idVertice);

	// Retorna o Id do vértice
	int getId();

	// Adiciona uma aresta ao vértice
	void addEdge(GraphEdge *edge);

	// Retorna a aresta a partir do Id
	GraphEdge* getEdge(int idEdge);

	// Retorna a lista de arestas do vértice
	unordered_map<int, GraphEdge*> getEdgeList();

	// Remove a aresta do vértice
	void removeEdge(int idEdge);

	// Retorna o grau do vértice
	int getDegree();
};

#endif