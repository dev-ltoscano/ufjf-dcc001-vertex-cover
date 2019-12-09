/*
*	Análise e Projeto de Algoritmos - Problema da Cobertura de Vértices
*	Allan Carlos Amaral Ribeiro (201465551C), Jefferson Amará (201765125A), Luis Augusto T. Guimarães (201365165AC)
*/

#include "MergeSort.h"

void MergeSort::merge(vector<GraphVertex*> *vertexList, int start, int end, int middle)
{
	vector<GraphVertex*> tmpVerticeList(end - start + 1);
	int i = start;
	int j = middle + 1;
	int k = 0;

	while ((i <= middle) && (j <= end))
	{
		if (vertexList->at(i)->getDegree() > vertexList->at(j)->getDegree())
		{
			tmpVerticeList[k++] = vertexList->at(i);
			i++;
		}
		else
		{
			tmpVerticeList[k++] = vertexList->at(j);
			j++;
		}
	}

	while (i <= middle)
	{
		tmpVerticeList[k++] = vertexList->at(i);
		i++;
	}

	while (j <= end)
	{
		tmpVerticeList[k++] = vertexList->at(j);
		j++;
	}

	for (i = start; i <= end; i++)
	{
		vertexList->at(i) = tmpVerticeList[i - start];
	}

}

void MergeSort::sort(vector<GraphVertex*> *vertexList, int start, int end)
{
	if (start < end)
	{
		int middle = (start + end) / 2;

		sort(vertexList, start, middle);
		sort(vertexList, middle + 1, end);

		merge(vertexList, start, end, middle);
	}
}