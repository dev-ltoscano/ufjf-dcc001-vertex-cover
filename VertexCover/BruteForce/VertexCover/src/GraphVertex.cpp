/*
*	Análise e Projeto de Algoritmos - Problema da Cobertura de Vértices
*	Allan Carlos Amaral Ribeiro (201465551C), Jefferson Amará (201765125A), Luis Augusto T. Guimarães (201365165AC)
*/

#include "GraphVertex.h"

GraphVertex::GraphVertex(int idVertex)
{
	this->id = idVertex;
}

int GraphVertex::getId()
{
	// Retorna o Id do vértice
	return id;
}

void GraphVertex::addEdge(GraphEdge *edge)
{
	// Adiciona a aresta na lista de arestas do vértice
	edgeList.insert(pair<int, GraphEdge*>(edge->getId(), edge));
}

GraphEdge* GraphVertex::getEdge(int idEdge)
{
	// Retorna a aresta a partir de 'idEdge'
	return edgeList.at(idEdge);
}

unordered_map<int, GraphEdge*> GraphVertex::getEdgeList()
{
	// Retorna a lista de arestas do vértice
	return edgeList;
}

void GraphVertex::removeEdge(int idEdge)
{
	// Remove a aresta do vértice
	edgeList.erase(idEdge);
}

int GraphVertex::getDegree()
{
	// Retorna o grau do vértice
	return static_cast<int>(edgeList.size());
}