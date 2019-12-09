/*
*	Análise e Projeto de Algoritmos - Problema da Cobertura de Vértices
*	Allan Carlos Amaral Ribeiro (201465551C), Jefferson Amará (201765125A), Luis Augusto T. Guimarães (201365165AC)
*/

#include "GraphEdge.h"

GraphEdge::GraphEdge(int idEdge, int idFirstVertex, int idSecondVertex, double weight)
{
	this->id = idEdge;
	this->idFirstVertex = idFirstVertex;
	this->idSecondVertex = idSecondVertex;
	this->weight = weight;
}

int GraphEdge::getId()
{
	// Retorna o Id da aresta
	return id;
}

int GraphEdge::getIdFirstVertex()
{
	// Retorna o Id do primeiro vértice da aresta (u, v)
	return idFirstVertex;
}

int GraphEdge::getIdSecondVertex()
{
	// Retorna o Id do segundo vértice da aresta (u, v)
	return idSecondVertex;
}

double GraphEdge::getWeight()
{
	// Retorna o peso da aresta
	return weight;
}