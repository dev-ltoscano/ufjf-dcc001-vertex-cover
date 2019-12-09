#ifndef GRAFO_H
#define GRAFO_H

using namespace std;

#include <string>
#include <vector>
#include "Aresta.h"
#include "No.h" 

class Grafo {
private:
    bool orientado;
    int tamanho;
    vector<No*> ListaNos;
    vector<Aresta*> ListaArestas;
    int contMultAresta;
public:
    Grafo();
    ~Grafo();
    void setTamanho(int t);
    int getTamanho();
    void insereNoGrafo(int idNo);
    void insereArestaGrafo(int idNo1, int idNo2, int peso);
    void removeArestaGrafo(int idNo1, int idNo2, int peso);
    void removeArestaGrafo(int idNo1, int idNo2);
    void removeNoGrafo(int idNo);
    int checkNo(int idNo);
    int checkAresta(int idAresta, int peso);
    int checkAresta(int idAresta);
    void verificarKRegular(int k);
    void informarVizinhancaAberta(int idNo);
    void informarVizinhancaFechada(int idNo);
    void verificaGrafoCompleto();
    void verificaBipartido();
    vector<No*> getListaNos();
    vector<Aresta*> getListaArestas();
    No* getNoPorId(int idNo);
    int getGrauNoPorId(int idNo);
    int getOrdemGrafo();
    void ehTrivial();
    void ehNulo();
    void ehMultigrafo();
    void getSeqNos();
    void leArquivo(const char arquivo[50]);
    void escreveArquivo(const char enderecoSaida[50]);
    int concat(int x, int y);
    void setOrientado();
    bool getOrientado();
};


#endif /* GRAFO_H */