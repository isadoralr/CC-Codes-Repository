/*
 * Tarefa 02 - Alteracoes de Transito
 *
 * GEN254 - Grafos - 2024/2
 *
 * Nome:      Isadora Laís Ruschel
 * Nome:      Augusto Renostro Remus   
 */

#ifndef DIGRAFO_H

#define DIGRAFO_H
#include <vector>
#include "Aresta.h"
#include <list>

class Digrafo {
public:
    Digrafo(int num_vertices);
    int num_arestas();
    int num_vertices();
    void insere_aresta(Aresta e);
    void remove_aresta(Aresta e);
    bool tem_aresta(Aresta e);
    void busca_prof(int v, std::vector<int> &marcado);
    void busca_prof_fin(int v, std::vector<int> &marcado, std::vector<int> &fin, int &i);
    std::vector<int> monta_componente(std::vector<int> &marcado, std::vector<int> &adicionados);
    void determina_componentes_fortemente_conexas();
    int encontra_maior(std::vector<int> &vet, std::vector<int> &marcado);
    void inicializa_marcado(std::vector<int> &marcado);
    void faz_procura(std::vector<std::vector<int>> &componentes);
    
private:
    int num_vertices_;
    int num_arestas_;
    std::vector<std::list<int>> listas_adj_;
    void valida_vertice(int v);
    void valida_aresta(Aresta e);
};
    

#endif /* GRAFO_H */