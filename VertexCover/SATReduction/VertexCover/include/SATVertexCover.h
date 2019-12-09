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

using namespace std;

class SATVertexCover
{
private:
	static bool isVertexCover(vector<int> cover, Graph *graph);
	
	// Gera o arquio que será utilizado pelo resolvedor SAT
	// θ(k*(|V|²+|E|)) - Nao Otimizado
	// θ(k*(|V|+|E|))  - Otimizado
	static void generateSATFile(Graph& graph, uint32_t k, bool optimizedAtMostOne);

	// Chamada ao resolverdor
	static void callMinisat();

	// Volta da redução
	// θ(|V|)
	static bool checkSATSolution(std::vector<int>& cover, uint32_t k, int vertexCount);

	// Funcoes de suporte, usadas para gerar as clausulas do arquivo SAT
	// No maximo um id da lista deve ser verdadeiro - versão original
	// θ(n²)
	static void atMostOne(std::vector<int64_t>& ids, uint32_t& clausules, std::stringstream& ss);
	
	// No maximo um id da lista deve ser verdadeiro - versão otimizada
	// θ(n)
	static void atMostOneOpt(std::vector<int64_t>& ids, uint32_t& clausules, uint64_t& variables, std::stringstream& ss);
	
	// Pelo menos um dos ids da lista deve ser verdadeiro
	// θ(n)
	static void atLeastOne(std::vector<int64_t>& ids, uint32_t& clausules, std::stringstream& ss);
public:
	static vector<int> solve(Graph *graph);
};

#endif