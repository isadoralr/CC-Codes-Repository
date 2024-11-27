/**
 * @file InsertionSort.c
 * @author Isadora Laís Ruschel
 * @date 2024-04-26
 *
 * @copyright Copyright (c) 2024
 *
 *
 * @brief Insertion Sort - Trabalho 1 POD
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

void printList(List *first){//Percorre a lista até o final, imprimindo os nós
    List *aux= first;
    for(aux = first; aux!=NULL; aux=aux->next){
        printf("%d ",aux->valor);
    }
    printf("\n");
}

void insertion(List **first, List *node)//Utiliza o first da nova lista pra inserir os nós ordenamente
{
    if (*first == NULL || (*first)->valor > node->valor){// Verifica se o valor do first é maior que o valor do nó ou se o first é NULL
        node->next = *first;//O nó a ser inserido é o novo first, pois é menor que o first atual
        *first = node; //Atualiza o first da lista passada
        return;
    }
    //Procura o local correto do nó na parte ordenada
    List *aux = *first;
    while (aux->next != NULL && aux->next->valor <= node->valor){//Percorre a lista até encontrar um valor maior do que o a ser inserido ou até chegar no último
        aux = aux->next;//Move o aux para o nó seguinte
    }
    node->next = aux->next; //Atualiza o next do nó inserido corretamente, apontando para o nó com valor maior que o dele
    aux->next = node;//Atualiza o next do nó posterior

} 

void insertionSort(List **first)
{
    List *newList = NULL;//Lista organizada
    List *aux = *first;
    while (aux != NULL)
    {
        List *next = aux->next;// Armazena o nó seguinte, já que o nó do aux será manipulado
        // Insere nó atual na lista organizada
        insertion(&newList, aux);
        aux = next;// Move o aux
    }
    //Atualiza o first com a lista organizada
    *first= newList;
}

int main()
{
    List *first= NULL;
    int vList[]={48,78,14,1,-6,-2};//Vetor com os valores da lista
    int size = sizeof(vList) / sizeof(vList[0]);//Tamanho do vetor/lista
    
    for(int i=0; i<size;i++){
        first = createNode(first,vList[i]);//Cria a lista com os valores do vetor
    }
    printList(first);//Antes do sort
    insertionSort(&first);//First recebe a lista organizada
    printList(first);//Depois do sort
    freeList(&first);//Libera a lista

    return 0;

}