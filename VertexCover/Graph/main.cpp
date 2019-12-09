using namespace std;

#include<iostream>
#include<string>
#include <cstdlib>
#include "Grafo.h"
#include<fstream>
#include<valarray>
#include <iomanip>

void exibeMenu(Grafo *g, const char enderecoSaida[50]){
    char opcao;
    while (true) {
        cout << endl;
        cout << "~~TRABALHO GRAFOS GRUPO X ~~" << endl
                << endl;
        cout << endl;
        cout << "          Menu de funcionalidades            " << endl;
        cout << "(a) Inclusão de Nó no Grafo" << endl;
        cout << "(b) Inclusão de Aresta no Grafo" << endl;
        cout << "(c) Imprimir o Grau de um Nó" << endl;
        cout << "(d) Verificar a k regularidade do Grafo" << endl;
        cout << "(e) Informar a Ordem do Grafo " << endl;
        cout << "(f) Informar se o Grafo é Trivial " << endl;
        cout << "(g) Informar se o Grafo é Nulo " << endl;
        cout << "(h) Mostrar a vizinhança aberta de um Nó " << endl;
        cout << "(i) Mostrar a vizinhança fechada de um Nó" << endl;
        cout << "(j) Verificar se é um Multigrafo" << endl;
        cout << "(k) Verificar se o Grafo é completo" << endl;
        cout << "(l) Verificar se o Grafo é Bipartido" << endl;
        cout << "(m) Apresentar a sequencia de graus" << endl;
        cout << "(n) Remoção de Aresta no Grafo" << endl;
        cout << "(o) Remoção de No no Grafo" << endl;
        cout << "(x) Sair do programa" << endl;
        cout << "(w) Salvar a instancia e Sair" << endl;

        cin >> opcao;

        while (!(opcao >= 'a' && opcao <= 'x')) {
            cout << "opção incorreta" << endl
                    << "Digite uma opção válida: ";
            cin >> opcao;
        }

        int v = 1;
        int v1 = 1;
        int v2 = 1;
        int p = 0;
        cout << endl
                << endl;

        switch (opcao) {
            case 'a':
                int v;
                cout << "Digite o ID do Nó para a inclusão:";
                cin >> v;
                g->insereNoGrafo(v);
                cout << endl
                        << endl;
                break;

            case 'b':
                cout << "Digite o ID do primeiro Nó e do segundo e o peso da aresta entre eles" << endl
                        << " seguidos de enter" << endl;
                cout << " - ";
                cin >> v1;
                cout << " - ";
                cin >> v2;
                cout << " - ";
                cin >> p;
                g->insereArestaGrafo(v1, v2, p);
                cout << endl
                        << endl;
                break;

            case 'c':
                cout << "Digite o ID do Nó: ";
                cin >> v;
                if (!g->getOrientado()) {
                    cout << "O grau do nó é : " << g->getGrauNoPorId(v);
                } else {
                    cout << "O grau de saida do nó é : " << g->getNoPorId(v)->getGrauSaida() << endl;
                    cout << "O grau de entrada do nó é : " << g->getNoPorId(v)->getGrauEntrada() << endl;
                }
                break;

            case 'd':
                cout << "Informe k: ";
                cin >> v;
                g->verificarKRegular(v);
                break;

            case 'e':
                cout << "A Ordem do Grafo é " << g->getTamanho() << endl;
                break;

            case 'f':
                g->ehTrivial();
                break;

            case 'g':
                g->ehNulo();
                break;

            case 'h':
                cout << "Digite o numero do Nó: ";
                cin >> v;
                g->informarVizinhancaAberta(v);
                break;

            case 'i':
                cout << "Digite o numero do Nó: ";
                cin >> v;
                g->informarVizinhancaFechada(v);
                break;

            case 'j':
                g->ehMultigrafo();
                break;

            case 'k':
                g->verificaGrafoCompleto();
                break;

            case 'l':
                g->verificaBipartido();
                break;

            case 'm':
                g->getSeqNos();
                break;

            case 'n':
                cout << "Digite o ID do primeiro Nó e do segundo e o peso da aresta entre eles" << endl
                        << " seguidos de enter" << endl;
                cout << " - ";
                cin >> v1;
                cout << " - ";
                cin >> v2;
                cout << " - ";
                cin >> p;
                g->removeArestaGrafo(v1, v2, p);
                cout << endl
                        << endl;
                break;
            case 'o':
                cout << "Digite o ID do Nó para a exclusão:";
                cin >> v;
                g->removeNoGrafo(v);
                cout << endl
                        << endl;
                break;
            case 'x':
                exit(0);
                break;

            case 'w':
                g->escreveArquivo(enderecoSaida);
                exit(0);
                break;
        }
    }
    
    
}

int main(int argc, char **argv) {

	string graphFile = "D:\\Data\\Developer\\UFJF\\APA2018\\dados5.txt";
	string graphOutFile = "D:\\graph.txt";

    Grafo *g = new Grafo();
    g->setOrientado();
    g->leArquivo(graphFile.c_str());

    exibeMenu(g,argv[2]);

    delete g;

	system("PAUSE");
    return 0;
}
