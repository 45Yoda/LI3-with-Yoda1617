#ifndef _avl_h_
#define _avl_h_


#include "global.h"


//Declaração do tipo AVL.
typedef struct avl *Avl;

//Declaração do nodo de uma AVL.
typedef struct nodeAvl *NODO;

typedef void* Estrutura;
typedef long Valor;

typedef void(*Funcao)(void*);

typedef void(*Funcao2)(long,void*,void*);

//Inicia a estrutura Avl.
Avl initAvl();

//Insere um valor numa Avl tendo como ponto de referência um Valor.
Avl insertAvl(Avl a,Valor val,Estrutura estrutura);

//Faz um clone de uma dada Avl.
Avl cloneAvl(Avl node, Avl new);

//Insere uma nova estrutura numa dada Avl tendo como referência um Valor
Avl atualizaAvl(Avl a, Valor val, Estrutura estrutura);

//Devolve um Bool que se refere a ter ou não encontrado um valor
Boolean avlSearch(Avl a, Valor v);

//Retorna o número de elementos da Avl.
int totalElems(Avl a);

//Função que liberta a memória ocupada por uma dada Avl.
void freeAvl(Avl a, Funcao f);


void foreachAvl(Avl a,Funcao2 func,void* dados);

//Devolve uma estrutura associada a um nodo de uma Avl.
Estrutura getAvlEstrutura(Avl node,Valor val);

//Função que retorna o nodo da raiz de uma dada Avl;
NODO getNodo(Avl a);

//Função que dado um NODO retorna o nodo que está a sua esquerda
NODO getNodoEsq(NODO n);

//Função que dado um NODO retorna o nodo que está a sua direita
NODO getNodoDir(NODO n);

//Função que dado um NODO retorna o seu id
long getId(NODO n);

//Função que dado um NODO retorna o seu info
void* getInfo(NODO n);

//Função que liberta a memória ocupada por um determinado NODO
void freeNode(NODO node);

#endif
