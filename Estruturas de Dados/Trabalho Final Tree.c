#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

#define COUNT 5
#define SIZE 10

typedef struct fardo{
   char cultivar[20];
   char tipoDeFeno;
   int diametro;
} Fardo;

typedef struct data{
   int dia;
   int mes;
   int ano;
} Data;

typedef struct producao{
   int codigo;
   Data dataProducao;
   
   Fardo tipoDeFardo;  
   int qtDeFardos;
   float duracao;
} Producao;

struct tnode {
  Producao producao;
  struct tnode *left, *right;
};
typedef struct tnode vnode;

struct ttree {
  vnode *root;
};

typedef struct ttree vtree;

void initTree(vtree *t) {
  t->root = NULL;
}

bool isEmptyTree(vtree tree) {
    return tree.root == NULL;
}
vnode *newNode(Producao prod) {
  vnode *n;
  n = (vnode *)malloc(sizeof(vnode));
  n->producao = prod;
  n->left = NULL;
  n->right = NULL;
  return n;
}


//
int depthLeft(vnode *r) {
  if (r == NULL)
    return 0;
  return 1 + depthLeft(r->left);
}
int depthRight(vnode *r) {
  if (r == NULL)
    return 0;
  return 1 + depthRight(r->right);
}

// AVL methods
int depthSubTree(vnode *root) {
  int depthLeft, depthRight;

  if (root == NULL)
    return 0;

  // calculate the depth of the left subtree
  depthLeft = depthSubTree(root->left); 
  // calculate the depth of the right subtree
  depthRight =  depthSubTree(root->right); 

  return 1 + (depthLeft > depthRight
                  ? depthLeft
                  : depthRight); // verify the deepest sub-tree and add + 1.
}

vnode *ll(vnode *root) {
  vnode *newRoot = root->left;
  root->left = newRoot->right;
  newRoot->right = root;

  return newRoot;
}

vnode *rr(vnode *root) {
  vnode *newRoot = root->right;
  root->right = newRoot->left;
  newRoot->left = root;

  return newRoot;
}

vnode *lr(vnode *root) {
  root->left = rr(root->left);
  return ll(root);
}

vnode *rl(vnode *root) {
  root->right = ll(root->right);
  return rr(root);
}

vnode *balanceCheck(vnode *root) {
  int rootBalance, childBalance;

  rootBalance = depthSubTree(root->left) - depthSubTree(root->right);

  if (rootBalance > 1) {
    // calculates the balance value of the left child
    childBalance =
        depthSubTree(root->left->left) - depthSubTree(root->left->right);
    root = (childBalance > 0) ? ll(root) : lr(root);

  } else if (rootBalance < -1) {
    // calculates the balance value of the right child
    childBalance =
        depthSubTree(root->right->left) - depthSubTree(root->right->right);
    root = (childBalance < 0) ? rr(root) : rl(root);
  }
  return root;
}

// Function to print binary tree in 2D
// It does reverse inorder traversal
void print2DUtil(vnode *root, int space) {
    // Base case
    if (root == NULL)
        return;
    
    // Increase distance between levels
    space += COUNT;
    
    // Process right child first
    print2DUtil(root->right, space);
    
    // Print current node after space
    // count
    printf("\n");
    for (int i = COUNT; i < space; i++)
        printf(" ");
    printf("-----------------------------\n");
    for (int i = COUNT; i < space; i++)
        printf(" ");
    printf("|Código: %d\n",root->producao.codigo);
    for (int i = COUNT; i < space; i++)
        printf(" ");
    printf("|Data: ");
    printf("%d / ", root->producao.dataProducao.dia);
    printf("%d / ", root->producao.dataProducao.mes);
    printf("%d\n", root->producao.dataProducao.ano);
    for (int i = COUNT; i < space; i++)
        printf(" ");
    printf("|Tipo de fardo:\n");
    for (int i = COUNT; i < space; i++)
        printf(" ");
    printf("| Cultivar: %s\n",root->producao.tipoDeFardo.cultivar);
    for (int i = COUNT; i < space; i++)
        printf(" ");
    printf("| Tipo de feno: %c\n",root->producao.tipoDeFardo.tipoDeFeno);
    for (int i = COUNT; i < space; i++)
        printf(" ");
    printf("| Diâmetro: %d\n",root->producao.tipoDeFardo.diametro);
    for (int i = COUNT; i < space; i++)
        printf(" ");
    printf("|Duração: %.2f\n",root->producao.duracao);
    for (int i = COUNT; i < space; i++)
        printf(" ");
    printf("-----------------------------\n");
    

  // Process left child
  print2DUtil(root->left, space);
}

// Wrapper over print2DUtil()
void print2D(vnode *root) {
  // Pass initial space count as 0
  print2DUtil(root, 0);
}
bool validateFardoType(char type) {
  if (type=='A') {
    return true;
  } else if (type== 'B') {
    return true;
  } else if (type== 'C') {
    return true;
  } else {
    return false;
  }
}
bool validateCultivar(char *cultivar) {
    if (strcmp(cultivar, "Tifton 85") == 0) {
    return true;
    } else if (strcmp(cultivar, "Florakirk") == 0) {
    return true;
    } else if (strcmp(cultivar, "Jiggs") == 0) {
    return true;
    } else if (strcmp(cultivar, "Coastcross") == 0) {
    return true;
    } else {
    return false;
    }
}

bool isValidDate(Data data) {
    // validar dia, mês, e ano
    if (data.ano < 1 || data.mes < 1 || data.mes > 12 || data.dia < 1) {
        return false;
    }

    // Verifica os dias de cada mês
    int daysInMonth;
    switch (data.mes) {
        case 2:
            // Verifica ano bissexto
            daysInMonth = (data.ano % 4 == 0 && (data.ano % 100 != 0 || data.ano % 400 == 0)) ? 29 : 28;
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            daysInMonth = 30;
            break;
        default:
            daysInMonth = 31;
            break;
    }
    
    return data.dia <= daysInMonth;
}


int calculaDiasTotais(Data data){
    return data.dia + data.mes*30 + data.ano*365;
}
vnode *insertNodeR(vnode *root, vnode *n) //  recursive
{
  if (root == NULL)
    return n;

  if (calculaDiasTotais(n->producao.dataProducao) < calculaDiasTotais(root->producao.dataProducao)) // go to left
    root->left = insertNodeR(root->left, n);
  else
    root->right = insertNodeR(root->right, n);

  root = balanceCheck(root);

  return root;
}
// in order
void showTreeRIn(vnode *root) {
  if (root == NULL) {
    printf("\n");
    return;
  }
  showTreeRIn(root->left);
  printf("%d / ", root->producao.dataProducao.dia);
  printf("%d / ", root->producao.dataProducao.mes);
  printf("%d\n", root->producao.dataProducao.ano);
  showTreeRIn(root->right);
}

void freeTree(vnode *n) {
  if (n == NULL)
    return;
  freeTree(n->left);
  freeTree(n->right);
  free(n);
}

vnode *searchById(vnode *n, int id) {
    vnode *result;

    if (n == NULL)
        return NULL;

    if (n->producao.codigo == id)
        return n;

    result = searchById(n->left, id);
    if (result != NULL)
        return result;

    return searchById(n->right, id);
}

vnode *encontrarMenorNo(vnode *node) {
    vnode *atual = node;

    // Loop down to find the leftmost leaf
    while (atual->left != NULL) {
        atual = atual->left;
    }

    return atual;
}



vnode *deleteNode(vnode *root, int id) {
    if (root == NULL) {
        return NULL;
    }

    // If the ID matches, perform the deletion
    if (id == root->producao.codigo) {
        // Node with only one child or no child
        if (root->left == NULL) {
            vnode *temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            vnode *temp = root->left;
            free(root);
            return temp;
        }

        // Node with two children
        vnode *temp = encontrarMenorNo(root->right);

        // Copy the inorder successor's data to this node
        root->producao = temp->producao;

        // Delete the inorder successor
        root->right = deleteNode(root->right, temp->producao.codigo);
    }
    
    root->left = deleteNode(root->left, id);
    root->right = deleteNode(root->right, id);

    // Perform AVL balancing
    return balanceCheck(root);
}

vnode *deleteProd(vnode *root, int id) {
    if (root == NULL) {
        return NULL;
    }

    // deletion based on ID
    root = deleteNode(root, id);
    return root;
}


vnode *deleteNodeById(vnode *root, int id) {
    printf("Deletando produção com código %d\n", id);
    root = deleteProd(root, id);
    if (root == NULL) {
        printf("Sucesso.\n");
    } 
    else {
        printf("Produção não encontrada.\n");
    }
    printf("----------------------------------------------------------\n");
    return root;
}
vnode *alterarDataProducao(vnode *root, int id, Data novaData) {
    if (root == NULL) {
        printf("Árvore vazia.\n");
        return NULL;
    }

    vnode *node = searchById(root, id);

    if (node != NULL) {
        // Atualiza a data no nó
        node->producao.dataProducao = novaData;

        // Rebalanceia a árvore após a alteração
        root = balanceCheck(root);

        printf("Data da produção alterada com sucesso.\n");
    } else {
        printf("Produção não encontrada.\n");
    }

    printf("----------------------------------------------------------\n");
    return root;
}

vnode *alterarProd(vnode *r, int id) {
    if (r == NULL)
        return NULL;

    vnode *node = searchById(r, id);

    if (node != NULL) {
        int op;
        printf("------------------------ ALTERAR -------------------------\n");
        printf("Escolha o campo a ser alterado:\n");
        printf("1 - Código\n");
        printf("2 - Data\n");
        printf("3 - Tipo de Fardo\n");
        printf("4 - Quantidade de Fardos\n");
        printf("5 - Duração\n");
        printf("6 - Cancelar\n");
        printf("----------------------------------------------------------\n");
        printf("Digite o número da opção: ");
        scanf("%d", &op);
        printf("----------------------------------------------------------\n");
        switch (op) {
            case 1:
                // Alterar código
                int cod;
                printf("Insira o novo código: ");
                scanf("%d", &cod);
                if(searchById(r, cod) != NULL) {
                    printf("Código já cadastrado.\n");
                    return r;
                } else {
                    node->producao.codigo = cod;
                }
                break;
            case 2:
                // Alterar data
                Data novaData;
                printf("Insira a nova data:\n");
                printf("Dia: ");
                scanf("%d", &novaData.dia);
                printf("Mês: ");
                scanf("%d", &novaData.mes);
                printf("Ano: ");
                scanf("%d", &novaData.ano);
                r = alterarDataProducao(r, id, novaData);
                break;
            case 3:
                // Alterar tipo de fardo
                char feno='z';
                char cultivar[20];
                while(validateCultivar(cultivar)==false){
                    printf("Insira o novo tipo de fardo:\n");
                    printf("Cultivar: ");
                    scanf("%s",cultivar);
                    if(validateCultivar(cultivar)){
                        strcpy(node->producao.tipoDeFardo.cultivar,cultivar);
                    }
                    else{
                        printf("Cultivar inválido.");
                        printf("----------------------------------------------------------\n");
                    }
                }
                while(validateFardoType(feno)==false){
                    printf("Tipo de feno: ");
                    scanf(" %c", &feno);
                    if(validateFardoType(feno)==true){
                        node->producao.tipoDeFardo.tipoDeFeno=feno;
                    }
                    else{
                        printf("Tipo de feno inválido.\n");
                        printf("----------------------------------------------------------\n");
                    }
                }
                printf("Diâmetro: ");
                scanf("%d", &node->producao.tipoDeFardo.diametro);
                break;
            case 4:
                // Alterar quantidade de fardos
                printf("Insira a nova quantidade de fardos: ");
                scanf("%d", &node->producao.qtDeFardos);
                break;
            case 5:
                // Alterar duração
                printf("Insira a nova duração: ");
                scanf("%f", &node->producao.duracao);
                break;
            case 6:
                // Cancelar
                break;
            default:
                printf("Opção inválida.\n");
                break;
                
        }
    } else {
        printf("Registro não encontrado.\n");
    }

    return r;
}
int qtdFardosProduzidosEmData(vnode *root, Data data) {
    if (root == NULL) {
        return 0;
    }

    int count = 0;

    if (root->producao.dataProducao.dia == data.dia &&
        root->producao.dataProducao.mes == data.mes &&
        root->producao.dataProducao.ano == data.ano) {
        count += root->producao.qtDeFardos;
    }

    count += qtdFardosProduzidosEmData(root->left, data);
    count += qtdFardosProduzidosEmData(root->right, data);

    return count;
}
int somaFardosPorCultivarHelper(vnode *root, char *cultivar) {
    if (root == NULL) {
        return 0;
    }

    int count = 0;

    if (strcmp(root->producao.tipoDeFardo.cultivar, cultivar) == 0) {
        count += root->producao.qtDeFardos;
    }

    count += somaFardosPorCultivarHelper(root->left, cultivar);
    count += somaFardosPorCultivarHelper(root->right, cultivar);

    return count;
}

int somaFardosPorCultivar(vnode *root, char *cultivar) {
    if (root == NULL) {
        return 0;
    }

    int count = somaFardosPorCultivarHelper(root, cultivar);
    return count;
}

int PrintByDateHelper(vnode *root, Data date, int count) {
    if (root != NULL) {
        if (calculaDiasTotais(root->producao.dataProducao) == calculaDiasTotais(date)) {
            printf("%d / ", root->producao.dataProducao.dia);
            printf("%d / ", root->producao.dataProducao.mes);
            printf("%d: %s - ", root->producao.dataProducao.ano, root->producao.tipoDeFardo.cultivar);
            printf("%c - %d\n", root->producao.tipoDeFardo.tipoDeFeno, root->producao.qtDeFardos);
            
            count++;
        }
        count = PrintByDateHelper(root->right, date, count);
        count = PrintByDateHelper(root->left, date, count);
    }
    return count;
}

void PrintByDate(vnode *root, Data date) {
    if (root == NULL) {
        printf("Árvore vazia.\n");
        return;
    }

    printf("------------------ IMPRIMINDO POR DATA -------------------\n");
    int count = PrintByDateHelper(root, date, 0);
    printf("Quantidade de fardos produzidos na data: %d\n",qtdFardosProduzidosEmData(root, date));

    if (count == 0) {
        printf("Não há produções correspondentes à data inserida.\n");
    }

    printf("----------------------------------------------------------\n");
}

int PrintByCultivarHelper(vnode *root, char *cultivar, int count) {
    if (root != NULL) {
        count = PrintByCultivarHelper(root->left, cultivar, count);
        count = PrintByCultivarHelper(root->right, cultivar, count);

        if (strcmp(root->producao.tipoDeFardo.cultivar, cultivar) == 0) {
            printf("%s: %c",root->producao.tipoDeFardo.cultivar,root->producao.tipoDeFardo.tipoDeFeno);
            printf(" - %d\n", root->producao.qtDeFardos);
            count++;
        }
    }
    return count;
}

void PrintByCultivar(vnode *root, char *cultivar) {
    if (root == NULL) {
        printf("Árvore vazia.\n");
        return;
    }

    printf("----------------- IMPRIMINDO POR CULTIVAR -----------------\n");
    int count = PrintByCultivarHelper(root, cultivar, 0);
    printf("Soma da quantidade de fardos com o cultivar: %d\n",somaFardosPorCultivar(root, cultivar));

    if (count == 0) {
        printf("Não há produções correspondentes ao cultivar inserido.\n");
    }

    printf("----------------------------------------------------------\n");
}


int main() {
    int op = 0;
    vtree tree;
    Producao prod;
    initTree(&tree);
    while(op!=7){
        printf("========================== MENU ==========================\n");
        printf("1 - Incluir Produção\n");
        printf("2 - Consultar\n");
        printf("3 - Alterar\n");
        printf("4 - Excluir\n");
        printf("5 - Listar todos\n");
        printf("6 - Limpar lista\n");
        printf("7 - Sair\n");
        printf("==========================================================\n");
        printf("Digite o número da opção: ");
        scanf("%d",&op);
        if(op== 1){
            printf("------------------ INCLUSÃO DE PRODUÇÃO ------------------\n");
            printf("Insira o código da produção:");
            scanf("%d",&prod.codigo);
            if (searchById(tree.root, prod.codigo)!=NULL){
                printf("Código já registrado.\n");
                printf("---------------------- REINICIANDO -----------------------\n");
                continue;
            }
            printf("Insira a data da produção: \n");
            printf("Dia: ");
            scanf("%d",&prod.dataProducao.dia);
            printf("Mês: ");
            scanf("%d",&prod.dataProducao.mes);
            printf("Ano: ");
            scanf("%d",&prod.dataProducao.ano);
            printf("Insira o tipo de fardo: \n");
            printf("Cultivar: ");
            scanf(" %s",prod.tipoDeFardo.cultivar);
            if(!validateCultivar(prod.tipoDeFardo.cultivar)){
                printf("----------------------------------------------------------\n");
                printf("Cultivar inválido.\n");
                printf("---------------------- REINICIANDO -----------------------\n");
                continue;
            }
            printf("Tipo de feno: ");
            scanf(" %c",&prod.tipoDeFardo.tipoDeFeno);//a ou b ou c
            if (!validateFardoType(prod.tipoDeFardo.tipoDeFeno)) {
                printf("----------------------------------------------------------\n");
                printf("Tipo de feno inválido.\n");
                printf("---------------------- REINICIANDO -----------------------\n");
                continue;
            }
            printf("Diâmetro: ");
            scanf("%d",&prod.tipoDeFardo.diametro);
            printf("Insira a quantidade de fardos: ");
            scanf("%d",&prod.qtDeFardos);
            printf("Insira a duração: ");
            scanf("%f",&prod.duracao);
            tree.root = insertNodeR(tree.root, newNode(prod));
            printf("----------------------------------------------------------\n");
        }
        else if(op==2){
            if(!isEmptyTree(tree)){
                printf("------------------------- CONSULTAR ----------------------\n");
                printf("1 - Consultar por data\n");
                printf("2 - Consultar pelo cultivar\n");
                printf("3 - Voltar\n");
                printf("----------------------------------------------------------\n");
                printf("Digite o número da opção: ");
                scanf("%d",&op);
                if(op==1){
                    Data data;
                    printf("Insira a data da produção: \n");
                    printf("Dia: ");
                    scanf("%d",&data.dia);
                    printf("Mês: ");
                    scanf("%d",&data.mes);
                    printf("Ano: ");
                    scanf("%d",&data.ano);
                    PrintByDate(tree.root,data);
                }
                else if(op==2){
                    char cultivar[20];
                    printf("Insira o cultivar: \n");
                    scanf("%s",cultivar);
                    PrintByCultivar(tree.root, cultivar);
                }
            }
            else{
                printf("Árvore vazia.\n");
                printf("---------------------- REINICIANDO -----------------------\n");
            }
        }
        else if(op==3){
            int id;
            if(!isEmptyTree(tree)){
                printf("------------------------ ALTERAR -------------------------\n");
                printf("Insira o código da produção: ");
                scanf("%d",&id);
                if(alterarProd(tree.root, id)==NULL){
                    printf("---------------------- REINICIANDO -----------------------\n");
                    continue;
                    }
                tree.root = alterarProd(tree.root, id);
            }
            else{
                printf("Árvore vazia.\n");
                printf("---------------------- REINICIANDO -----------------------\n");
            }
        }
            
        else if(op==4){
            int id;
            if(!isEmptyTree(tree)){
                printf("------------------------ EXCLUIR -------------------------\n");
                
                printf("Insira o código da produção: \n");
                scanf("%d",&id);
                tree.root = deleteProd(tree.root,id);
                printf("----------------------------------------------------------\n");
            }
            else{
                printf("Árvore vazia.\n");
                printf("---------------------- REINICIANDO -----------------------\n");
            }
        }
        else if(op==5){
            if(!isEmptyTree(tree)){
                printf("------------------ IMPRIMINDO REGISTROS ------------------\n");
                
                print2D(tree.root);
                printf("----------------------------------------------------------\n");
            }
            else{
                printf("Árvore vazia.\n");
                printf("---------------------- REINICIANDO -----------------------\n");
            }
        }
                
        else if (op==6){
            if(!isEmptyTree(tree)){
                freeTree(tree.root);
                printf("----------------------- LISTA LIMPA ----------------------\n");
            }
            else{
                printf("Árvore vazia.\n");
                printf("---------------------- REINICIANDO -----------------------\n");
            }
        }
        else if(op==7){
            printf("---------------------- FINALIZANDO -----------------------\n");
            freeTree(tree.root);
            break;
        }
        else{
            printf("--------------------- OPÇÃO INVÁLIDA ---------------------\n");
        }
    }
    return 0;
}