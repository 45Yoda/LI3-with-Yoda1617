#ifndef _matriz_h_
#define _matriz_h_

#include "global.h"
#include "avl.h"
#include "contribuidor.h"
#include "artigo.h"
// Declaração do tipo da Estrutura
typedef void* Estrutura;

//Declaração da Estrututa reg
typedef struct reg *Registo;

//Função que inicializa toda a estrutura Registo alocando memoria para todos os seus componentes
Registo initReg();

/* Recebe um Registo r e um long id como argumento e retorna a avl de artigos que tem o primeiro numero de ID em comum com o fornecido*/
Avl getRegArtigos(Registo r, long id);

/* Recebe um Registo r e um long id como argumento e retorna a avl de contribuidores que tem o primeiro numero de ID em comum com o fornecido*/
Avl getRegContribuidores(Registo r, long id);

/*Recebe um Registo reg, o id do artigo e a estrutura do mesmo e insere esse artigo no Registo retornando-o atualizado*/
Registo insereRegArtigo(Registo reg, long id,void* estrutura);

/*Recebe um Registo reg, o id de um Contribuidor e uma estrutura e insere esse Contribuidor e sua estrutura no Registo retornando-o atualizado*/
Registo insereRegContribuidor(Registo reg,long id,void* estrutura);

/*Recebe um Registo reg, o id do artigo e a estrutura com a sua imformação e atualiza a informação do artigo do id dado*/ 
Registo atualizaRegArtigos(Registo reg, long id,void* estrutura);

/*Recebe um Registo reg, o id do Contribuidor e a sua estrutura de informção e atualiza com os dados recebidos a sua informação no Registo retornando-o*/
Registo atualizaRegContribuidores(Registo reg,long id,void* estrutura);

/* Dado um Registo e um id de um artigo retorna toda a informação armazenada desse artigo*/
void* getRegArtEstrutura(Registo reg, long id);

/* Dado um Registo e um id de um Contribuidor retorna toda a informação armazenada desse Contribuidor*/
void* getRegContEstrutura(Registo reg, long id);

/* Recebe como argumento um artigo e liberta toda a memória que estava a ser ocupado por aquela estrutura Reg*/
void freeReg(Registo reg);

/* Recebe como argumento o Registo e retorna o numero total de artigos na estrutura*/
long totalRegElemsArtigos(Registo reg);

/* Recebe como argumento o Registo e retorna o numero total de Contribuidores na estrutura*/
long totalRegElemsCont(Registo reg);

/* Recebe como argumento o Registo e um indice e retorna o numero total de Contribuidores com o ID iniciado com aquele indice na estrutura*/
int totalIndElemsCont(Registo reg,int indice);

/* Recebe um Registo reg e clona-o para o Registo new retornando-o*/
Registo cloneReg(Registo reg, Registo new);


#endif
