/*
*	Análise e Projeto de Algoritmos - Problema da Cobertura de Vértices
*	Allan Carlos Amaral Ribeiro (201465551C), Jefferson Amará (201765125A), Luis Augusto T. Guimarães (201365165AC)
*/

#ifndef MERGESORT_H
#define MERGESORT_H

#include <vector>
#include "GraphVertex.h"

/*
*	Classe que implementa o algoritmo MergeSort para ordenação dos vértices
*/
class MergeSort
{
private:
	// Operação de merge do algoritmo MergeSort para unir de forma ordenada duas metades
	static void merge(vector<GraphVertex*> *vertexList, int start, int end, int middle);
public:
	// Ordena o vetor em ordem decrescente pelo grau dos vértices usando o algoritmo MergeSort
	static void sort(vector<GraphVertex*> *vertexList, int start, int end);
};

#endif