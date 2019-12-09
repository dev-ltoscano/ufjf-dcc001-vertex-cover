/*
*	An�lise e Projeto de Algoritmos - Problema da Cobertura de V�rtices
*	Allan Carlos Amaral Ribeiro (201465551C), Jefferson Amar� (201765125A), Luis Augusto T. Guimar�es (201365165AC)
*/

#include "GraphVertex.h"

GraphVertex::GraphVertex(int idVertex)
{
	this->id = idVertex;
}

int GraphVertex::getId()
{
	// Retorna o Id do v�rtice
	return id;
}

void GraphVertex::addEdge(GraphEdge *edge)
{
	// Adiciona a aresta na lista de arestas do v�rtice
	edgeList.insert(pair<int, GraphEdge*>(edge->getId(), edge));
}

GraphEdge* GraphVertex::getEdge(int idEdge)
{
	// Retorna a aresta a partir de 'idEdge'
	return edgeList.at(idEdge);
}

unordered_map<int, GraphEdge*> GraphVertex::getEdgeList()
{
	// Retorna a lista de arestas do v�rtice
	return edgeList;
}

void GraphVertex::removeEdge(int idEdge)
{
	// Remove a aresta do v�rtice
	edgeList.erase(idEdge);
}

int GraphVertex::getDegree()
{
	// Retorna o grau do v�rtice
	return static_cast<int>(edgeList.size());
}