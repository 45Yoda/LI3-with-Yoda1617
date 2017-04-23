#include <stdlib.h>
#include <string.h>

#include "./headers/arraydinamico.h"

struct array{
    char** titles;
    size_t used;
    size_t size;
};

Array initArray(size_t initialSize){
    Array a = (Array) malloc(sizeof(struct array));
    a->titles = (char**) malloc(initialSize*sizeof(char*));
    a->used = 0;
    a->size = initialSize;
    return a;
}

Array insertArray(Array a,char* str){
    if(a->used == (a->size -2)){
        a->size *=2;
        a->titles = realloc(a->titles,a->size * sizeof(char*));
    }
    a->titles[a->used++]= strdup(str);
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
    for(i=0;i<a->used;i++){
        free(a->titles[i]);
    }
    free(a->titles);
    free(a);
}

int getPosArray(Array a){
    return a->used;
}

char* getNameArray(Array a,int pos){
    char* new = strdup(a->titles[pos]);
    return new;
}
