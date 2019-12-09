/*
*	An�lise e Projeto de Algoritmos - Problema da Cobertura de V�rtices
*	Allan Carlos Amaral Ribeiro (201465551C), Jefferson Amar� (201765125A), Luis Augusto T. Guimar�es (201365165AC)
*/

#include "VertexCover.h"

bool VertexCover::isVertexCover(vector<int> cover, Graph *graph)
{
	// Obt�m a lista de arestas do grafo
	unordered_map<int, GraphEdge*> graphEdgeList = graph->getEdgeList();

	GraphVertex *tmpVertex;

	// Repete para cada v�rtice da cobertura
	for (auto it = cover.begin(); it != cover.end(); it++)
	{
		// Obt�m o v�rtice do grafo a partir do Id do v�rtice
		tmpVertex = graph->getVertex((*it));

		// Obt�m a lista de arestas do v�rtice
		unordered_map<int, GraphEdge*> vertexEdgeList = tmpVertex->getEdgeList();

		// Repete para cada aresta do v�rtice
		for (auto it2 = vertexEdgeList.begin(); it2 != vertexEdgeList.end(); it2++)
		{
			// Remove a aresta da lista de arestas do grafo
			graphEdgeList.erase(it2->second->getId());

			// Verifica se o grafo n�o � orientado
			if (!graph->isOriented())
			{
				// Remove a aresta oposta da lista de arestas do grafo
				graphEdgeList.erase((-1 * it2->second->getId()));
			}
		}
	}

	// Verifica se todas as arestas do grafo foram cobertas pela solu��o
	return (graphEdgeList.size() == 0);
}

vector<int> VertexCover::greedySolution(Graph *graph)
{
	// Obt�m a lista de v�rtices do grafo
	unordered_map<int, GraphVertex*> vertexMapList = graph->getVertexList();

	vector<GraphVertex*> vertexList;

	// Converte a estrutura de map para vector de v�rtices
	for (auto it = vertexMapList.begin(); it != vertexMapList.end(); it++)
	{
		vertexList.push_back(it->second);
	}

	// Ordena por ordem descrescente a lista de v�rtices pelo grau dos v�rtices
	MergeSort::sort(&vertexList, 0, (static_cast<int>(vertexList.size()) - 1));

	// Solu��o para o problema de cobertura de v�rtices
	vector<int> cover;

	// Repete at� que uma cobertura seja encontrada
	do
	{
		// Adiciona na solu��o o v�rtice com maior grau (Primeiro v�rtice da lista)
		cover.push_back(vertexList.at(0)->getId());

		// Remove da lista de v�rtices o primeiro v�rtice
		vertexList.erase(vertexList.begin());

		cout << "Testing...K=" << cover.size() << endl;

		// Testa se � uma solu��o para o problema de cobertura de v�rtices
		if (isVertexCover(cover, graph))
		{
			// Retorna a solu��o
			return cover;
		}
	} 
	while (true);
}

vector<int> VertexCover::incrementalSolution(unordered_map<int, GraphEdge*> edgeList, int k)
{
	// Solu��o para o problema de cobertura de v�rtices
	vector<int> cover;

	// Verifica se n�o h� mais arestas no grafo ou se K == 0
	if ((edgeList.size() == 0) || (k == 0))
	{
		return cover;
	}

	// Obt�m a primeira aresta do grafo (Escolha arbitr�ria)
	GraphEdge *edge = edgeList.begin()->second;

	vector<GraphEdge*> tmpEdgeList;

	// Remove o v�rtice da c�pia do grafo
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

	// Adiciona a solu��o do problema para o grafo menor para a atual
	for (auto it = c1.begin(); it != c1.end(); it++)
	{
		cover.push_back((*it));
	}

	// Adiciona o n� removido na solu��o
	cover.push_back(edge->getIdFirstVertex());

	// Retorna a solu��o
	return cover;
}

vector<int> VertexCover::bruteForceSolution(Graph *graph)
{
	// Solu��o para o problema de cobertura de v�rtices
	vector<int> cover;

	// Tamanho das combina��es geradas como solu��o para o problema
	int k = 1;
	int n = graph->vertexCount();

	// Repete at� que uma cobertura seja encontrada
	do
	{
		cout << "Testing...K=" << k << endl;

		// Fonte: http://rosettacode.org/wiki/Combinations#C.2B.2B
		// Gera todas as combina��es de tamanho K como solu��o para o problema
		string bitmask(k, 1);
		bitmask.resize(n, 0);

		// Repete at� que n�o tenha mais combina��es
		do
		{
			for (int i = 0; i < n; i++)
			{
				if (bitmask[i])
				{
					cover.push_back(i + 1);
				}
			}

			// Testa se � uma solu��o para o problema de cobertura de v�rtices
			if (isVertexCover(cover, graph))
			{
				// Retorna a solu��o
				return cover;
			}

			// Limpa a solu��o para uma nova combina��o
			cover.clear();
		} 
		while (prev_permutation(bitmask.begin(), bitmask.end()));
		// Fim da gera��o de combina��es

		k++;
	}
	while (true);
}