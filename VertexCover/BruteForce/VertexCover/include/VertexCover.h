/*
*	An�lise e Projeto de Algoritmos - Problema da Cobertura de V�rtices
*	Allan Carlos Amaral Ribeiro (201465551C), Jefferson Amar� (201765125A), Luis Augusto T. Guimar�es (201365165AC)
*/

#ifndef VERTEXCOVER_H
#define VERTEXCOVER_H

#include <iostream>
#include <algorithm>
#include <vector>

#include "Graph.h"
#include "MergeSort.h"

using namespace std;

/*
*	Classe que implementa algoritmos para resolu��o do problema de cobertura de v�rtices
*/
class VertexCover
{
public:
	// Verifica se � uma solu��o para o problema de cobertura de v�rtices
	static bool isVertexCover(vector<int> cover, Graph *graph);

	// Gera uma solu��o para o problema usando uma estrat�gia gulosa
	static vector<int> greedySolution(Graph *graph);

	// Gera uma solu��o para o problema usando estrat�gia incremental
	static vector<int> incrementalSolution(unordered_map<int, GraphEdge*> edgeList, int k);

	// Gera uma solu��o para o problema usando for�a bruta
	static vector<int> bruteForceSolution(Graph *graph);
};

#endif