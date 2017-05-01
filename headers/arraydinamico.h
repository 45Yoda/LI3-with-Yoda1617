#ifndef _arraydinamico_h_
#define _arraydinamico_h_

#include "global.h"

//Declaração da Estrutura do Array dinamico
typedef struct array *Array;

/*Inicialização do Array que recebe como argumento um int com o seu tamanho inicial*/
Array initArray(int initialSize);

/* Dado o array e um char* str insere este mesmo ao array */
Array insertArray(Array a,char* str);

/* Dado o array e um char*val retorna True se existir esse valor no arrayy, False caso contrário */
Boolean existeArray(Array a,char* val);

/* Liberta toda a memória e dados utilizados pelo array */
void freeArray(Array a);

/* Dado o array devolve a posição atual no array*/
int getPosArray(Array a);

/* Dado o array e um int retorna o valor nessa posição no array*/
char* getNameArray(Array a,int pos);

/* Dado o array cria um clone do mesmo */
char** cloneArray(Array a);

#endif
