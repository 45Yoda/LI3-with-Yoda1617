#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "./headers/arraydinamico.h"

struct array{
    char** titles;
    long used;
    long size;
};

Array initArray(int initialSize){
    Array a = (Array) malloc(sizeof(struct array));
    a->titles = (char**) malloc(initialSize*sizeof(char*));
    a->used = 0;
    a->size = initialSize;
    return a;
}

Array insertArray(Array a,char* str){
    if(a->used >= (a->size *0.80)){
        a->size *=2;
        a->titles = realloc(a->titles,a->size * sizeof(char*));
    }

    a->titles[a->used++] = strdup(str);


    return a;
}

Boolean existeArray(Array a,char* val){
    int i;

    for(i=0;i<a->used;i++){
        if(strcmp(a->titles[i],val)==0) return true;
    }

    return false;
}

void freeArray(Array a){
    int i;

    for(i=0; i<a->used;i++){
        free(a->titles[i]);
    }

    free(a->titles);
    free(a);
}

int getPosArray(Array a){
    return a->used;
}

char* getNameArray(Array a,int pos){
    char* novo;

    if(pos > a->used) return NULL;
    novo=malloc((strlen(a->titles[pos]))*sizeof(char));

    strcpy(novo,a->titles[pos]);
    return novo;
}

char** cloneArray(Array a){
    int i=0;
    char** new = malloc((a->used+1) * sizeof(char *));

    for(i=0;i<a->used;i++){
        new[i] = strdup(a->titles[i]);
    }
    new[i] = NULL;

    return new;
}
