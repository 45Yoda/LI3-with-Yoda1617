#ifndef _matriz_h_
#define _matriz_h_

#include "global.h"
#include "avl.h"
#include "contribuidor.h"
#include "artigo.h"

typedef void* Estrutura;


//Declaração do tipo Matriz;
typedef struct reg *Registo;

Registo initReg();

//Estrutura getMatrizContributores(Matriz m, int i);
//Avl getMatrizArtigos(Matriz m, int i);
Avl getRegArtigos(Registo r, long id);

Avl getRegContribuidores(Registo r, long id);

Registo insereRegArtigo(Registo reg, long id,void* estrutura);

Registo insereRegContribuidor(Registo reg,long id,char* user);

Registo atualizaRegArtigos(Registo reg, long id,void* estrutura);

Registo atualizaRegContribuidores(Registo reg,long id,void* estrutura);

void* getRegArtEstrutura(Registo reg, long id);

void* getRegContEstrutura(Registo reg, long id);

void freeReg(Registo reg, Funcao f);

long totalRegElemsArtigos(Registo reg);

long totalRegElemsCont(Registo reg);

int totalIndElemsCont(Registo reg,int indice);

Registo cloneReg(Registo reg, Registo new);

#endif
