/*
 * Tarefa 02 - Alteracoes de Transito
 *
 * GEN254 - Grafos - 2024/2
 *
 * Nome:      Isadora Laís Ruschel
 * Nome:      Augusto Renostro Remus   
 */
#include "Digrafo.h"
#include <iostream>
#include <vector> 
#include <list>

using namespace std;

Digrafo::Digrafo(int num_vertices) {
    if (num_vertices <= 0) {
        cout << "O numero de vertices eh invalido!";
        return;
    }

    num_vertices_ = num_vertices;
    num_arestas_ = 0;

    listas_adj_.resize(num_vertices);

    
}

int Digrafo::num_vertices() {
    return num_vertices_;
}

int Digrafo::num_arestas() {
    return num_arestas_;
}

bool Digrafo::tem_aresta(Aresta e){
    for(auto i: listas_adj_[e.v1]){
        if(i==e.v2){
            return true;
        }
    }
    return false;
}

void Digrafo::insere_aresta(Aresta e) {
    if(tem_aresta(e)|| (e.v1==e.v2)){
        return;
    }

    listas_adj_[e.v1].push_front(e.v2);
    num_arestas_++;
}


void Digrafo::remove_aresta(Aresta e) {
    if(tem_aresta(e)&& (e.v1!=e.v2)){
        listas_adj_[e.v1].remove(e.v2);
        num_arestas_--;
    }
}

void Digrafo::inicializa_marcado(vector<int> &marcado){
    for(int i=0;i<num_vertices_;i++){
        marcado[i]=0;
    }
}

void Digrafo::busca_prof_fin(int v, vector<int> &marcado, vector<int> &fin, int &i)
{
    marcado[v] = 1;
    for (int u = 0; u < num_vertices_; u++){
        if (tem_aresta(Aresta(v,u)))
            if (marcado[u] == 0)
                busca_prof_fin(u, marcado, fin,i);
    }
    fin[v]=i;
    i++;
}

void Digrafo::busca_prof(int v, vector<int> &marcado) {
    marcado[v] = 1;
    for (int u = 0; u < num_vertices_; u++)
        if (tem_aresta(Aresta(v,u)))
            if (marcado[u] == 0)
                busca_prof(u, marcado);
}

int Digrafo::encontra_maior(vector<int> &vet, vector<int> &marcado){
    int v = -1;
    int maior = -1;
    for (int i = 0; i < num_vertices_;i++) {
        if (!marcado[i] && vet[i]>maior) {
            maior = vet[i];
            v = i;
        }
    }
    return v;
}

vector<int> Digrafo::monta_componente(vector<int> &marcado, vector<int> &adicionados){
    vector<int> v; // Vai ter os vértices da componente fortemente conexa
    for(int i=0;i<num_vertices_;i++){
        if(marcado[i] && !adicionados[i]){ // Se tiver sido marcado e ainda não tiver sido adicionado a uma componente, coloca no vetor v
            v.push_back(i);
            adicionados[i]=1;
        }
    }
    return v;
}

void Digrafo::determina_componentes_fortemente_conexas()
{
    int i=0;
    vector<int> marcado(num_vertices_);
    inicializa_marcado(marcado);
    vector<int> fin(num_vertices_);
    for(int j=0;j<num_vertices_;j++){ // faz a busca em profundidade a partir de vertices não marcados
        if(!marcado[j]){
            busca_prof_fin(j,marcado,fin,i);
        }
    }
    Digrafo invertido(num_vertices_);
    for(int j=0;j<num_vertices_;j++){
        for (auto k : listas_adj_[j]){
            invertido.insere_aresta(Aresta(k,j)); //cria o grafo com as arestas invertidas
        }
    }

    inicializa_marcado(marcado);
    vector<int> adicionados(num_vertices_);
    inicializa_marcado(adicionados);
    vector<vector<int>> componentes;//Vai ter os vetores de cada componente fortemente conexa

    for(int j=0;j<num_vertices_;j++){ //faz as buscas pelas componentes fortemente conexas
        int k = invertido.encontra_maior(fin,marcado);
        if(k==-1){ //já percorreu todos os vértices
            break;
        }
        if(!marcado[k]){
            invertido.busca_prof(k,marcado);//Marca no vetor marcado os vértices da componente fortemente conexa visitados 
            componentes.push_back(monta_componente(marcado,adicionados));//Coloca os vértices da componente fortemente conexa e adiciona ao vetor de componentes.
        }
    }
    faz_procura(componentes);
}


void Digrafo::faz_procura(vector<vector<int>> &componentes){
    int i=0;
    while(i<int(componentes.size())){ //para todas as componentes
        int caminhos = 0;
        cout << i << ": ";//imprime
        for(int k=0;k<int(componentes.size());k++){ // tem o indice da outra componente que está sendo verificada
            bool encontrou = false;
            if(i==k){ // se for a mesma componente, passa pra próxima
                continue;
            }
            else{
                for(auto vi:componentes[i]){ // pra cada vértice da componente i
                    if(encontrou){ // Se já encontrou caminho pra componente k, passa pra próxima
                        break;
                    }
                    for(auto vk:componentes[k]){// testa se há caminho para algum vértice da outra componente
                        if(encontrou){
                            break;
                        }
                        if (tem_aresta(Aresta(vi,vk))){
                            caminhos++;
                            encontrou = true;
                            break;
                        }
                    }
                }
            } 
        }
        cout<< caminhos << "\n";
        i++;
    }

}