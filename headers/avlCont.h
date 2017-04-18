#ifndef _avlCont_h_
#define _avlCont_h_


#include "global.h"


//Declaração do tipo AVL.
typedef struct avlCont *AvlCont;

//Declaração do nodo de uma AVL.
typedef struct nodeAvlCont *NODO;

typedef long Valor;
typedef char* User;

typedef void(*Funcao)(void*);

//Inicia a estrutura Avl.
AvlCont initAvlCont();

//Insere um valor numa Avl tendo como ponto de referência um Valor.
AvlCont insertAvl(AvlCont a,Valor val, User user);

//Faz um clone de uma dada Avl.
AvlCont cloneAvl(AvlCont node, AvlCont new);

//Insere uma nova estrutura numa dada Avl tendo como referência um Valor
AvlCont atualizaAvlCont(AvlCont a, Valor val, User user);

//Devolve um Bool que se refere a ter ou não encontrado um valor
Boolean avlSearchCont(Avl a, Valor v);

//Retorna o número de elementos da Avl.
int totalElems(AvlCont a);

//Função que liberta a memória ocupada por uma dada Avl.
void freeAvlCont(AvlCont a, Funcao f);

//Função que retorna o nodo da raiz de uma dada Avl;
NODO getNodoCont(AvlCont a);

//Função que dado um NODO retorna o nodo que está a sua esquerda
NODO getNodoEsqCont(NODO n);

//Função que dado um NODO retorna o nodo que está a sua direita
NODO getNodoDirCont(NODO n);

//Função que dado um NODO retorna o seu id
long getIdAut(NODO n);

//Função que dado um NODO retorna o seu username
char* getUsername(NODO n);

//Função que dado um NODO retorna o seu numero de contribuições
int getCont (NODO n);

//Função que liberta a memória ocupada por um determinado NODO
void freeNode(NODO node);

#endif
