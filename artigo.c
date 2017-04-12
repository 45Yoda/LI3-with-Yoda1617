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

void getTitulo (Artigo a,char* t) {
	t=strdup(a->titulo);
}

void setTitulo(Artigo a, char* title){
	a->titulo = title;
}

int getN(Artigo a){
	return a->n;
}

void incrN(Artigo a){
	 a->n++;
}

//se deu segmentation fault é pq és burro
void getTimeStamp(Artigo a, char* t[]){
	int b=getN(a),i;
	for(i=0;i<b;i++)
		t[i]=strdup(a->timestamp[i]);
}

void setTimeStamp(Artigo a, char* timestamp,int pos){
	a->timestamp[pos] = timestamp;
	for(int i=0;i<pos;i++)
	printf("%s\n", a->timestamp[i]);
}

void getAutores(Artigo a,char* aut[]) {
	int b=getN(a),i;
	for(i=0;i<b;i++)
		aut[i]=strdup(a->autores[i]);
}

void setAutores(Artigo a, char* autor, int pos){
	a->autores[pos]=autor;
	printf("%s\n",a->autores[pos]);
}

void getAutId(Artigo a,long c[]){
	int b=getN(a),i;
	c=(long*)malloc(b*sizeof(long));
	for(i=0;i<b;i++)
		c[i]=a->autId[i];
}

void setAutId(Artigo a, long id, int pos){
	a->autId[pos]=id;
	printf("%ld\n",a->autId[pos]);
}

long getBytes(Artigo a){
	return a->bytes;
}

void setBytes(Artigo a, long bytes){
	a->bytes=bytes;
}

long getWords(Artigo a){
	return a->words;
}

void setWords(Artigo a, long words){
	a->words=words;
}
