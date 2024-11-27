/*
 * Tarefa 01 - Grafo - Listas de Adjacencia
 *
 * GEN254 - Grafos - 2024/2
 *
 * Nome:      Isadora Laís Ruschel
 */

#ifndef GRAFO_H

#define GRAFO_H
#include <vector>
#include "Aresta.h"
#include <list>

class Grafo {
public:
    Grafo(int num_vertices);
    // ~Grafo(); // Se necessario
    int num_arestas();
    int num_vertices();
    void insere_aresta(Aresta e);
    void remove_aresta(Aresta e);
    bool tem_aresta(Aresta e);
    int num_arestas_subgrafo_induzido(std::vector<int> vet);
    void imprime_complemento();
private:
    int num_vertices_;
    int num_arestas_;
    std::vector<std::list<int>> listas_adj_;
    void valida_vertice(int v);
    void valida_aresta(Aresta e);
};
    

#endif /* GRAFO_H */