/**
 * @file TabelaHash.c
 * @author Isadora Laís Ruschel
 * @date 2024-05-23
 *
 * @copyright Copyright (c) 2024
 *
 *
 * @brief Tabela Hash - Trabalho 2 POD
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

void printList(List *first){//Percorre a lista até o final, imprimindo os nós
    List *aux= first;
    for(aux = first; aux!=NULL; aux=aux->next){
        printf("%d ",aux->valor);
    }
    printf("\n");
}

void printTable(List **table, int size){// Imprime a tabela com os nós de cada posição
    printf("------------ Tabela Hash ------------\n");
    for(int i=0;i<size;i++){
        if(table[i]!=NULL){// Printa só as posições que possuem valores
            printf("%d |- ",i); // Mostra índice da tabela seguido da lista encadeada ocupando a posição (i)
            printList(table[i]);
        }
    }
}

void initTable(List **table, int size){// Inicializa a tabela com firsts NULLs para ser possível identificar quais posições estão vazias e quais não
    for(int i=0;i<size;i++){
        List *first=NULL;
        table[i]=first;
    }
}

int tableIndex(int val){
    return val%23;// Calcula a posição na tabela (vetor)
}

void hashing(List **table, int val){// Adiciona o nó à posição calculada pela função tableIndex
    table[tableIndex(val)]= createNode(table[tableIndex(val)], val);// Atualiza os firsts com o nó adicionado
}

void convertFile(FILE *fp, List **hashT){// Captura os números do arquivo e adiciona à tabela

     while(!feof(fp)){//Percorre o arquivo até o final
        char num[12];// Vai armazenar cada número posterior ao ponto e vírgula/final do arquivo
        int i=0; // Conta os caracteres/índices para percorrer os números do arquivo
        char c =' ';// Inicializa c para não ter lixo
        while(!feof(fp) && c!=';'){// Percorre até achar ponto e vírgula ou o fim do arquivo
            c = fgetc(fp);// Recebe o próximo caracter/número
            num[i] = c;// Coloca o caractere na string
            if(c==';' || feof(fp)){ // Se achar ';' ou o final, há um número para adicionar
                num[i]='\0';// Coloca o final da string (onde está o ponto e vírgula)
                hashing(hashT,atoi(num)); // Converte o número e manda para a função adicioná-lo à tabela
            }
            i++;
        }
    }
}

int main()
{
    List *hashT[23];//Vetor, tabela hash com os ponteiros das listas encadeadas
    initTable(hashT,23);// Inicializa a tabela
    
    FILE *fp = fopen("casos_de_teste.txt", "r");// Abre o arquivo

    if (fp == NULL) {// Verifica se foi aberto corretamente
        printf("Erro na abertura do arquivo!");
        return 1;
    }   

    convertFile(fp, hashT);// Converte e adiciona os números do arquivo
    printTable(hashT,23);// Imprime a tabela e seus nós
    return 0;

}