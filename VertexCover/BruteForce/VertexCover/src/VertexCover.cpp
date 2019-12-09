/*
*	Análise e Projeto de Algoritmos - Problema da Cobertura de Vértices
*	Allan Carlos Amaral Ribeiro (201465551C), Jefferson Amará (201765125A), Luis Augusto T. Guimarães (201365165AC)
*/

#include "VertexCover.h"

bool VertexCover::isVertexCover(vector<int> cover, Graph *graph)
{
	// Obtém a lista de arestas do grafo
	unordered_map<int, GraphEdge*> graphEdgeList = graph->getEdgeList();

	GraphVertex *tmpVertex;

	// Repete para cada vértice da cobertura
	for (auto it = cover.begin(); it != cover.end(); it++)
	{
		// Obtém o vértice do grafo a partir do Id do vértice
		tmpVertex = graph->getVertex((*it));

		// Obtém a lista de arestas do vértice
		unordered_map<int, GraphEdge*> vertexEdgeList = tmpVertex->getEdgeList();

		// Repete para cada aresta do vértice
		for (auto it2 = vertexEdgeList.begin(); it2 != vertexEdgeList.end(); it2++)
		{
			// Remove a aresta da lista de arestas do grafo
			graphEdgeList.erase(it2->second->getId());

			// Verifica se o grafo não é orientado
			if (!graph->isOriented())
			{
				// Remove a aresta oposta da lista de arestas do grafo
				graphEdgeList.erase((-1 * it2->second->getId()));
			}
		}
	}

	// Verifica se todas as arestas do grafo foram cobertas pela solução
	return (graphEdgeList.size() == 0);
}

vector<int> VertexCover::greedySolution(Graph *graph)
{
	// Obtém a lista de vértices do grafo
	unordered_map<int, GraphVertex*> vertexMapList = graph->getVertexList();

	vector<GraphVertex*> vertexList;

	// Converte a estrutura de map para vector de vértices
	for (auto it = vertexMapList.begin(); it != vertexMapList.end(); it++)
	{
		vertexList.push_back(it->second);
	}

	// Ordena por ordem descrescente a lista de vértices pelo grau dos vértices
	MergeSort::sort(&vertexList, 0, (static_cast<int>(vertexList.size()) - 1));

	// Solução para o problema de cobertura de vértices
	vector<int> cover;

	// Repete até que uma cobertura seja encontrada
	do
	{
		// Adiciona na solução o vértice com maior grau (Primeiro vértice da lista)
		cover.push_back(vertexList.at(0)->getId());

		// Remove da lista de vértices o primeiro vértice
		vertexList.erase(vertexList.begin());

		cout << "Testing...K=" << cover.size() << endl;

		// Testa se é uma solução para o problema de cobertura de vértices
		if (isVertexCover(cover, graph))
		{
			// Retorna a solução
			return cover;
		}
	} 
	while (true);
}

vector<int> VertexCover::incrementalSolution(unordered_map<int, GraphEdge*> edgeList, int k)
{
	// Solução para o problema de cobertura de vértices
	vector<int> cover;

	// Verifica se não há mais arestas no grafo ou se K == 0
	if ((edgeList.size() == 0) || (k == 0))
	{
		return cover;
	}

	// Obtém a primeira aresta do grafo (Escolha arbitrária)
	GraphEdge *edge = edgeList.begin()->second;

	vector<GraphEdge*> tmpEdgeList;

	// Remove o vértice da cópia do grafo
	for (auto it = edgeList.begin(); it != edgeList.end(); it++)
	{
		if ((it->second->getIdFirstVertex() == edge->getIdFirstVertex())
			|| (it->second->getIdSecondVertex() == edge->getIdFirstVertex()))
		{
			tmpEdgeList.push_back(it->second);
		}
	}

	for (auto it = tmpEdgeList.begin(); it != tmpEdgeList.end(); it++)
	{
		edgeList.erase((*it)->getId());
	}

	// Resolve o problema para o grafo menor
	vector<int> c1 = incrementalSolution(edgeList, (k - 1));

	// Adiciona a solução do problema para o grafo menor para a atual
	for (auto it = c1.begin(); it != c1.end(); it++)
	{
		cover.push_back((*it));
	}

	// Adiciona o nó removido na solução
	cover.push_back(edge->getIdFirstVertex());

	// Retorna a solução
	return cover;
}

vector<int> VertexCover::bruteForceSolution(Graph *graph)
{
	// Solução para o problema de cobertura de vértices
	vector<int> cover;

	// Tamanho das combinações geradas como solução para o problema
	int k = 1;
	int n = graph->vertexCount();

	// Repete até que uma cobertura seja encontrada
	do
	{
		cout << "Testing...K=" << k << endl;

		// Fonte: http://rosettacode.org/wiki/Combinations#C.2B.2B
		// Gera todas as combinações de tamanho K como solução para o problema
		string bitmask(k, 1);
		bitmask.resize(n, 0);

		// Repete até que não tenha mais combinações
		do
		{
			for (int i = 0; i < n; i++)
			{
				if (bitmask[i])
				{
					cover.push_back(i + 1);
				}
			}

			// Testa se é uma solução para o problema de cobertura de vértices
			if (isVertexCover(cover, graph))
			{
				// Retorna a solução
				return cover;
			}

			// Limpa a solução para uma nova combinação
			cover.clear();
		} 
		while (prev_permutation(bitmask.begin(), bitmask.end()));
		// Fim da geração de combinações

		k++;
	}
	while (true);
}