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

/*void contaContribuicoes(long id,Contribuidor c,int* soma){
	*soma +=getCont(c);
}*/

Registo insereRegArtigo(Registo reg, long id,void* estrutura){
	int i = firstDigit(id);
	reg->artigos[i] = insertAvl(reg->artigos[i],id,estrutura);
	return reg;
}

/*
 * Insere um contribuidor no registo.
 * Se o contribuidor ainda não existir no registo, insere-o, caso contrário
 * Substitui a informacao.
 */
Registo insereRegContribuidor(Registo reg,long id,char* user){
	int i = firstDigit(id);
	Avl c = reg->contribuidores[i];
	Contribuidor con =getAvlEstrutura(reg->contribuidores[i],id);
	if(!con){
		con = initContribuidor(user);
		setUsername(con,user);
		incrCont(con);
		reg->contribuidores[i]=insertAvl(reg->contribuidores[i],id,con);
	}
	else{
		incrCont(con);
		reg->contribuidores[i]=atualizaAvl(reg->contribuidores[i],id,con);

	}

	// Se NULL -> inseria
	// Senao -> substituia
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

void freeReg(Registo reg, Funcao f){
	int i;

	for(i=0;i<SIZE;i++){
		freeAvl(reg->artigos[i],f);
		freeAvl(reg->contribuidores[i],f);
	}
	free(reg);
}

Registo getReg () {

}
int firstDigit(long value) {
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
