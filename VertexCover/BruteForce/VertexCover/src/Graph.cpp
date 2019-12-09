/*
*	Análise e Projeto de Algoritmos - Problema da Cobertura de Vértices
*	Allan Carlos Amaral Ribeiro (201465551C), Jefferson Amará (201765125A), Luis Augusto T. Guimarães (201365165AC)
*/

#include "Graph.h"

Graph::Graph(bool oriented)
{
	this->oriented = oriented;
}

Graph::Graph(Graph *graph)
{
	this->oriented = graph->isOriented();

	for (auto it = graph->vertexList.begin(); it != graph->vertexList.end(); it++)
	{
		addVertex(new GraphVertex(it->second->getId()));
	}

	for (auto it = graph->vertexList.begin(); it != graph->vertexList.end(); it++)
	{
		unordered_map<int, GraphEdge*> tmpAdjList = it->second->getEdgeList();

		for (auto it2 = tmpAdjList.begin(); it2 != tmpAdjList.end(); it2++)
		{
			addEdge(new GraphEdge(it2->second->getId(), it2->second->getIdFirstVertex(), it2->second->getIdSecondVertex(), it2->second->getWeight()));
		}
	}
}

Graph::Graph(bool oriented, int vertexCount, double edgeProb)
{
	random_device	rd;
	mt19937 gen(rd());
	bernoulli_distribution dist(edgeProb);

	this->oriented = oriented;

	for (int i = 0; i < vertexCount; i++)
	{
		addVertex(new GraphVertex(i + 1));
	}

	int idEdge = 0;

	for (int i = 1; i < vertexCount; i++)
	{
		for (int j = i + 1; j < vertexCount; j++)
		{
			if (dist(gen))
			{
				addEdge(new GraphEdge(++idEdge, i, j, 0));
			}
		}
	}
}

Graph::~Graph()
{
	// Desaloca a memória de cada vértice da lista de vértices do grafo
	for (auto it = vertexList.begin(); it != vertexList.end(); it++)
	{
		delete it->second;
	}

	// Desaloca a memória de cada aresta da lista de arestas do grafo
	for (auto it = edgeList.begin(); it != edgeList.end(); it++)
	{
		delete it->second;
	}
}

void Graph::load(string filename)
{
	ifstream graphFile;

	// Tenta abrir o arquivo
	graphFile.open(filename);

	// Verifica se o arquivo foi aberto
	if (graphFile.is_open())
	{
		// Quantidade de vértices do grafo
		int vertexCount;

		// Faz a leitura da quantidade de vértices
		graphFile >> vertexCount;

		// Adiciona a quantidade de vértices no grafo
		for (int i = 1; i <= vertexCount; i++)
		{
			addVertex(new GraphVertex(i));
		}

		// Id da aresta (u, v)
		int idEdge = 1;

		// IDs dos vértices da aresta (u, v)
		int idFirstVertex, idSecondVertex;

		// Peso da aresta (u, v)
		double adjWeight = 0;

		// Repete até o fim do arquivo
		while (!graphFile.eof())
		{
			// Faz a leitura da aresta do grafo
			graphFile >> idFirstVertex >> idSecondVertex >> adjWeight;

			// Adiciona a aresta no grafo
			addEdge(new GraphEdge(idEdge, idFirstVertex, idSecondVertex, adjWeight));

			idEdge++;
		}

		// Fecha o arquivo
		graphFile.close();
	}
}

void Graph::save(string filename)
{
	ofstream graphFile(filename.c_str(), ofstream::out | ofstream::binary);

	graphFile << vertexCount() << std::endl;

	for (auto& edge : edgeList)
	{
		graphFile << edge.second->getIdFirstVertex() << " "
					<< edge.second->getIdSecondVertex() << " "
					<< std::endl;
	}

	graphFile.close();
}

void Graph::print()
{
	cout << endl;

	// Imprime a lista de vértices do grafo
	for (auto it = vertexList.begin(); it != vertexList.end(); it++)
	{
		cout << "VERTEX > Id=" << it->second->getId() << " | degree=" << it->second->getDegree() << endl;
	}

	// Imprime a lista de arestas do grafo
	for (auto it = edgeList.begin(); it != edgeList.end(); it++)
	{
		cout << "EDGE > Id=" << it->second->getId() 
			<< " | IdFirstVertex=" << it->second->getIdFirstVertex() << " | IdSecondVertex=" << it->second->getIdSecondVertex() 
			<< " | Weight=" << it->second->getWeight() << endl;
	}

	cout << endl;
}

bool Graph::isOriented()
{
	// Indica se o grafo é orientado ou não
	return oriented;
}

void Graph::addVertex(GraphVertex *vertex)
{
	// Adiciona o vértice na lista de vértices
	vertexList.insert(pair<int, GraphVertex*>(vertex->getId(), vertex));
}

GraphVertex* Graph::getVertex(int idVertex)
{
	// Retorna o vértice com 'idVertex' da lista de vértices
	return vertexList.at(idVertex);
}

unordered_map<int, GraphVertex*> Graph::getVertexList()
{
	// Retorna a lista de vértices
	return vertexList;
}

void Graph::removeVertex(int idVertex)
{
	// Obtém o vértice do grafo a partir do 'idVertex'
	GraphVertex *vertex = getVertex(idVertex);

	// Obtém a lista de arestas do vértice
	unordered_map<int, GraphEdge*> vertexEdgeList = vertex->getEdgeList();

	// Remove todas as arestas do vértice do grafo
	for (auto it = vertexEdgeList.begin(); it != vertexEdgeList.end(); it++)
	{
		// Remove a aresta do grafo
		removeEdge(it->first);
	}

	// Remove o vértice
	vertexList.erase(vertex->getId());

	// Desaloca a memória do vértice
	delete vertex;
}

int Graph::vertexCount()
{
	// Retorna a quantidade de vértices do grafo
	return static_cast<int>(vertexList.size());
}

void Graph::addEdge(GraphEdge *edge)
{
	// Adiciona a aresta na lista de arestas do grafo
	edgeList.insert(pair<int, GraphEdge*>(edge->getId(), edge));

	// Obtém o primeiro vértice da aresta (u, v) a partir do Id do vértice
	GraphVertex *firstVertex = getVertex(edge->getIdFirstVertex());

	// Adiciona a aresta na lista de arestas do vértice
	firstVertex->addEdge(edge);

	// Verifica se o grafo não é orientado
	if (!isOriented())
	{
		// Cria a aresta oposta a que está sendo adicionada
		GraphEdge *otherEdge = new GraphEdge((-1 * edge->getId()), edge->getIdSecondVertex(), edge->getIdFirstVertex(), edge->getWeight());

		// Insere a aresta oposta na lista de arestas do grafo
		edgeList.insert(pair<int, GraphEdge*>(otherEdge->getId(), otherEdge));

		// Obtém o vértice do grafo a partir do Id do vértice 
		GraphVertex *secondVertex = getVertex(otherEdge->getIdFirstVertex());

		// Adiciona a aresta na lista de arestas do vértice
		secondVertex->addEdge(otherEdge);
	}
}

GraphEdge* Graph::getEdge(int idEdge)
{
	// Retorna a aresta com 'idEdge' da lista de vértices
	return edgeList.at(idEdge);
}

unordered_map<int, GraphEdge*> Graph::getEdgeList()
{
	// Retorna a lista de arestas
	return edgeList;
}

void Graph::removeEdge(int idEdge)
{
	// Obtém a aresta do grafo a partir de 'idEdge'
	GraphEdge *edge = getEdge(idEdge);

	// Obtém o primeiro vértice da aresta (u, v) a partir do Id do vértice
	GraphVertex *firstVertex = getVertex(edge->getIdFirstVertex());

	// Remove a aresta da lista de arestas do vértice
	firstVertex->removeEdge(edge->getId());

	// Remove a aresta da lista de arestas do grafo
	edgeList.erase(idEdge);

	// Verifica se o grafo não é orientado
	if (!isOriented())
	{
		// Obtém a aresta oposta a que está sendo removida
		GraphEdge *otherEdge = getEdge((-1 * edge->getId()));

		// Obtém o vértice do grafo a partir do Id do vértice
		GraphVertex *secondVertex = getVertex(otherEdge->getIdFirstVertex());

		// Remove a aresta da lista de arestas do vértice
		secondVertex->removeEdge(otherEdge->getId());

		// Remove a aresta da lista de arestas do grafo
		edgeList.erase(otherEdge->getId());

		// Desaloca a memória da aresta
		delete otherEdge;
	}

	// Desaloca a memória da aresta
	delete edge;
}

int Graph::edgeCount()
{
	// Retorna a quantidade de arestas do grafo
	return static_cast<int>(edgeList.size());
}