using namespace std;

#include <iostream>
#include <vector>
#include "Grafo.h"
#include "No.h"
#include "Aresta.h"

No::No(int id) {
    this->id = id;
    this->grauNo = 0;
    this->grauEntrada = 0;
    this->grauSaida = 0;
    this->visitado = 0;
            
}


void No::insereNoAdj(int idNo){
    No* no = new No(idNo);
    this->ListaNosAdj.push_back(no);
}

void No::setVisitado(int v){
    this->visitado = v;
}

int No::getVisitado(){
    return this->visitado;
}

void No::removeNoAdj(int idNo){
     for (int i = 0; i< this->ListaNosAdj.size(); i++) {
        if (this->ListaNosAdj.at(i)->getId() == idNo) {
            this->ListaNosAdj.erase(this->ListaNosAdj.begin() + i);
            this->grauNo--;
                
        }
    }
}

int No::getId() {
    return this->id;
}
int No::getGrauNo(){
    return this->grauNo;
}
void No::setGrauNo(int g){
    this->grauNo = g;
}

int No::getGrauEntrada(){
    return this->grauEntrada;
}

void No::setGrauEntrada(int g){
    this->grauEntrada = g;
}

int No::getGrauSaida(){
    return this->grauSaida;
}

void No::setGrauSaida(int g){
    this->grauSaida = g;
}


vector<No*> No::getListaNosAdj(){
     return this->ListaNosAdj;
}
