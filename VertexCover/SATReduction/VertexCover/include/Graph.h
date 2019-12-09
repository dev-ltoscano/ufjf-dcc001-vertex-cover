/*
*	An�lise e Projeto de Algoritmos - Problema da Cobertura de V�rtices
*	Allan Carlos Amaral Ribeiro (201465551C), Jefferson Amar� (201765125A), Luis Augusto T. Guimar�es (201365165AC)
*/

/*
*	An�lise e Projeto de Algoritmos - Problema da Cobertura de V�rtices
*	Allan Carlos Amaral Ribeiro (201465551C), Jefferson Amar� (201765125A), Luis Augusto T. Guimar�es (201365165AC)
*/

#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <random>

#include "GraphVertex.h"
#include "GraphEdge.h"

using namespace std;

/*
*	Classe que representa um grafo
*/
class Graph
{
private:
	// Indica se o grafo � orientado ou n�o
	bool oriented;

	// Guarda os v�rtices do grafo
	unordered_map<int, GraphVertex*> vertexList;

	// Guarda as arestas do grafo
	unordered_map<int, GraphEdge*> edgeList;
public:
	Graph(bool oriented);
	Graph(Graph *graph);
	Graph(bool oriented, int vertexCount, double edgeProb);
	~Graph();

	// Carrega um grafo a partir de um arquivo
	void load(string filename);
	void save(string filename);
	
	// Imprime os v�rtices e arestas do grafo no console
	void print();

	// Verifica se o grafo � orientado ou n�o
	bool isOriented();

	// Adiciona um v�rtice ao grafo
	void addVertex(GraphVertex *vertex);

	// Retorna o v�rtice a partir do Id
	GraphVertex* getVertex(int idVertex);

	// Retorna a lista de v�rtices do grafo
	unordered_map<int, GraphVertex*> getVertexList();

	// Remove um v�rtice do grafo
	void removeVertex(int idVertex);

	// Retorna a quantidade de v�rtices do grafo
	int vertexCount();

	// Adiciona uma aresta ao grafo
	void addEdge(GraphEdge *edge);

	// Retorna a aresta a partir do Id
	GraphEdge* getEdge(int idEdge);

	// Retorna a lista de arestas do grafo
	unordered_map<int, GraphEdge*> getEdgeList();

	// Remove a aresta do grafo
	void removeEdge(int idEdge);

	// Retorna a quantidade de arestas do grafo
	int edgeCount();
};

#endif