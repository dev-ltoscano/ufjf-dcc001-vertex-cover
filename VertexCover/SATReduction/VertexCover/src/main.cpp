/*
*	An�lise e Projeto de Algoritmos - Problema da Cobertura de V�rtices
*	Allan Carlos Amaral Ribeiro (201465551C), Jefferson Amar� (201765125A), Luis Augusto T. Guimar�es (201365165AC)
*/

#include <iostream>
#include <chrono>

#include "Graph.h"
#include "SATVertexCover.h"

using namespace std;

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		cout << "Usage: ./SATVertexCover <graph_file_path>" << endl;
		cout << "       ./SATVertexCover <number_of_vertex> <edge_probability> [graph_save_path]" << endl;
		return 0;
	}

	Graph *graph = nullptr;
	
	if(argc == 2)
	{
		graph = new Graph(false);
		graph->load(argv[1]);
		graph->print();
	}
	else
	{
		graph = new Graph(false, atoi(argv[1]), atof(argv[2]));
		if(argc == 4) graph->save(argv[3]);
		graph->print();
	}

	// Marca o tempo para resolução do problema
	auto t1 = chrono::high_resolution_clock::now();
	
	vector<int> cover = SATVertexCover::solve(graph);
	
	auto t2 = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
	cout << "Time: " << duration.count() << " seconds" << std::endl;
	
	cout << endl << "Vertex cover: " << endl;
	cout << "Size: " << cover.size() << endl;

	for (int i = 0; i < cover.size(); i++)
	{
		cout << " " << cover[i];
	}

	cout << endl;

	delete graph;
	return 0;
}