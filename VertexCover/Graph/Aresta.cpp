using namespace std;

#include <iostream>
#include <vector>
#include "Grafo.h"
#include "No.h"
#include "Aresta.h"

Aresta::Aresta(No* no1, No* no2, int peso, int id) {
    this->idAresta = id;
    this->pesoAresta = peso;
    this->ListaNosIncid.push_back(no1);
    this->ListaNosIncid.push_back(no2);
}

Aresta::~Aresta() {
};

int Aresta::getIdAresta(){
    return this->idAresta;
}

int Aresta::getPesoAresta(){
    return this->pesoAresta;
}

vector <No*> Aresta::getListaNosIncid(){
    return this->ListaNosIncid;
}