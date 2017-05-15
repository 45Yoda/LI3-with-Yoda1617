#ifndef _ourparser_h_
#define _ourparser_h_

#include "global.h"
#include "avl.h"
#include "artigo.h"
#include "registo.h"
#include "contribuidor.h"

/* Recebe um Registo reg, numero de argumentos argc e os snapshots e retorna a Estrutura com os dados retirados durante o parser aos snapshots */
Registo parser(Registo reg,int argc, char **argv);

#endif
