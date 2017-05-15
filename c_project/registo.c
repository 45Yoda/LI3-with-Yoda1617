#include "./headers/registo.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

struct reg{
	Avl artigos[SIZE];
    Avl contribuidores[SIZE];
};


static int firstDigit(long value);

Registo initReg(){
    int i=0;
    Registo r = malloc(sizeof(struct reg));

    for(i=0;i<SIZE;i++){
        r->artigos[i] = initAvl();
        r->contribuidores[i] = initAvl();
    }

    return r;
}

Avl getRegArtigos(Registo r, long id){
	int i= firstDigit(id);
	return r->artigos[i];
}


Avl getRegContribuidores(Registo r, long id) {
	int i=firstDigit(id);
	return r->contribuidores[i];
}

Registo insereRegArtigo(Registo reg, long id,void* estrutura){
	int i = firstDigit(id);
	reg->artigos[i] = insertAvl(reg->artigos[i],id,estrutura);
	return reg;
}

Registo insereRegContribuidor(Registo reg,long id,void* estrutura){
	int i = firstDigit(id);
	reg->contribuidores[i] = insertAvl(reg->contribuidores[i],id,estrutura);
	return reg;
}

Registo atualizaRegArtigos(Registo reg, long id,void* estrutura){
	int i = firstDigit(id);
	reg->artigos[i] = atualizaAvl(reg->artigos[i],id,estrutura);
	return reg;
}

Registo atualizaRegContribuidores(Registo reg,long id,void* estrutura){
	int i = firstDigit(id);
	reg->contribuidores[i] = atualizaAvl(reg->contribuidores[i],id,estrutura);
	return reg;
}

long totalRegElemsArtigos(Registo reg){
	int i, total=0;
	for (i=0;i<SIZE;i++){
		total += totalElems(reg->artigos[i]);
	}
	return total;
}


long totalRegElemsCont(Registo reg){
	int i, total=0;
	for (i=0;i<SIZE;i++){
		total += totalElems(reg->contribuidores[i]);
	}
	return total;
}

int totalIndElemsArtigos(Registo reg,int indice){
	int total = 0;
	total += totalElems(reg->artigos[indice]);
	return total;
}

int totalIndElemsCont(Registo reg,int indice){
	int total = 0;
	total += totalElems(reg->contribuidores[indice]);
	return total;
}


Registo cloneReg(Registo reg, Registo new){
	int i;
	new = (Registo) malloc(sizeof(struct reg));
	for(i=0;i<SIZE;i++){
		new->artigos[i] = cloneAvl(reg->artigos[i],new->artigos[i]);
		new->contribuidores[i]=cloneAvl(reg->contribuidores[i],new->contribuidores[i]);
	}
	return new;
}

void* getRegArtEstrutura(Registo reg, long id){
	int i = firstDigit(id);
	return getAvlEstrutura(reg->artigos[i],id);
}

void* getRegContEstrutura(Registo reg, long id){
	int i = firstDigit(id);
	return getAvlEstrutura(reg->contribuidores[i],id);
}

void freeReg(Registo reg){
	int i;

	for(i=0;i<SIZE;i++){
		freeAvl(reg->artigos[i],(Funcao) freeArt);

		if(reg->contribuidores[i] != NULL){
			freeAvl(reg->contribuidores[i],(Funcao) freeCont);
		}
	}
	free(reg);
}

static int firstDigit(long value) {
	if (value >= 1000000000)
        value = value / 1000000000;
    if (value >= 100000000)
        value = value / 100000000;
    if (value >= 10000000)
        value = value / 10000000;
    if (value >= 1000000)
        value = value / 1000000;
    if (value >= 100000)
        value = value / 100000;
    if (value >= 10000)
        value = value / 10000;
    if (value >= 1000)
        value = value / 1000;
    if (value >= 100)
        value = value / 100;
    if (value >= 10)
        value = value/10;

    return value;
}
