#ifndef _ourparser_h_
#define _ourparser_h_

#include "global.h"
#include "avl.h"
#include "artigo.h"
#include "registo.h"
#include "contribuidor.h"

Registo parser(Registo reg,int argc, char **argv);

void parseFinal(long idArt,char* title,char* timestamp,long idRev,long idAutor,char* username,Registo reg,long wcount,long bcount);




#endif
