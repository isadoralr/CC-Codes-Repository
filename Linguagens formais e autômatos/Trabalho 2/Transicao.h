/*
 * Trabalho 2 
 *
 * GEX101 - Linguagens Formais e Autômatos - 2025/1
 *
 * Nome:      Isadora Laís Ruschel
 * Nome:      Nycollas Wildney
 */
#ifndef TRANSICAO_H

#define TRANSICAO_H

class Transicao {
public:
    const int estado_origem; 
    const char simbolo; // Símbolo que vai ser consumido
    const char remove_topo; // Símbolo que vai precisar estar no topo da pilha e será removido
    const char insere_topo; // Símbolo que vai ser inserido no topo ao realizar a transição
    const int estado_destino;

    Transicao(int estado_origem, char simbolo, char remove_topo, char insere_topo, int estado_destino);

};

#endif /* TRANSICAO_H */