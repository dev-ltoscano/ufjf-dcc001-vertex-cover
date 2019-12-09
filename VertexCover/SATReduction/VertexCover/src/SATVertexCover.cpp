/*
*	An�lise e Projeto de Algoritmos - Problema da Cobertura de V�rtices
*	Allan Carlos Amaral Ribeiro (201465551C), Jefferson Amar� (201765125A), Luis Augusto T. Guimar�es (201365165AC)
*/
#include "SATVertexCover.h"

#include <sstream>
#include <chrono>

bool SATVertexCover::isVertexCover(vector<int> cover, Graph *graph)
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

vector<int> SATVertexCover::solve(Graph *graph)
{
	vector<int> combination;

	bool hasAnSolution = false;
	uint32_t k = 1;

	// Itera com k variando de k = 1 até k = |V|
	while(!hasAnSolution && k <= graph->vertexCount())
	{
		auto t1 = std::chrono::high_resolution_clock::now();

		std::cout << "k=" << k << " ";
		generateSATFile(*graph, k, true);
		callMinisat();
		hasAnSolution = checkSATSolution(combination, k, graph->vertexCount());
		k++;

		auto t2 = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
		std::cout << duration.count() << " seconds" << std::endl;
	}

	if(!isVertexCover(combination, graph))
	{
		combination.clear();
	}

	return combination;
}

// Gera o arquio que será utilizado pelo resolvedor SAT
// θ(k*(|V|²+|E|)) - Nao Otimizado
// θ(k*(|V|+|E|))  - Otimizado
void SATVertexCover::generateSATFile(Graph& graph, uint32_t k, bool optimizedAtMostOne)
{
	std::stringstream ss;
	uint32_t totalClausulesNumber = 0;

	unordered_map<int, GraphVertex*> vertexList = graph.getVertexList();
	unordered_map<int, GraphEdge*>   edgeList   = graph.getEdgeList();

	uint64_t variables = k * vertexList.size();

	// Cada vertice recebe um id baseado em i, tal que 1 <= i <= k
	// θ(k*(|V|+ 3*|V|) -> θ(k*|V|)  - otimizado
	// θ(k*(|V|+|V|²)   -> θ(k*|V|²) - nao otimizado
	for(uint32_t i = 1; i <= k; i++)
	{
		ss << "c Vertex Part - i = " << i << std::endl;
		std::vector<int64_t> vertexIds;
		uint32_t numClausules = 0;

		// For each vertex
		for(auto& vertex : vertexList)
		{
			int64_t id = (vertex.first-1) * k + i;
			vertexIds.push_back(id);
		}
		if(optimizedAtMostOne)
			atMostOneOpt(vertexIds, numClausules, variables, ss); // θ(3*n)
		else 
			atMostOne(vertexIds, numClausules, ss);	// θ(n^2)
		totalClausulesNumber += numClausules;
	}

	// Segunda parte, para cada aresta, garante que pelo menos um dos end points fazem parte da solução
	// θ(k*|E|)
	for(auto& edge : edgeList)
	{
		// Como nao tratamos digrafos, arestas de volta (id negativo) são desconsideradas
		if (edge.first < 0) continue;

		ss << "c Edge " << edge.first << std::endl;
		std::vector<int64_t> vertexIds;
		uint32_t numClausules = 0;

		for(uint32_t i = 1; i <= k; i++)
		{
			int64_t uId = (edge.second->getIdFirstVertex() -1)*k + i;
			int64_t vId = (edge.second->getIdSecondVertex()-1)*k + i;
			vertexIds.push_back(uId);
			vertexIds.push_back(vId);
		}

		atLeastOne(vertexIds, numClausules, ss); // θ(n)
		totalClausulesNumber += numClausules;
	}

	std::ofstream of("sat.in", std::ofstream::out | std::ofstream::binary);
	of << "p cnf " << variables << " " << totalClausulesNumber << std::endl;
	of << ss.rdbuf();
	of.close();
}

void SATVertexCover::callMinisat()
{
	#ifdef __linux__
		system("./minisat sat.in sat.out -no-luby -verb=0 -rinc=1.5 -phase-saving=0 -rnd-freq=0.02");
	#else
		system("minisat.exe sat.in sat.out -no-luby -verb=0 -rinc=1.5 -phase-saving=0 -rnd-freq=0.02 > nul");
	#endif
}

bool SATVertexCover::checkSATSolution(std::vector<int>& cover, uint32_t k, int vertexCount)
{
	std::ifstream in("sat.out", std::ifstream::in | std::ifstream::binary);
	std::string result;
	int32_t variable;
	in >> result;

	// Se for satisfativel, nos temos uma cobertura
	// Leia o resto do aquivo para montar a lista de vertices da solução
	if(result == "SAT")
	{
		// Limpa qualquer possivel solução anterior
		cover.clear();

		in >> variable;
		while(variable != 0)
		{	
			// Se a  variavel for maior que  0, é verdadeira.
			// Portanto, faz parte da solução
			if(variable > 0)
			{
				int id = ((variable-1) / k) + 1;
				if(id <= vertexCount)
				{
					cover.push_back(id);
				} // Se for maior que o numero de vertices, é uma variavel
				  // adicional criada pelo atMostOne.
			}
			in >> variable;
		}

		return true;
	}
	else if (result == "UNSAT")
	{
		return false;
	}
}

void SATVertexCover::atMostOneOpt(std::vector<int64_t>& ids, uint32_t& clausules, uint64_t& variables, std::stringstream& ss)
{
	int64_t r = variables - 1;
	ss << -ids[0] << " " << -ids[1] << " 0" << std::endl;
	ss << -ids[0] << " " <<     r+2 << " 0" << std::endl;
	ss << -ids[1] << " " <<     r+2 << " 0" << std::endl;
	clausules = 3;
	for(int32_t j = 2; j < (int32_t)ids.size(); j++)
	{
		ss << -(r+j) << " " << -ids[j] << " 0" << std::endl;
		clausules++;
	}
	for(int32_t j = 2; j < (int32_t)ids.size()-1; j++)
	{
		ss << -(r+j) << " " << (r+j+1) << " 0" << std::endl;
		clausules++;
	}
	for(int32_t j = 2; j < (int32_t)ids.size()-1; j++)
	{
		ss << -ids[j] << " " << r+j+1 << " 0" << std::endl;
		clausules++;
	}
	variables += ids.size() - 2;
}

void SATVertexCover::atMostOne(std::vector<int64_t>& ids, uint32_t& clausules, std::stringstream& ss)
{
	clausules = 0;
	for(uint64_t i = 0; i < ids.size(); i++)
	{
		for(uint64_t j = 0; j < i; j++)
		{
			ss << -ids[i] << " " << -ids[j] << " 0" << std::endl;
			clausules++; 
		}
	}
}

void SATVertexCover::atLeastOne(std::vector<int64_t>& ids, uint32_t& clausules, std::stringstream& ss)
{
	for(uint64_t i = 0; i < ids.size(); i++)
	{
		ss << ids[i] << " ";
	}
	ss << "0" << std::endl;
	clausules = 1;
}