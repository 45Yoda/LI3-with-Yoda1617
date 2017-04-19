#ifndef _matriz_h_
#define _matriz_h_

#include "global.h"

typedef void* Estrutura;



//Declaração do tipo Matriz;

typedef struct matrizVal *MatVal;


//Declaração do tipo Matriz;
typedef struct mat *Matriz;

Matriz initMatriz();

Estrutura getMatrizEstrutura(Matriz m,int linha, int coluna);






#endif
