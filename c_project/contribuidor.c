#include "./headers/contribuidor.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

struct contribuidor{
    char* username;
    int cont;
};

Contribuidor initContribuidor(char * username){
    Contribuidor new = (Contribuidor) malloc(sizeof(struct contribuidor));
    new->username = strdup(username);
    new->cont = 1;
    return new;
}

void getUsername(Contribuidor c,char* new){
    strcpy(new,c->username);
}

void setUsername(Contribuidor c,char* user){
    c->username = user;
}

int getCont(Contribuidor c){
    return c->cont;
}

void incrCont(Contribuidor c){
    c->cont++;
}


void freeCont(Contribuidor c){
    free(c);
}
