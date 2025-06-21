/*
 * Trabalho 2 
 *
 * GEX101 - Linguagens Formais e Autômatos - 2025/1
 *
 * Nome:      Isadora Laís Ruschel
 * Nome:      Nycollas Wildney
 */
#include <iostream>
#include "Automato.h"
#include <string>


using namespace std;
int main() {

    int num_estados=5;
    Automato automato(num_estados);
    automato.montar_padrao(); // Montar autômato 
    string entrada;
    cout<<"===== Insira a sequencia do DNA =====\n";
    cin>>entrada;
    bool aceitou = automato.processar_entrada(entrada);
    if(aceitou){
        cout<<"===== Sequencia de DNA aceita =====\n";
    }
    else{
        cout << "===== Sequencia de DNA rejeitada =====\n";
    }
    return 0;
}