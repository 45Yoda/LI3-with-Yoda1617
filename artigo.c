#include "artigo.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 64
/*1- todos os artigos (contar i's)
2-artigos unicos (contar nodos)
3-nr revisoes (timestamps diferentes)
4- autores mais revisoes (guardar autores e revisores de cada artigo)
5-autor com determinado id
6-artigos mais bytes
7-artigo com um id
8-mais words( conta ultima revisao)
9-artigos com prefixo (conta titulo ultima revisão)
10-timestamp certa revisao de um artigo
*/

struct artigo {
	char* titulo; //atualizar a cada revisao
	int n; //nr de vezes que artigo aparece
	char** timestamp; //guarda todos os timestamps por ordem de revisao
	char** autores; //autores de todas as revisoes
	long* autId; // id dos autores
	long bytes; //atualizar a cada revisao
	long words; //atualizar a cada revisao
};


Artigo init_Artigo (int size) {
	Artigo novo = (Artigo) malloc(sizeof(struct artigo));
	novo->titulo=NULL;
	novo->n=0;
	novo->timestamp=malloc(size *sizeof(char*));
	novo->autores=malloc(size *sizeof(char*));
	novo->autId=malloc(size *sizeof(long));
	for(int i=0; i<size;i++){
		novo->timestamp[i]=malloc(MAXSIZE);
		novo->autores[i]=malloc(MAXSIZE);
	}
	novo->bytes=0;
	novo->words=0;
}

char* getTitulo (Artigo a) {
	return a->titulo;
}

int getN(Artigo a) {
	return a->n;
}

void getTimeStamp(Artigo a, char* t[]){
	int b=getN(a),i;
	for(i=0;i<b;i++)
		strcpy(t[i],a->timestamp[i]);
}

void getAutores(Artigo a,char* aut[]) {
	int b=getN(a),i;
	for(i=0;i<b;i++)
		strcpy(aut[i],a->autores[i]);
}

void getAutId(Artigo a,long c[]){
	int b=getN(a),i;
	for(i=0;i<b;i++)
		c[i]=a->autId[i];
}

long getBytes(Artigo a){
	return a->bytes;
}

long getWords(Artigo a){
	return a->words;
}
