/*
*	Análise e Projeto de Algoritmos - Problema da Cobertura de Vértices
*	Allan Carlos Amaral Ribeiro (201465551C), Jefferson Amará (201765125A), Luis Augusto T. Guimarães (201365165AC)
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <chrono>

#include "Graph.h"
#include "VertexCover.h"

using namespace std;

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		cout << "Usage: ./VertexCover <graph_file_path> <algorithm>" << endl;
		cout << "<algorithm>: 1 - Greedy solution, 2 - Incremental solution, 3 - Brute force solution" << endl;

		return 0;
	}

	// Instância e carrega um grafo não orientado
	Graph *graph = new Graph(false);

	// Carrega o grafo a partir de um arquivo
	graph->load(argv[1]);
	
	switch (atoi(argv[2]))
	{
		case 1:
		{
			// Marca o tempo para resolução do problema
			auto t1 = chrono::high_resolution_clock::now();
			
			vector<int> cover = VertexCover::greedySolution(graph);
			
			auto t2 = std::chrono::high_resolution_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
			cout << "Time: " << duration.count() << " seconds" << std::endl;

			// Imprime a solução
			cout << endl << "Vertex cover size: " << cover.size() << endl;
			cout << "Vertex cover: " << endl;

			for (int i = 0; i < cover.size(); i++)
			{
				cout << " " << cover.at(i);
			}

			cout << endl;
			break;
		}
		case 2:
		{
			// Marca o tempo para resolução do problema
			auto t1 = chrono::high_resolution_clock::now();
			
			vector<int> cover = VertexCover::incrementalSolution(graph->getEdgeList(), graph->edgeCount());
			
			auto t2 = std::chrono::high_resolution_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
			cout << "Time: " << duration.count() << " seconds" << std::endl;

			// Imprime a solução
			cout << endl << "Vertex cover size: " << cover.size() << endl;
			cout << "Vertex cover: " << endl;

			for (int i = 0; i < cover.size(); i++)
			{
				cout << " " << cover.at(i);
			}

			cout << endl;
			break;
		}
		case 3:
		{
			// Marca o tempo para resolução do problema
			auto t1 = chrono::high_resolution_clock::now();
			
			vector<int> cover = VertexCover::bruteForceSolution(graph);
			
			auto t2 = std::chrono::high_resolution_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
			cout << "Time: " << duration.count() << " seconds" << std::endl;

			// Imprime a solução
			cout << endl << "Vertex cover size: " << cover.size() << endl;
			cout << "Vertex cover: " << endl;

			for (int i = 0; i < cover.size(); i++)
			{
				cout << " " << cover.at(i);
			}

			cout << endl;
			break;
		}
		default:
			cout << "<algorithm>: 1 - Greedy solution, 2 - Incremental solution, 3 - Brute force solution" << endl;
	}

	// Desaloca a memória do grafo
	delete graph;
	return 0;
}