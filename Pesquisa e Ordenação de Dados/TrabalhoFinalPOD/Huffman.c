/**
 * @file Huffman.c
 * @author Isadora Laís Ruschel
 * @date 2024-06-15
 *
 * @copyright Copyright (c) 2024
 *
 *
 * @brief Codificação de Huffman - Trabalho Final POD
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

struct tlist {
    char letra;
    int freq;
    struct tlist* left;
    struct tlist* right;
}; typedef struct tlist List; //Nomeei como List

//O nó adicionado
List *createNode(char caractere){
    List *node = (List *)malloc(sizeof(List));//Aloca o espaço na memória para o nó
    node->freq=1;
    node->left=NULL;
    node->right=NULL;
    node->letra= caractere;
    return node;
}

////////////////////////////////////////////////////////
void intercala(List **A, int inicio, int meio, int fim){
    List *auxiliar[fim-inicio+1];
    int i =inicio; 
    int j = meio + 1; 
    int k = 0; 
    while(i <=meio && j<= fim){
        if(A[i]->freq < A[j]->freq || (A[i]->freq == A[j]->freq && A[i]->letra <= A[j]->letra)){// Mais detalhes de ordenação
            auxiliar[k]= A[i];
            i++;
        }else{
            auxiliar[k]= A[j];
            j++;
        }
        
        k++;
    }
    while(i <=meio){ /* ainda há elementos na primeira parte */
        auxiliar[k] =A[i];
        k++;
        i++;
    }
    while(j <= fim){ /* ainda há elementos na segunda parte */
        auxiliar[k] = A[j];
        k++;
        j++;
    }
    for(k=inicio;k<=fim; k++){ /* transferindo elementos de volta para o
        vetor original */
        A[k] = auxiliar[k - inicio];
    }
}

void mergeSort(List **A, int inicio, int fim){
    if(inicio <fim){
            int meio = (inicio + fim)/ 2;
            mergeSort(A, inicio, meio);
            mergeSort(A, meio + 1, fim);
            intercala(A, inicio, meio, fim);
        }
}
////////////////////////////////////////////////////////
int convertString(char *string, List **stringNodes){// Considerando que a string não terá caracteres especiais, faz as contagens e remove caracteres repetidos
    int k=0;// Contador de letras únicas
    for(int i=0;i<strlen(string);i++){
        if(string[i]!='-'){
            stringNodes[k]= createNode(string[i]);// Cria o nó da letra
            for(int j=i+1;j<strlen(string);j++){
                if(string[i]==string[j]){
                    string[j]='-';
                    stringNodes[k]->freq++;
                }
            }
            k++;
        }
    }
    if(k>1){
        mergeSort(stringNodes, 0,k-1);
    }
    return k;
}

List* trieMaker(char *string){
    List *stringNodes[strlen(string)];// Vetor com os nós de cada caractere da string
    int tamanho = convertString(string,stringNodes);
    int inicio=0;
    while(inicio<(tamanho-1) && tamanho>1){// Se tiver + de 1 caractere, monta a trie e para quando tiver chegado na raiz (um nó restante)
        List *newNode =createNode('\0');
        newNode->left =stringNodes[inicio];
        newNode->right =stringNodes[inicio+1];
        newNode->freq = stringNodes[inicio]->freq+stringNodes[inicio+1]->freq;
        stringNodes[inicio+1]=newNode;
        stringNodes[inicio]=NULL;
        inicio++;
        mergeSort(stringNodes,inicio,tamanho-1);
    }
    return stringNodes[inicio];
}

int codeSize(List* root) { //Calcula a profundidade máxima da árvore (estimar quantidade máxima de dígitos em binário)
    if(root ==NULL) {
        return 0;
    }
    int leftDepth = codeSize(root->left);
    int rightDepth = codeSize(root->right);
    if (leftDepth >rightDepth) {
        return leftDepth +1;
    }else {
        return rightDepth +1;
    }
}

int searchLetra(List* root, int codigo[], char letra, int posicao){// Procura a letra e bota o código no vetor
    if(root == NULL){
        return 0;
    }
    if(root->letra == letra){
        return 1;
    }
    if(root->left != NULL){
        if(searchLetra(root->left, codigo, letra, posicao + 1)){
            codigo[posicao + 1] = 0;
            return 1;
        }
    }
    if(root->right != NULL){
        if(searchLetra(root->right, codigo, letra, posicao + 1)){
            codigo[posicao + 1] = 1;
            return 1;
        }
    }
    return 0;
}

void codifica(List* root, int tamanho, FILE *amostra, FILE *codificado){
    rewind(amostra);
    while (!feof(amostra)){
        char letra = fgetc(amostra);
        if (letra == EOF) break;
        int codigo[tamanho];
        for(int i=0;i<tamanho;i++) {
            codigo[i]= -1; // Inicializa o vetor com -1 pra saber o fim de cada um
        }
        if(root->letra==letra && root->left==NULL && root->right==NULL){// Se a trie só possui um caractere, o código será 0
            fputc('0', codificado);
        }
        else if(searchLetra(root, codigo, letra, -1)){// Encontrou a letra e atualizou o vetor com o código
            int i=0;
            while(i<tamanho && codigo[i] != -1){
                char num = codigo[i] + '0';// Conversão int pra char
                fputc(num, codificado);// Coloca os bits da letra no arquivo codificado
                i++;
            }
        }
    }
}

void decodifica(List *root, FILE *codificado, FILE *decodificado){
    List *aux= root;
    
    if(aux != NULL && aux->left==NULL && aux->right==NULL){// Se há apenas um nó (a root), ou seja só uma letra
        while (!feof(codificado)){
            char cod = fgetc(codificado);// Para fazer o ponteiro andar
            if(cod==EOF){
                break;
            }
            fputc(aux->letra, decodificado);
        }
    }
    else{
        while (!feof(codificado)){
            if(aux != NULL && aux->left==NULL && aux->right==NULL){// Chegou na folha desejada
                fputc(aux->letra, decodificado);
                aux=root;
            }
            else{
                char cod = fgetc(codificado);
                if (cod == EOF) {
                    break;
                }
                if(cod=='0'){
                    aux = aux->left;
                }
                else if (cod=='1'){
                    aux = aux->right;
                }
            }
        }
    }
    
}


void convertFileString(FILE *fp, char string[]){// Captura os números do arquivo e adiciona à string
    int i=0;
    char letra;
    while ((letra = fgetc(fp)) != EOF) {
        string[i] = letra;
        i++;
    }
    string[i] = '\0';
}

int main()
{
    FILE *amostra = fopen("amostra.txt", "r");
    FILE *codificado = fopen("codificado.txt", "w+");
    FILE *decodificado = fopen("decodificado.txt", "w");
    char string[100];// Armazenar o conteúdo do arquivo
    convertFileString(amostra,string);
    List *root=trieMaker(string);// Trie feita
    codifica(root, codeSize(root),amostra,codificado);
    rewind(codificado);// Já foi percorrido, volta
    decodifica(root, codificado, decodificado);
    fclose(amostra);
    fclose(codificado);
    fclose(decodificado);
    return 0;
}