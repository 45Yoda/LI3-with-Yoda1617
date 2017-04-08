#ifndef _avl_h_
#define _avl_h_


#include "global.h"


//Declaração do tipo AVL.
typedef struct avl *Avl;

//Declaração do nodo de uma AVL.
typedef struct nodeAvl *NODO;

typedef void* Estrutura;
typedef long Valor;


//Inicia a estrutura Avl.
Avl initAvl();

//Insere um valor num dado nodo de uma Avl.
Avl insertAvl(Avl a,int x);

//Devolve um Bool que se refere a ter ou não encontrado um valor
Boolean avlSearch(Avl a, Valor v);

//Remove um nodo de uma Avl, libertando o seu espaço.
void freeAvl(Avl a);

//Retorna o número de elementos da Avl.
int totalElems(Avl a);

//Função que retorna o nodo da raiz de uma dada Avl;
NODO getNodo(Avl a);

//Função que dado um NODO retorna o nodo que está a sua esquerda
NODO getNodoEsq(NODO n);

//Função que dado um NODO retorna o nodo que está a sua direita
NODO getNodoDir(NODO n);

//Função que liberta a memória ocupada por um determinado NODO
void freeNode(NODO node);

#endif
