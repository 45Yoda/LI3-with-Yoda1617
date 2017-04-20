#ifndef _matriz_h_
#define _matriz_h_

#include "global.h"

typedef void* Estrutura;


//Declaração do tipo Matriz;
typedef struct mat *Matriz;

Matriz initMatriz();

//Estrutura getMatrizContributores(Matriz m, int i);
//Avl getMatrizArtigos(Matriz m, int i);
Estrutura getMatrizEstrutura(Matriz m,int linha, int coluna);






#endif
