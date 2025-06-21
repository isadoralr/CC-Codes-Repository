/*
 * Trabalho 2 
 *
 * GEX101 - Linguagens Formais e Autômatos - 2025/1
 *
 * Nome:      Isadora Laís Ruschel
 * Nome:      Nycollas Wildney
 */
#ifndef AUTOMATO_H

#define AUTOMATO_H
#include <vector>
#include <list>
#include "Transicao.h"
#include <string>

class Automato {
public:
    Automato(int num_estados);
    int num_transicoes();
    int num_estados();
    int estado_final();
    bool tem_transicao(Transicao t);
    void insere_transicao(Transicao t);
    void montar_padrao();
    Transicao encontrar_transicao(int estado_atual, char simbolo, char topo_pilha);
    bool processar_entrada(std::string entrada);
private:
    int num_transicoes_;
    int num_estados_;
    int estado_final_;
    std::vector<std::list<Transicao>> automato_listas_transicoes_;
};
    

#endif /* AUTOMATO_H */