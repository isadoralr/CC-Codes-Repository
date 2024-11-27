/*
 * Tarefa 01 - Grafo - Listas de Adjacencia
 *
 * GEN254 - Grafos - 2024/2
 *
 * Nome:      Isadora Laís Ruschel
 */

#include "Grafo.h"
#include <iostream>
#include <vector> 

using namespace std;

Grafo::Grafo(int num_vertices) {
    if (num_vertices <= 0) {
        cout << "O numero de vertices eh invalido!";
    }

    num_vertices_ = num_vertices;
    num_arestas_ = 0;

    listas_adj_.resize(num_vertices);
}

int Grafo::num_vertices() {
    return num_vertices_;
}

int Grafo::num_arestas() {
    return num_arestas_;
}

bool Grafo::tem_aresta(Aresta e){
    for(auto i: listas_adj_[e.v1]){
        if(i==e.v2){
            return true;
        }
    }
    return false;
}

void Grafo::insere_aresta(Aresta e) {
    if(tem_aresta(e)|| (e.v1==e.v2)){
        return;
    }

    listas_adj_[e.v1].push_front(e.v2);
    listas_adj_[e.v2].push_front(e.v1);
    num_arestas_++;
}


void Grafo::remove_aresta(Aresta e) {
    if(tem_aresta(e)&& (e.v1!=e.v2)){
        listas_adj_[e.v1].remove(e.v2);
        listas_adj_[e.v2].remove(e.v1);
        num_arestas_--;
    }
}
int Grafo::num_arestas_subgrafo_induzido(vector<int> vet) {
    int num = 0;  
    if (vet.size() > 1) {
        for (int i = 0; i < int(vet.size()-1); i++) { 
            for(int j=i+1; j<int(vet.size());j++){
                Aresta e(vet[i], vet[j]);
                if (tem_aresta(e)) {  
                    num++; 
                }
            }
        }
    }
    return num;
}

void Grafo::imprime_complemento(){
    for(int i =0; i<int(listas_adj_.size());i++){
        cout << i<<": ";
        for(int j=0; j<int(listas_adj_.size());j++){
            Aresta e(i,j);
            if(!tem_aresta(e) && e.v1!=e.v2){
                 cout<<j<< " ";
            }
        }
        cout << "\n";
    }

}
