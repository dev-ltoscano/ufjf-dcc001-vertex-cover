#ifndef NO_H
#define NO_H


#include <iostream> 
#include <vector>  
#include <algorithm> 
#include "Aresta.h"

using namespace std;

class No {
private:
    int id;
    int grauNo;
    int grauSaida;
    int grauEntrada;
    vector <No*> ListaNosAdj;
    int visitado;
    //vector <Aresta*> ListaArestasIncid;

public:
    No(int id);
    ~No();
    int getId();
    void insereNoAdj(int idNo);
    //void insereArestaIncid(int idAresta);
    //void removeArestaIncid(int idAresta);
    void removeNoAdj(int idNo);
    int getGrauNo();
    void setGrauNo(int g);
    int getGrauEntrada();
    void setGrauEntrada(int g);
    int getGrauSaida();
    void setGrauSaida(int g);
    void setVisitado(int v);
    int getVisitado();
    vector<No*> getListaNosAdj();
};

#endif /* NO_H */