#include "./headers/contribuidor.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

struct contribuidor{
    char* username;
    int cont;
};

Contribuidor initContribuidor(){
    Contribuidor new = (Contribuidor) malloc(sizeof(struct contribuidor));
    new->username = "1";
    new->cont = 0;
    return new;
}

char* getUsername(Contribuidor c){
    return c->username;
}

void setUsername(Contribuidor c,char* user){
    c->username = user;
}

int getCont(Contribuidor c){
    return c->cont;
}

void incrCont(Contribuidor c){
    c->cont+=1;
}
