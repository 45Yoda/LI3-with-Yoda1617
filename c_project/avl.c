#include "./headers/avl.h"
#include <stdio.h>
#include <stdlib.h>
#include "./headers/artigo.h"

// Estrutura de um nodo da AVL
struct nodeAvl{
    long id;                      //inteiro com um valor
    void *info;                   //apontador para a estrutura
    int height;                   //inteiro com altura da árvore;
    struct nodeAvl *left;         //apontador para nodo da esquerda
    struct nodeAvl *right;        //apontador para nodo da direita
};

struct avl{
    NODO tree;
    int size;
};

//Funções privadas
static int heightAvl(NODO n);
static int max(int a, int b);
static int getBalance(NODO n);
static Boolean nodeSearch(NODO node,Valor v);
static NODO newNode(NODO node,Valor ident,void* estrutura);
static NODO rotateRight(NODO);
static NODO rotateLeft(NODO);
static NODO atualizaNode (NODO node, long value, Estrutura estrutura);
static NODO nodeInsert(NODO node,Valor ident,Estrutura estrutura);
static NODO cloneTree (NODO node, NODO new);
static NODO foreachNode(NODO n,Funcao2 func,void* dados);
static Estrutura getNodeEstrutura(NODO node, Valor value);
static void freeTree(NODO node, Funcao f);

//Inicializa a estrutura da Avl
Avl initAvl(){
    Avl a = malloc(sizeof(struct avl));
    a->tree = NULL;
    a->size = 0;
    return a;
}

//Insere uma nova estrutura numa dada Avl tendo como referência um Valor
Avl atualizaAvl(Avl a, long value, Estrutura estrutura){
    a->tree = atualizaNode(a->tree,value,estrutura);
    return a;
}

//Insere um valor numa Avl tendo como ponto de referência um Valor.
Avl insertAvl(Avl a, Valor val,Estrutura estrutura){
    a->tree = nodeInsert(a->tree,val,estrutura);
    a->size++;
    return a;
}


//Devolve um Bool que se refere a ter ou não encontrado um valor
Boolean avlSearch(Avl a, Valor v){
  if(a == NULL) return false;
  return nodeSearch(a->tree,v);
}

//Retorna o número de elementos da Avl.
int totalElems(Avl a){
    return a->size;
}

//Faz um clone de uma dada Avl.
Avl cloneAvl(Avl node, Avl new){
    new = (Avl) malloc(sizeof(struct avl));
    new->tree = cloneTree(node->tree,new->tree);
    new->size = node->size;
    return new;
}

//Devolve uma estrutura associada a um nodo de uma Avl.
Estrutura getAvlEstrutura(Avl node, Valor val){
    return getNodeEstrutura(node->tree,val);
}

//Função que retorna o nodo da raiz de uma dada Avl;
NODO getNodo(Avl a){
    NODO new;
    if(a->tree){
        new = (NODO) malloc(sizeof(struct nodeAvl));
        new->id = a->tree->id;
        new->info = a->tree->info;
        new->left = a->tree->left;
        new->right = a->tree->right;
    }else{
        new = NULL;
    }

    return new;
}

//Função que dado um NODO retorna o nodo que está a sua esquerda
NODO getNodoEsq(NODO n){
    NODO new;
    if(n->left){
        new = (NODO) malloc(sizeof(struct nodeAvl));
        new->id = n->left->id;
        new->info = n->left->info;
        new->left = n->left->left;
        new->right = n->left->right;
    }else{
        new = NULL;
    }
    return new;
}

//Função que dado um NODO retorna o nodo que está a sua direita
NODO getNodoDir(NODO n){
    NODO new;
    if(n->right){
        new = (NODO) malloc(sizeof(struct nodeAvl));
        new->id = n->right->id;
        new->info = n->right->info;
        new->left = n->right->left;
        new->right = n->right->right;
    }else{
        new = NULL;
    }
    return new;
}

//Função que dado um NODO retorna o seu id
long getId(NODO n){
    return n->id;
}

//Função que dado um NODO retorna o seu info
void* getInfo(NODO n){
    return n->info;
}

//Função que liberta a memória ocupada por uma dada Avl.
void freeAvl(Avl node, Funcao f){
    freeTree(node->tree,f);
    free(node);
}


//Função que liberta a memória ocupada por um determinado NODO
void freeNode(NODO node){
    if(node!=NULL)
        free(node);
}

//Função que devolve a altura da Avl.
static int heightAvl(NODO n){
    if(n==NULL)
        return 0;
    return n->height;
}

//Função para determinar o maior entre dois inteiros.
static int max(int a,int b){
    if(a>b) return a;
    else return b;
}

//Função que retorna o índice de balanceamento da Avl
static int getBalance(NODO n){
  if(n==NULL) return 0;
  return heightAvl(n->left) - heightAvl(n->right);
}

//Função auxiliar que faz a rotação da Avl à direita.
static NODO rotateRight(NODO n){
    NODO aux;
    if(!n || !n->left)
        return 0;
    aux=n->left;
    n->left=aux->right;
    aux->right=n;
    n->height = max(heightAvl(n->left),heightAvl(n->right))+1;
    aux->height = max(heightAvl(n->left),heightAvl(n->right))+1;
    return aux;
}

//Função auxiliar que faz a rotação da Avl à esquerda.
static NODO rotateLeft(NODO n){
    NODO aux;
    if(!n || !n->right)
        return 0;
    aux=n->right;
    n->right=aux->left;
    aux->left=n;
    n->height = max(heightAvl(n->left),heightAvl(n->right))+1;
    aux->height=max(heightAvl(aux->left),heightAvl(aux->right))+1;
    return aux;
}





//Função que cria um novo nodo
static NODO newNode(NODO node,Valor ident,void* estrutura){
    node = (NODO) malloc(sizeof(struct nodeAvl));
    node->id = ident;
    node->info = estrutura;
    node->height= 1;
    node->left = NULL;
    node->right = NULL;
    return node;
}

static Boolean nodeSearch(NODO node,Valor v){
    if(node==NULL) return false;
    else{
        if(v == node->id) return true;
        else if(v < node->id) return nodeSearch(node->left,v);
        else return nodeSearch(node->right,v);
    }
}

void foreachAvl(Avl a,Funcao2 func,void* dados){
    if(a)
        foreachNode(a->tree,func,dados);
}

static NODO foreachNode(NODO n,Funcao2 func,void* dados){
    if (n) {
        func(n->id,n->info,dados);
        foreachNode(n->left,func,dados);
        foreachNode(n->right,func,dados);
    }
    return n;
}


static NODO nodeInsert(NODO node,Valor ident,Estrutura estrutura){
    int balance;
    if(node != NULL){
            if(ident < node->id)
                node->left = nodeInsert(node->left,ident,estrutura);
            else if(ident > node->id)
                node->right = nodeInsert(node->right,ident,estrutura);


        //Atualiza o peso
        node->height = max(heightAvl(node->left), heightAvl(node->right))+1;

        //Verifica balanceamento
        balance = getBalance(node);

        // Left Left Case

        if(balance>1 && (ident < node->left->id)) {
            return rotateRight(node);
}
        //Right Right Case
        if(balance< -1 && (ident>node->right->id)) {
            return rotateLeft(node);
}

        //Left Right Case
        if(balance > 1 && (ident > node->left->id)){
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        //Right Left Case
        if(balance < -1 && (ident < node->right->id)){
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
    }else node = newNode(node,ident,estrutura);

    return node;
}

static NODO cloneTree (NODO node, NODO new){

    if(node){
        new = malloc(sizeof(struct nodeAvl));
        new->id = node->id;
        new->height= node->height;
        new->info = NULL;
        new->left = cloneTree(node->left,new->left);
        new->right= cloneTree(node->right,new->right);
    }
    else new = NULL;

    return new;
}

static NODO atualizaNode (NODO node, long value, Estrutura estrutura){
    if(value == node->id){
        node->info = estrutura;
        return node;
    }
    else if(value < node->id) atualizaNode(node->left,value,estrutura);
    else atualizaNode(node->right,value,estrutura);

    return node;
}

static Estrutura getNodeEstrutura(NODO node, Valor value){
    if(node == NULL) return NULL;
    else{
        if(value == node->id) return node->info;
        else if (value < node->id) return getNodeEstrutura(node->left,value);
        else return getNodeEstrutura(node->right,value);
    }

}

static void freeTree(NODO node, Funcao f){
    if(node != NULL){
        freeTree(node->left,f);
        freeTree(node->right,f);
        if(node->info != NULL){
            f(node->info);
        }
        free(node);
    }
}
