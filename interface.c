#include "./headers/avl.h"
#include <stdio.h>
#include <string.h>

//total = 59593
//uniq 19886
//uniq rev 40131

Avl init() {
	Avl a = initAvl();
	return a;
}

Avl load(Avl a, int nsnaps, char* snaps_paths[]) {
	a=parser(a,nsnaps,snaps_paths); // atual main do parser
	return a;
}

//-----------------------------------------
//esta funcemina!!!


long contaArt(Registo reg,Avl a, NODO n) {
    long t=0;
    if (n!=NULL){
        void* artigo;
        long id = getId(n);
        artigo = getRegArtEstrutura(reg,id);
        t=getN(artigo)+contaArt(reg,a,getNodoEsq(n))+contaArt(reg,a,getNodoDir(n));
    }
    return t;
}

long all_Articles(Registo reg){
    long i,t=0;
    for(i=0;i<10;i++){
        Avl a = getRegArtigos(reg,i);
        NODO n = getNodo(a);
        t+= contaArt(reg,a,n);
    }
    return t;

}

//-----------------------------------------------
//esta tambem nao // come nos 19 artigos

long unique_articles( Avl a){
    return totalRegElemsArtigos(reg);
}


//-------------------
//funciona
long contaRev(Avl a, NODO n) {
    long t=0;
    int i,c=1;
    if (n!=NULL){
        void* artigo;
        long id = getId(n);
        artigo = getAvlEstrutura(a,id);
        long *revid=malloc(getN(artigo)*sizeof(long*));
        getRevId(artigo,revid);
        for (i=0;i<getN(artigo)-1;i++) {
            if (revid[i]!=revid[i+1]) c++;
        }
        t= c+contaRev(a,getNodoEsq(n))+contaRev(a,getNodoDir(n));
        free(revid);
    }
    return t;
}

long all_revisions(Avl a) {
    long tot=0;
    if (a!=NULL){
        NODO n=getNodo(a);
        tot=contaRev(a,n);
    }
    return tot;
}

//------------------------------
//funcemina
char* procContributor (long id, NODO n,Avl a) {
    int c=-1;
    int i;
    char* cont=NULL;
    if (n!=NULL) {
        void* artigo=getAvlEstrutura(a,getId(n));
        long *autid=malloc(getN(artigo)*sizeof(long*));
        getAutId(artigo,autid);
        for (i=0;i<getN(artigo) && c==-1;i++) {
            if (autid[i]==id) c=i;
        }
        if (c!=-1) {
            char** nome = malloc(getN(artigo)*sizeof(char*));
            getAutores(artigo,nome);
            cont=nome[c];
        }
        else {
            char *esq,*dir;
            esq=procContributor(id,getNodoEsq(n),a);
            dir=procContributor(id,getNodoDir(n),a);

            if (esq!=NULL) cont=esq;
            else cont=dir;
        }
    }
    return cont;
}


char* contributor_name(long contributor_id, Avl a) {
    NODO n = getNodo(a);
    return procContributor(contributor_id,n,a);

}
//------------------------------------------
//funciona
char* article_title(long id, Avl a) {
    void* artigo = getAvlEstrutura(a,id);
    return getTitulo(artigo);
}


//---------------------
// funciona
char* article_timestamp(long article_id,long revision_id,Avl a) {
    void* artigo = getAvlEstrutura(a,article_id);
    long *revid=malloc(getN(artigo)*sizeof(long*));
    char* timeSt = NULL;
    int i;
    getRevId(artigo,revid);
    for (i=0;i<getN(artigo);i++) {
        if (revid[i]==revision_id) {
            char** times = malloc(getN(artigo)*sizeof(char*));
            getTimeStamp(artigo,times);
            timeSt = times[i];
            free(times);
            }
    }
    free(revid);
    return timeSt;
}
