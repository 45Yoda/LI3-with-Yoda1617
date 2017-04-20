#ifndef _matriz_h_
#define _matriz_h_

#include "global.h"
#include "avl.h"

typedef void* Estrutura;


//Declaração do tipo Matriz;
typedef struct reg *Registo;

Registo initReg();

//Estrutura getMatrizContributores(Matriz m, int i);
//Avl getMatrizArtigos(Matriz m, int i);
Estrutura getRegEstrutura(Registo r, int key);

int firstDigit(long value);



#endif
