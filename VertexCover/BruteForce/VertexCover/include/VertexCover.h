/*
*	Análise e Projeto de Algoritmos - Problema da Cobertura de Vértices
*	Allan Carlos Amaral Ribeiro (201465551C), Jefferson Amará (201765125A), Luis Augusto T. Guimarães (201365165AC)
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
*	Classe que implementa algoritmos para resolução do problema de cobertura de vértices
*/
class VertexCover
{
public:
	// Verifica se é uma solução para o problema de cobertura de vértices
	static bool isVertexCover(vector<int> cover, Graph *graph);

	// Gera uma solução para o problema usando uma estratégia gulosa
	static vector<int> greedySolution(Graph *graph);

	// Gera uma solução para o problema usando estratégia incremental
	static vector<int> incrementalSolution(unordered_map<int, GraphEdge*> edgeList, int k);

	// Gera uma solução para o problema usando força bruta
	static vector<int> bruteForceSolution(Graph *graph);
};

#endif