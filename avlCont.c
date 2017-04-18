#include "./headers/avlCont.h"

#include <stdlib.h>

struct nodeAvlCont{
    long idAut;                      //inteiro com um valor
    char* username;                  //string com o username
    int cont;                          //numero de contribuições
    int height;                   //inteiro com altura da árvore;
    struct nodeAvlCont *left;
    struct nodeAvlCont *right;
};

struct avlCont{
    NODOCONT tree;
    int size;
};

//Funções privadas
static int heightAvlCont(NODOCONT n);
static int max(int a, int b);
static int getBalance(NODOCONT n);
static Boolean nodeSearch(NODOCONT node,Valor v);
static NODOCONT newNode(NODOCONT node,Valor ident,char* user);
static NODOCONT rotateRight(NODOCONT);
static NODOCONT rotateLeft(NODOCONT);
static NODOCONT atualizaNode (NODOCONT node, long value, char* user);
static NODOCONT nodeInsert(NODOCONT node,Valor ident,char* user);
static NODOCONT cloneTree (NODOCONT node, NODOCONT new);
static void freeTree(NODOCONT node, Funcao f);

//Inicializa a estrutura da Avl
AvlCont initAvlCont(){
    AvlCont a = malloc(sizeof(struct avlCont));
    a->tree = NULL;
    a->size = 0;
    return a;
}

//Insere uma nova estrutura numa dada Avl tendo como referência um Valor
AvlCont atualizaAvlCont(AvlCont a, long value, char* username){
    a->tree = atualizaNode(a->tree,value,username);
    return a;
}
//Insere um valor numa Avl tendo como ponto de referência um Valor.
AvlCont insertAvlCont(AvlCont a, Valor val, char* user){
    a->tree = nodeInsert(a->tree,val,user);
    a->size++;
    return a;
}

//Devolve um Bool que se refere a ter ou não encontrado um valor
Boolean avlSearchCont(AvlCont a, Valor v){
  if(a == NULL) return false;
  return nodeSearch(a->tree,v);
}

//Retorna o número de elementos da Avl.
int totalElemsCont(AvlCont a){
    return a->size;
}

//Faz um clone de uma dada Avl.
AvlCont cloneAvlCont(AvlCont node, AvlCont new){
    new = (AvlCont) malloc(sizeof(struct avlCont));
    new->tree = cloneTree(node->tree,new->tree);
    new->size = node->size;
    return new;
}


//Função que retorna o nodo da raiz de uma dada Avl;
NODOCONT getNodoCont(AvlCont a){
    NODOCONT new;
    if(a->tree){
        new = (NODOCONT) malloc(sizeof(struct nodeAvlCont));
        new->idAut = a->tree->idAut;
        new->username = a->tree->username;
        new->cont=a->tree->cont;
        new->left = a->tree->left;
        new->right = a->tree->right;
    }else{
        new = NULL;
    }

    return new;
}

//Função que dado um NODO retorna o nodo que está a sua esquerda
NODOCONT getNodoEsqCont(NODOCONT n){
    NODOCONT new;
    if(n->left){
        new = (NODOCONT) malloc(sizeof(struct nodeAvlCont));
        new->idAut = n->left->idAut;
        new->username = n->left->username;
        new->cont=n->left->cont;
        new->left = n->left->left;
        new->right = n->left->right;
    }else{
        new = NULL;
    }
    return new;
}

//Função que dado um NODO retorna o nodo que está a sua direita
NODOCONT getNodoDirCont(NODOCONT n){
    NODOCONT new;
    if(n->right){
        new = (NODOCONT) malloc(sizeof(struct nodeAvlCont));
        new->idAut = n->right->idAut;
        new->username = n->right->username;
        new->cont=n->right->cont;
        new->right = n->right->right;
    }else{
        new = NULL;
    }
    return new;
}

//Função que dado um NODO retorna o seu id
long getIdAut(NODOCONT n){
    return n->idAut;
}

//Função que dado um NODO retorna o seu info
char* getUsername(NODOCONT n){
    return n->username;
}

int getCont (NODOCONT n) {
    return n->cont;
}

//Função que liberta a memória ocupada por uma dada Avl.
void freeAvlCont(AvlCont node, Funcao f){
    freeTree(node->tree,f);
    free(node);
}


//Função que liberta a memória ocupada por um determinado NODO
void freeNodeCont(NODOCONT node){
    if(node!=NULL)
        free(node);
}

//Função que devolve a altura da Avl.
static int heightAvl(NODOCONT n){
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
static int getBalance(NODOCONT n){
  if(n==NULL) return 0;
  return heightAvl(n->left) - heightAvl(n->right);
}

//Função auxiliar que faz a rotação da Avl à direita.
static NODOCONT rotateRight(NODOCONT n){
    NODOCONT aux;
    aux=n->left;
    n->left=aux->right;
    aux->right=n;
    n->height = max(heightAvl(n->left),heightAvl(n->right))+1;
    aux->height = max(heightAvl(n->left),heightAvl(n->right))+1;
    return aux;
}

//Função auxiliar que faz a rotação da Avl à esquerda.
static NODOCONT rotateLeft(NODOCONT n){
    NODOCONT aux;
    aux=n->right;
    n->right=aux->left;
    aux->left=n;
    n->height = max(heightAvl(n->left),heightAvl(n->right))+1;
    aux->height=max(heightAvl(aux->left),heightAvl(aux->right))+1;
    return aux;
}




//Função que cria um novo nodo
static NODOCONT newNode(NODOCONT node,Valor ident,User username){
    node = (NODOCONT) malloc(sizeof(struct nodeAvlCont));
    node->idAut = ident;
    node->username;
    node->cont=1;
    node->height= 1;
    node->left = NULL;
    node->right = NULL;
    return node;
}

static Boolean nodeSearch(NODOCONT node,Valor v){
    if(node==NULL) return false;
    else{
        if(v == node->idAut) return true;
        else if(v < node->idAut) nodeSearch(node->left,v);
        else nodeSearch(node->right,v);
    }
}

static NODOCONT nodeInsert(NODOCONT node,Valor ident,char* user){
    int balance;

    if(node !=NULL){
        if(ident < node->idAut)
            node->left = nodeInsert(node->left,ident,user);
        else if(ident> node->idAut)
            node->right = nodeInsert(node->right,ident,user);
        else{node->username = user;node->cont+=1;}


    //Atualiza o peso
    node->height = max(heightAvl(node->left), heightAvl(node->right))+1;

    //Verifica balanceamento
    balance = getBalance(node);

    // Left Left Case
    if(balance>1 && (ident < node->left->idAut)) return rotateRight(node);

    //Right Right Case
    if(balance< -1 && (ident<node->right->idAut)) return rotateLeft(node);

    //Left Right Case
    if(balance > 1 && (ident > node->left->idAut)){
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    //Right Left Case
    if(balance < -1 && (ident >node->right->idAut) < 0){
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    }else node = newNode(node,ident,user);

    return node;
}

static NODOCONT cloneTree (NODOCONT node, NODOCONT new){

    if(node){
        new = malloc(sizeof(struct nodeAvlCont));
        new->idAut = node->idAut;
        new->height= node->height;
        new->username = NULL;
        new->left = cloneTree(node->left,new->left);
        new->right= cloneTree(node->right,new->right);
    }
    else new = NULL;

    return new;
}

static NODOCONT atualizaNode (NODOCONT node, long value, char* username){
    if(value == node->idAut){
        node->username=username;
        node->cont+=1;
        return node;
    }
    else if(value < node->idAut) atualizaNode(node->left,value,username);
    else atualizaNode(node->right,value,username);

    return node;
}


static void freeTree(NODOCONT node, Funcao f){
    if(node != NULL){
        freeTree(node->left,f);
        freeTree(node->right,f);
        if(node->username != NULL){
            f(node->username);
        }
        free(node);
    }
}
