#include "avl.h"

// Estrutura de um nodo da AVL
struct nodeAvl{
    long id;                      //inteiro com um valor
    void *info;                   //apontador para a estrutura
    int height;                   //inteiro com altura da árvore;
    struct nodeAvl *left *right;  //Apontadores para as Avl's da esquerda e da direita;
};

struct avl{
    NODO tree;
    int size;
};

//Funções privadas
static int heightAvl(NODO n);
static int max(int a, int b);
static int getBalance(NODO n);
static Avl rotateRight(Avl);
static Avl rotateLeft(Avl);
static int max(int a,int b);
static NODO newNode(NODO node,Valor ident,void *estutura);

//Inicializa a estrutura da Avl
Avl initAvl(){
    Avl a = malloc(sizeof(struct avl));
    a->tree = NULL;
    a->size = 0;
    return a;
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

//Função auxiliar que faz a rotação da Avl à direita.
static Avl rotateRight(NODO n){
    NODO aux;
    aux=n->left;
    n->left=aux->right;
    aux->right=n;
    n->height = max(heightAvl(n->left),heightAvl(n->right))+1;
    aux->height = max(heightAvl(n->left),heightAvl(n->right))+1;
    return aux;
}

//Função auxiliar que faz a rotação da Avl à esquerda.
static NODO rotateLeft(NODO n){
    Avl aux;
    aux=n->right;
    n->right=aux->left;
    aux->left=n;
    n->height = max(heightAvl(n->left),heightAvl(n->right))+1;
    aux->height=max(heightAvl(aux->left),heightAvl(aux->right))+1;
    return aux;
}

Boolean avlSearch(Avl a, Valor v){
    if(a == NULL) return false;
    return nodeSearch(a->tree,v);

}

//Função que cria um novo nodo
static NODO newNode(NODO node,Valor ident,void *estutura){
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
        else if(v < node->id) nodeSearch(node->left,v);
        else nodeSearch(node->right,v);
    }
}

static NODO nodeInsert(NODO node,Valor ident,Estutura est){
    int balance;

    if(node !=NULL){
        if(ident < node->id)
            node->left = nodeInsert(node->left,ident, est);
        else if(ident> node->id)
            node->right = nodeInsert(node->right,ident,est);
        else node->info = est;
    }

    //Atualiza o peso
    node->height = max(heightAvl(node->left), heightAvl(node->right))+1;

    //Verifica balanceamento
    bal = getBalance(node);

    // Left Left Case
    if(bal>1 && (ident < node->left->id)) return rotateRight(node);

    //Right Right Case
    if(bal< -1 && (ident<node->right->id)) return rotateLeft(node);

    //Left Right Case
    if(balance > 1 && (ident > node->left->id)){
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    //Right Left Case
    if(balance < -1)

}
