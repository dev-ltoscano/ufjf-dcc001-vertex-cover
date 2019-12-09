using namespace std;

#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include "Grafo.h"
#include "No.h"
#include "Aresta.h"
#include <cstdlib>
#include<fstream>
#include<valarray>
#include <iomanip>

Grafo::Grafo() {
    this->tamanho = 0;
}

Grafo::~Grafo() {
}

void Grafo::insereNoGrafo(int idNo) {
    if (this->checkNo(idNo) != 1) {
        No* no = new No(idNo);
        this->ListaNos.push_back(no);
        this->tamanho = this->tamanho + 1;
        cout << "No inserido com sucesso\n";
    } else {
        cout << "No ja esta no grafo\n";
    }
}

vector<Aresta*> Grafo::getListaArestas() {
    return this->ListaArestas;
}

vector<No*> Grafo::getListaNos() {
    return this->ListaNos;
}

int Grafo::checkNo(int idNo) {
    for (int i = 0; i< this->ListaNos.size(); i++) {
        if (this->ListaNos.at(i)->getId() == idNo) {
            //            cout << "No encontrado\n";
            return 1;
        }
    }
    return -1;
}

int Grafo::getTamanho() {
    return this->ListaNos.size();
}

void Grafo::setTamanho(int t) {
    this->tamanho = t;
}

void Grafo::verificaGrafoCompleto() {
    int qtdNoGrafo = this->ListaNos.size();
    int qtdArestasGrafo = this->ListaArestas.size();

    if (qtdArestasGrafo == (qtdNoGrafo * (qtdNoGrafo - 1) / 2)) {
        cout << "O grafo é Completo";
    } else {
        cout << "O grafo não é completo";
    }
}

void Grafo::verificaBipartido() {
    int k = 1;
    for (int i = 0; i < this->ListaArestas.size(); i++) {

        if (this->ListaArestas.at(i)->getListaNosIncid().at(0)->getVisitado() == 0) {
            this->ListaArestas.at(i)->getListaNosIncid().at(0)->setVisitado(k);
            k++;
        }

        if (this->ListaArestas.at(i)->getListaNosIncid().at(1)->getVisitado() == 0) {
            this->ListaArestas.at(i)->getListaNosIncid().at(0)->setVisitado(k);
            k--;
        }
        
        if (this->ListaArestas.at(i)->getListaNosIncid().at(0)->getVisitado() == this->ListaArestas.at(i)->getListaNosIncid().at(1)->getVisitado()) {
            cout << "Nao  eh um grafo bipartido" << endl;
            return;
        }
    }
    
    for (int i = 0; i < this->ListaArestas.size(); i++) {
        this->ListaArestas.at(i)->getListaNosIncid().at(0)->setVisitado(0);
        this->ListaArestas.at(i)->getListaNosIncid().at(1)->setVisitado(0);
    }
    cout << "O grafo eh bipartido" << endl;
}

void Grafo::informarVizinhancaFechada(int idNo) {
    if (this->getNoPorId(idNo)->getListaNosAdj().size() > 0) {
        cout << "A vizinhança fechada do nó é: \n";
        cout << "{ " << this->getNoPorId(idNo)->getId() << " ,";
        for (int i = 0; i<this->getNoPorId(idNo)->getListaNosAdj().size(); i++) {
            cout << this->getNoPorId(idNo)->getListaNosAdj().at(i)->getId() << " , ";
        }
        cout << " }";
    } else {
        cout << "A vizinhança fechada do nó é: \n";
        cout << "{ " << this->getNoPorId(idNo)->getId() << " }";
    }
}

void Grafo::informarVizinhancaAberta(int idNo) {
    if (this->getNoPorId(idNo)->getListaNosAdj().size() > 0) {
        cout << "A vizinhança aberta do nó é: \n";
        cout << "{ ";
        for (int i = 0; i<this->getNoPorId(idNo)->getListaNosAdj().size(); i++) {
            cout << this->getNoPorId(idNo)->getListaNosAdj().at(i)->getId() << " , ";
        }
        cout << " }";
    } else {
        cout << "O nó não possui vizinhança aberta";
    }

}

void Grafo::removeNoGrafo(int idNo) {

    if (getNoPorId(idNo) != NULL) {
        if (getNoPorId(idNo)->getGrauNo() > 0) {
            //removendo o nó das listas de adjacencia
            for (int i = 0; i<this->ListaNos.size(); i++) {
                removeArestaGrafo(this->ListaNos.at(i)->getId(), idNo);
                removeArestaGrafo(idNo, this->ListaNos.at(i)->getId());
                //cout<<".."<<endl;
            }

        }
        // removendo da lista do grafo
        for (int i = 0; i< this->ListaNos.size(); i++) {
            if (this->ListaNos.at(i)->getId() == idNo) {
                this->ListaNos.at(i)->setGrauNo(this->ListaNos.at(i)->getGrauNo() - 1);
                this->ListaNos.erase(this->ListaNos.begin() + i);
                cout << "No removido com sucesso";
            }
        }
        this->tamanho = this->tamanho - 1;
    }

}

void Grafo::verificarKRegular(int k) {
    for (int i = 0; i < ListaNos.size(); i++) {
        if (ListaNos.at(i)->getGrauNo() != k) {
            cout << "O grafo não é " << k << " regular";
            return;
        }
    }
    cout << "O grafo é " << k << " regular";
}

void Grafo::insereArestaGrafo(int idNo1, int idNo2, int peso) {
    int idAresta = concat(idNo1, idNo2);
    if (getNoPorId(idNo1) != NULL && getNoPorId(idNo2) != NULL) {
        if (this->checkAresta(idAresta, peso) != 1) {
            No* no1 = this->getNoPorId(idNo1);
            No* no2 = this->getNoPorId(idNo2);
            Aresta* ar = new Aresta(no1, no2, peso, idAresta);
            this->ListaArestas.push_back(ar);
            no1->insereNoAdj(no2->getId());
            no2->insereNoAdj(no1->getId());
            no1->setGrauNo(no1->getGrauNo() + 1);
            no2->setGrauNo(no2->getGrauNo() + 1);
            if (orientado) {
                no1->setGrauSaida(no1->getGrauSaida() + 1);
                no2->setGrauEntrada(no2->getGrauEntrada() + 1);
            }
            cout << "Aresta inserida com sucesso\n";
        } else {
            cout << "Aresta ja esta no grafo\n";
        }
    } else {
        cout << "Um dos nós não existe no grafo\n";
    }
}

int Grafo::checkAresta(int idAresta, int peso) {
    for (int i = 0; i< this->ListaArestas.size(); i++) {
        if (this->ListaArestas.at(i)->getIdAresta() == idAresta) {
            if (this->ListaArestas.at(i)->getPesoAresta() == peso) {
                cout << "Aresta encontrada\n";
                return 1;
            }
        }
    }
    //cout << "Aresta NAO encontrada" << endl;
    return -1;
}

No * Grafo::getNoPorId(int idNo) {
    No* noAux = NULL;
    for (int i = 0; i< this->ListaNos.size(); i++) {
        if (this->ListaNos.at(i)->getId() == idNo) {
            noAux = this->ListaNos.at(i);
            return noAux;
        }
    }
    return noAux;
}

void Grafo::removeArestaGrafo(int idNo1, int idNo2, int peso) {
    int idAresta = concat(idNo1, idNo2);

    for (int i = 0; i < this->ListaArestas.size(); i++) {
        if (this->ListaArestas.at(i)->getIdAresta() == idAresta && this->ListaArestas.at(i)->getPesoAresta() == peso) {//if (checkAresta(idAresta, peso) == 1) {
            if (orientado) {
                getNoPorId(idNo1)->setGrauSaida(getNoPorId(idNo1)->getGrauSaida() - 1);
                getNoPorId(idNo2)->setGrauEntrada(getNoPorId(idNo2)->getGrauEntrada() - 1);
            }
            getNoPorId(idNo1)->removeNoAdj(idNo2);
            getNoPorId(idNo2)->removeNoAdj(idNo1);
            this->ListaArestas.erase(this->ListaArestas.begin() + i);

            cout << "Aresta entre os nós: " << idNo1 << " e " << idNo2 << " removida com sucesso\n";
        }
    }
}

int Grafo::getOrdemGrafo() {
    return this->tamanho;
}

int Grafo::getGrauNoPorId(int idNo) {
    if (checkNo(idNo) == 1) {
        return getNoPorId(idNo)->getGrauNo();
    } else {
        cout << "no nao existe" << endl;
        return checkNo(idNo);
    }
}

void Grafo::ehTrivial() {
    if (this->tamanho == 1 && this->ListaArestas.size() == 0) {
        cout << "Eh um grafo trivial" << endl;
    } else {
        cout << "NAO eh um grafo trivial" << endl;
    }
}

void Grafo::ehNulo() {
    if (this->tamanho == 0) {
        cout << "Eh um grafo Nulo" << endl;
    } else {
        cout << "NAO eh um grafo Nulo" << endl;
    }
}

void Grafo::getSeqNos() {
    if (this->tamanho > 0) {
        vector<int> vetor;
        for (int i = 0; i< this->ListaNos.size(); i++) {
            vetor.push_back(this->ListaNos.at(i)->getGrauNo());
        }
        std::sort(vetor.begin(), vetor.end());
        cout << "{";
        for (int i = vetor.size() - 1; i >= 0; i--) {
            cout << vetor.at(i) << "-";
        }
        cout << "}";
    }
}

void Grafo::leArquivo(const char arquivo[50]) {
    ifstream arq_entrada;
    int *vet_dados = new int[10000000];
    int i = 0;
    arq_entrada.open(arquivo);

    if (arq_entrada.is_open()) {
        while (!arq_entrada.eof()) {
            arq_entrada >> vet_dados[i];
            i++;
            cout<<i<<endl;
            cout<<vet_dados[i]<<endl;
        }
    }
    arq_entrada.close();
    int tam = vet_dados[0];
    for (int j = 1; j < i - 2; j = j + 3) {
        this->insereNoGrafo(vet_dados[j]);
        this->insereNoGrafo(vet_dados[j + 1]);
        this->insereArestaGrafo(vet_dados[j], vet_dados[j + 1], vet_dados[j + 2]);
    }
}

void Grafo::escreveArquivo(const char enderecoSaida[50]) {
    ofstream arq_saida;
    arq_saida.open(enderecoSaida);
    

    if (!arq_saida.good())
        cout << "Arquivo nao pode ser criado" << endl;
    else{ 
        arq_saida << this->tamanho<< endl;
        arq_saida << "\r\n";
    for (int i = 0; i < this->ListaArestas.size(); i++) {
        arq_saida << this->ListaArestas.at(i)->getListaNosIncid().at(0)->getId();
        arq_saida << " ";
        arq_saida << this->ListaArestas.at(i)->getListaNosIncid().at(1)->getId();
        arq_saida << " ";
        arq_saida << this->ListaArestas.at(i)->getPesoAresta();
        arq_saida << "\r\n";
    }
    cout << "Arquivo Criado com sucesso" << endl;
}

arq_saida.close();

}

int Grafo::concat(int x, int y) {
    int m = 10;
    while (y / m > 0)
        m *= 10;
    return y + m*x;
}

void Grafo::ehMultigrafo() {
    if (this->ListaArestas.size() > 0) {
        vector<int> vetor;
        for (int i = 0; i< this->ListaArestas.size(); i++) {
            vetor.push_back(this->ListaArestas.at(i)->getIdAresta());
			if(this->ListaArestas.at(i)->getListaNosIncid().at(0)->getId() == this->ListaArestas.at(i)->getListaNosIncid().at(1)->getId()){
				cout<<"Eh multigrafo"<<endl;
				return;
				}
        }
        std::sort(vetor.begin(), vetor.end());
        int id = vetor.at(0);

        for (int i = 1; i < vetor.size(); i++) {
            if (vetor.at(i) == id) {
                cout << "Eh Multigrafo" << endl;
                return;
            }
            id = vetor.at(i);
        }
        cout << "Nao eh multigrafo" << endl;
    } else
        cout << "Nao eh multigrafo" << endl;
}

int Grafo::checkAresta(int idAresta) {
    for (int i = 0; i< this->ListaArestas.size(); i++) {
        if (this->ListaArestas.at(i)->getIdAresta() == idAresta) {
            cout << "Aresta encontrada\n";
            return 1;
        }
    }
    //cout << "Aresta NAO encontrada" << endl;
    return -1;
}

void Grafo::removeArestaGrafo(int idNo1, int idNo2) {
    int idAresta = concat(idNo1, idNo2);

    for (int i = 0; i < this->ListaArestas.size(); i++) {
        if (this->ListaArestas.at(i)->getIdAresta() == idAresta) {

            getNoPorId(idNo1)->removeNoAdj(idNo2);
            getNoPorId(idNo2)->removeNoAdj(idNo1);
            this->ListaArestas.erase(this->ListaArestas.begin() + i);
            if (orientado) {
                getNoPorId(idNo1)->setGrauSaida(getNoPorId(idNo1)->getGrauSaida() - 1);
                getNoPorId(idNo2)->setGrauEntrada(getNoPorId(idNo2)->getGrauEntrada() - 1);
            }
            cout << "Aresta entre os nós: " << idNo1 << " e " << idNo2 << " removida com sucesso\n";
        }
    }
}

void Grafo::setOrientado() {
    char chave;
    cout << "O Grafo é orientado? [S/N] = ";
    cin >> chave;
    while (chave != 'S' && chave != 'N' && chave != 's' && chave != 'n') {
        cout << "Digite o tipo de Grafo" << endl;
        cout << "(S) para orientado" << endl;
        cout << "(N) para nao orientado" << endl << " = ";
        cin>> chave;
    }

    if (chave == 'S' || chave == 's')
        this->orientado = true;
}

bool Grafo::getOrientado() {
    return this->orientado;
}