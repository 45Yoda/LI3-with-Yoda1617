#include "./headers/matriz.h"
#include "./headers/avl.h"
#include "./headers/avlCont.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define LINESIZE 2
#define ROWSIZE 10

struct matrizVal{
    void* avl;
};

struct mat{
	MatVal matriz[LINESIZE][ROWSIZE];
};

Matriz initMatriz(){
    int i=0,j=0;
    Matriz m = malloc(sizeof(struct mat));
    for(i=0;i<LINESIZE;i++){
        for(j=0;j<ROWSIZE;j++){
            if(i==0){
                Avl a = initAvl();
                m->matriz[i][j] = malloc(sizeof(struct matrizVal));
                (m->matriz[i][j])->avl = a;
            }else{
                AvlCont b = initAvlCont();
                m->matriz[i][j] = malloc(sizeof(struct matrizVal));
                m->matriz[i][j]->avl = b;
            }
        }
    }
    return m;
}

EstruturaB getMatrizEstrutura(Matriz m,int linha, int coluna){
    return m->matriz[linha][coluna]->avl;
}
