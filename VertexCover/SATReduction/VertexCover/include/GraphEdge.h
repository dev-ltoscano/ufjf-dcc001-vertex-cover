/*
*	An�lise e Projeto de Algoritmos - Problema da Cobertura de V�rtices
*	Allan Carlos Amaral Ribeiro (201465551C), Jefferson Amar� (201765125A), Luis Augusto T. Guimar�es (201365165AC)
*/

#ifndef GRAPHEDGE_H
#define GRAPHEDGE_H

/*
*	Classe que representa uma aresta do grafo
*/
class GraphEdge
{
private:
	// Id da aresta
	int id;

	// Id do primeiro v�rtice da aresta (u, v)
	int idFirstVertex;

	// Id do segundo v�rtice da aresta (u, v)
	int idSecondVertex;

	// Peso da aresta
	double weight;
public:
	GraphEdge(int idEdge, int idFirstVertex, int idSecondVertex, double weight);

	// Retorna o Id da aresta
	int getId();
	
	// Retorna o Id do primeiro v�rtice da aresta (u, v)
	int getIdFirstVertex();

	// Retorna o Id do segundo v�rtice da aresta (u, v)
	int getIdSecondVertex();

	// Retorna o peso da aresta
	double getWeight();
};

#endif