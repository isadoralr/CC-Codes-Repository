/*
 * Trabalho 2 
 *
 * GEX101 - Linguagens Formais e Autômatos - 2025/1
 *
 * Nome:      Isadora Laís Ruschel
 * Nome:      Nycollas Wildney
 */

#include "Transicao.h"

Transicao::Transicao(int estado_origem, char simbolo, char remove_topo, char insere_topo, int estado_destino)
    : estado_origem(estado_origem), simbolo(simbolo), remove_topo(remove_topo), insere_topo(insere_topo), estado_destino(estado_destino) {
}