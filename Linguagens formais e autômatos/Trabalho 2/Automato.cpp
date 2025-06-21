/*
 * Trabalho 2 
 *
 * GEX101 - Linguagens Formais e Autômatos - 2025/1
 *
 * Nome:      Isadora Laís Ruschel
 * Nome:      Nycollas Wildney
 */
#include "Automato.h"
#include <iostream>
#include <stack>

using namespace std;

Automato::Automato(int num_estados) {
    if (num_estados <= 0) {
        cout << "Numero de estados invalido!";
        return;
    }

    num_estados_ = num_estados;
    num_transicoes_ = 0;

    automato_listas_transicoes_.resize(num_estados);
}

int Automato::num_estados() {
    return num_estados_;
}

int Automato::num_transicoes() {
    return num_transicoes_;
}

int Automato::estado_final() {
    return estado_final_;
}

Transicao Automato::encontrar_transicao(int estado_atual, char simbolo, char topo_pilha){ // Não é preciso informar o destino
    for(auto transicao: automato_listas_transicoes_[estado_atual]){
        // Considerando que só tem uma transição possível de executar saindo do estado (pega a primeira que encontra)
        if((transicao.simbolo==simbolo || transicao.simbolo=='e') && (transicao.remove_topo==topo_pilha || transicao.remove_topo=='e') ){
            return transicao;
        }
    }
    return Transicao(-1, 'e', 'e', 'e', -1); // Retorna transição inválida se não encontrou transição 
}

bool Automato::tem_transicao(Transicao t){ // Verifica se já tem transição que pode ser realizada saindo do estado com o caractere e o topo da pilha atual
    for(auto transicao: automato_listas_transicoes_[t.estado_origem]){
        if((transicao.simbolo==t.simbolo && transicao.remove_topo==t.remove_topo) || (transicao.simbolo==t.simbolo && transicao.remove_topo=='e')
            || (transicao.simbolo=='e' && transicao.remove_topo==t.remove_topo) || (transicao.simbolo=='e' && transicao.remove_topo=='e'))
        {
            return true;
        }
    }
    return false;
}


void Automato::insere_transicao(Transicao t) {
    // Se já tem transição possível não insere outra igual ou possível
    if(tem_transicao(t)) {
        return;
    }
    
    automato_listas_transicoes_[t.estado_origem].push_front(t);
    num_transicoes_++;
}

// Função para montar o autômato feito
void Automato::montar_padrao(){
    // Transições do autômato (epsilon sendo representado por 'e' para não dar problema na compilação)
    vector<Transicao> transicoes = {Transicao(0, 'e', 'e', '$',1),
                                    Transicao(1, 'A', 'A', 'e', 1),
                                    Transicao(1, 'T', 'T', 'e', 1),
                                    Transicao(1, 'C', 'e', 'e', 1),
                                    Transicao(1, 'G', 'e', 'e', 1),
                                    Transicao(1, 'A', '$', '$', 2),
                                    Transicao(1, 'A', 'T', 'T', 2),
                                    Transicao(1, 'T', '$', '$', 3),
                                    Transicao(1, 'T', 'A', 'A', 3),
                                    Transicao(1, '#', '$', 'e', 4),
                                    Transicao(2, 'e', 'e', 'T', 1),
                                    Transicao(3, 'e', 'e', 'A', 1)
                                    };
    for(auto transicao : transicoes) {
        insere_transicao(transicao);
    }
    estado_final_=4;
}

bool Automato::processar_entrada(std::string entrada){
    int estado=0;
    bool encontrou=true; // Encontrou transição?
    stack<char> pilha; // Pilha para armazenar os símbolos da entrada
    for(int i=0;i<entrada.length();i++) {
        char simbolo = entrada[i];
        // Se a pilha estiver vazia envia e (epsilon não é aceito)
        Transicao transicao = encontrar_transicao(estado,simbolo, pilha.empty() ? 'e' : pilha.top());
        if(transicao.estado_origem==-1){
            encontrou = false;
            break;
        }
        if(transicao.remove_topo != 'e') {
            pilha.pop(); // Remove o topo da pilha se a transição encontrada remove o topo
        }
        if(transicao.insere_topo != 'e') {
            pilha.push(transicao.insere_topo); // Insere o símbolo na pilha se a transição encontrada tem símbolo para inserir
        }
        // Se a transição encontrada não consome símbolo de entrada, não consome o símbolo atual, usa ele na próxima iteração.
        if(transicao.simbolo =='e'){ 
            i--;
        }
        estado = transicao.estado_destino;
    }
    if(encontrou && estado==estado_final()){ // Encontrou transição para todos os símbolo da entrada e terminou em estado final
        return true;
    }
    else{
        return false;
    }
}
