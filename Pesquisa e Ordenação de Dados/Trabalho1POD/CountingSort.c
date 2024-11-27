/**
 * @file CountingSort.c
 * @author Isadora Laís Ruschel
 * @date 2024-04-26
 *
 * @copyright Copyright (c) 2024
 *
 *
 * @brief Counting Sort - Trabalho 1 POD
 */
#include <stdio.h>
#include <stdlib.h>

struct tlist {
    int valor;
    struct tlist* next;
}; typedef struct tlist List; //Nomeei como List

//Retorna a lista com o nó adicionado
List *createNode(List *first, int val){
    List *node = (List *)malloc(sizeof(List));//Aloca o espaço na memória para o nó
    node->next=NULL;
    node->valor= val;
    if(first==NULL){//Se o first é NULL, a lista está vazia
        return node;
    }
    List *aux;
    for(aux = first; aux->next!=NULL;aux=aux->next); //Percorre a lista até o último elemento
    aux->next = node;//Último elemento passa a apontar para o nó novo
    return first; //Atualiza a lista
}

void freeList(List **first){
    List *aux= *first, *aux2=*first;//Dois aux, um para liberar a memória e outro para percorrer a lista
    while (aux!=NULL){
        aux= aux->next;//Aux sempre no nó posterior ao nó do aux2
        free(aux2);//Libera o nó atual
        aux2= aux;//Aponta pro nó seguinte, o mesmo do aux
    }
    *first = NULL;
}

void fillVector(List *first, List **vec){//Atribui os nós ao vetor
    List *aux = first;
    int i=0;
    while(aux!= NULL){
        vec[i] = aux;
        i++;
        aux = aux->next;
    }
}

void printList(List *first){//Percorre a lista até o final, imprimindo os nós
    List *aux= first;
    for(aux = first; aux!=NULL; aux=aux->next){
        printf("%d ",aux->valor);
    }
    printf("\n");
}

void updateList(List **first, List **vec, int size){//Atualiza a lista encadeada com o vetor com os nós ordenados
    for(int i=0; i<size; i++){
        if(i< size- 1) {//Se não for o último, faz o nó atual apontar pro próximo 
            vec[i]->next=vec[i+1];
        }
        else{//Se for o último, precisa apontar pra NULL
            vec[i]->next=NULL;
        }
    }
    *first = vec[0];//Atualiza o first
}

int encontraMaior(List **A, int size){//Encontra o maior valor da lista para o Counting criar o vetor
    int maior = A[0]->valor;
    for(int i=1;i<size;i++){
        if(A[i]->valor>maior){
            maior = A[i]->valor;
        }
    }
    return maior;
}

void countingSort(List **A, int size){//Função adaptada para o vetor de ponteiros
    int k= encontraMaior(A, size);
    int count[k+1];
    List *aux[size];
    for(int i= 0; i <= k;i++){
        count[i] = 0; /* inicializa contagem com zeros */
    }
    for(int i= 0; i < size;i++){ /* para cada elemento de A */
        count[A[i]->valor]++; /* incrementa contador */
    }
    for(int i =1; i <= k;i++){
        count[i] += count[i-1]; /* soma acumulada */
    }
    for(int i =size-1; i >= 0;i--){
        count[A[i]->valor] = count[A[i]->valor] - 1;
        aux[count[A[i]->valor]] = A[i]; /* insere em aux */
    }
    for(int i= 0; i < size;i++){
        A[i] = aux[i]; /* copia para vetor original */
    }
}

int main()
{
    List *first= NULL;
    int vList[]={7,18,11,3,0};//Vetor com os valores da lista
    int size = sizeof(vList) / sizeof(vList[0]);//Tamanho do vetor/lista
    List *nList[size];//Vetor com os ponteiros para os nós da lista pra ser possível utilizar as posições dele para atualizar os next's

    for(int i=0; i<size;i++){
        first = createNode(first,vList[i]);//Cria a lista com os valores do vetor
    }

    fillVector(first, nList);    
    printList(first);//Antes do sort
    countingSort(nList,size);//Ordena o vetor com os nós
    updateList(&first,nList,size);//Atualiza os next's dos nós da lista
    printList(first);//Depois do sort
    freeList(&first);//Libera a lista

    return 0;

}