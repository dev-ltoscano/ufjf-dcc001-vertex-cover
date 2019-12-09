/*
*	An�lise e Projeto de Algoritmos - Problema da Cobertura de V�rtices
*	Allan Carlos Amaral Ribeiro (201465551C), Jefferson Amar� (201765125A), Luis Augusto T. Guimar�es (201365165AC)
*/

#ifndef MERGESORT_H
#define MERGESORT_H

#include <vector>
#include "GraphVertex.h"

/*
*	Classe que implementa o algoritmo MergeSort para ordena��o dos v�rtices
*/
class MergeSort
{
private:
	// Opera��o de merge do algoritmo MergeSort para unir de forma ordenada duas metades
	static void merge(vector<GraphVertex*> *vertexList, int start, int end, int middle);
public:
	// Ordena o vetor em ordem decrescente pelo grau dos v�rtices usando o algoritmo MergeSort
	static void sort(vector<GraphVertex*> *vertexList, int start, int end);
};

#endif