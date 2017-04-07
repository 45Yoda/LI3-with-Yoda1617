#include "artigo.h"
#include <string.h>
#include <stdio.h>
/*1- todos os artigos (contar i's)
2-artigos unicos (contar nodos)
3-nr revisoes (timestamps diferentes)
4- autores mais revisoes (guardar autores e revisores de cada artigo)
5-autor com determinado id
6-artigos mais bytes
7-artigo com um id
8-mais palavras( conta ultima revisao)
9-artigos com prefixo (conta titulo ultima revisão)
10-timestamp certa revisao de um artigo
*/

struct artigo {
	long id;
	char* titulo; //atualizar a cada revisao
	int n; //nr revisoes
	char* timestamp[100]; //guarda todos os timestamps por ordem de revisao
	char* autores[100]; //autores de todas as revisoes
	long autId[100]; // id dos autores 
	long bytes; //atualizar a cada revisao
	long palavras; //atualizar a cada revisao
};

long getId(Artigo a) {
	return a->id;
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

long getPalavras(Artigo a){
	return a->palavras;
}