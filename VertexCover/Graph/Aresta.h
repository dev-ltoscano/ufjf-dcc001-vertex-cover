#ifndef ARESTA_H
#define ARESTA_H

using namespace std;

#include <iostream> //entrada e saida de dados
#include <vector> //estrutura que armazena vectora de objetos 
#include <algorithm> // função find O(1)
#include "No.h"

class Aresta {
private:
    int idAresta;
    int pesoAresta;
    vector<No*> ListaNosIncid;

public:
    Aresta(No* no1, No* no2, int peso, int id);
    ~Aresta();
    void setPesoAresta(int peso);
    int getIdAresta();
    vector <No*> getListaNosIncid();
    int getPesoAresta();
};


#endif /* ARESTA_H */ 