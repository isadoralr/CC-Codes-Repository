/*
 * Tarefa 02 - Alteracoes de Transito
 *
 * GEN254 - Grafos - 2024/2
 *
 * Nome:      Isadora Laís Ruschel
 * Nome:      Augusto Renostro Remus   
 */
#include "Aresta.h"
#include "Digrafo.h"
#include <iostream>
#include <vector> 

using namespace std;
int main() {

    int P,D;
    cin>>P>>D;
    Digrafo digrafo(P);



    for(int i=0;i<D;i++){
        
        int X,Y,S;
        cin>>X>>Y>>S;
       

        if(S==1){
            digrafo.insere_aresta(Aresta(X,Y));
        }
        else if(S==2){
            digrafo.insere_aresta(Aresta(X,Y));
            digrafo.insere_aresta(Aresta(Y,X));
        }
    }
    digrafo.determina_componentes_fortemente_conexas();
  
    return 0;
}