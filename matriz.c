#include "./headers/matriz.h"
#include "./headers/avl.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define ROWSIZE 10

struct mat{
	Avl artigos[ROWSIZE];
    Avl contribuidores[ROWSIZE];
};

Matriz initMatriz(){
    int i=0,j=0;
    Matriz m = malloc(sizeof(struct mat));

    for(j=0;j<ROWSIZE;j++){
        m->artigos[j] = initAvl();
        m->contribuidores[j] = initAvl();
    }

    return m;
}

Avl getMatrizArtigos(Matriz m, int i) {
	return m->artigos[i];
}

Avl getMatrizContributores(Matriz m, int i) {
	return m->contribuidores[i];
}

Estrutura getMatrizEstrutura(Matriz m,int linha, int coluna){
	if (linha == 0)
		return m->artigos[coluna];
	else return m->contribuidores[coluna];
}
