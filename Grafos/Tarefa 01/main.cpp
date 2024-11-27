/*
 * Tarefa 01 - Grafo - Listas de Adjacencia
 *
 * GEN254 - Grafos - 2024/2
 *
 * Nome:      Isadora Laís Ruschel
 */
#include "Aresta.h"
#include "Grafo.h"
#include <iostream>
#include <vector> 

using namespace std;
int main() {

    int v,o;
    cin>>v>>o;
    Grafo g(v);
    for(int i=0; i<o;i++){
        vector<int> vet;
        char op;
        cin>>op;
        int x,y;
        switch(op){
            case 'I':
                cin>>x>>y;
                g.insere_aresta(Aresta(x,y));
                break;
            case 'R':
                cin>>x>>y;
                g.remove_aresta(Aresta(x,y));
                break;
            case 'S':
                int n;
                cin>>n;
            
                for(int i=0;i<n;i++){
                    int vertice;
                    cin>>vertice;
                    vet.push_back(vertice);
                }
                cout<< g.num_arestas_subgrafo_induzido(vet)<<"\n";
                break;
            case 'E':
                cout<< g.num_arestas()<<"\n";
                break;
            case 'X':
                g.imprime_complemento();
                break;
        }   
    }
    return 0;
}