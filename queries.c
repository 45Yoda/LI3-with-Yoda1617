#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include "./headers/ourparser.h"
#include "./headers/artigo.h"
#include "./headers/registo.h"
#include "./headers/contribuidor.h"
#include "./headers/arraydinamico.h"



Registo init(){
    Registo r = initReg();
    return r;
}

Registo load(Registo reg,int nsnaps, char* snaps_paths[]){
    reg=parser(reg,nsnaps,snaps_paths);
    return reg;
}

int main(int argc,char **argv){
    Registo r=init();
    r=load(r,argc,argv);
    return 0;
}

//interrogação nº1 total artigos
//feita
void contaArtigos(long id,Artigo art,long* soma){
    *soma +=getN(art);
}

long all_Articles(Registo reg){
    long i,t=0;
    for(i=0;i<10;i++){
        Avl a = getRegArtigos(reg,i);
        foreachAvl(a,(Funcao2) contaArtigos,&t);
    }
    return t;
}


//interrogação nº2 artigos unicos
// feita
long unique_articles(Registo reg){
    return totalRegElemsArtigos(reg);
}

//interrogação nº3 total de revisoes
//feita
void contaRev(Avl a,Artigo art,long* soma) {
    int i,c=1;
    long *revid=malloc(getN(art)*sizeof(long*));
    getRevId(art,revid);
    for (i=0;i<getN(art)-1;i++)
        if (revid[i]!=revid[i+1]) c++;
    *soma += c;
    free(revid);
}

long all_revisions(Registo reg) {
    long i,t=0;
    for(i=0;i<10;i++){
        Avl a = getRegArtigos(reg,i);
        foreachAvl(a,(Funcao2) contaRev,&t);
    }
    return t;
}


//interrogação nº4 que retorna o top 10 contribuidores
//Feita:
void initLongArray(long* top,int n) {
    int i;
    for(i=0;i<n;i++)
        top[i]=0;
}


void insereCont(long id, long cont,long* top){
    int i;
    long aux;
    top[9]=cont;
    top[19]=id;
    for (i=8;i>=0 && (top[i]<top[i+1] || (top[i]==top[i+1] && top[i+11]<top[10]));i--) {
            aux=top[i+1];
            top[i+1]=top[i];
            top[i]=aux;
            aux=top[i+11];
            top[i+11]=top[i+10];
            top[i+10]=aux;
    }
}


void checkCont (long id,Contribuidor con,long* topContId){
    long cont = getCont(con);
    if (cont> topContId[9] || (cont==topContId[9] && id>topContId[19]))
        insereCont(id,cont,topContId);
}

long* removeCont (long* top) {
    int i;
    long* t;
    for (i=0;i<10;i++)
        t[i]=top[i+10];
    return t;
}

long* top_10_contributors(Registo reg) {
    long* topContId= malloc(sizeof(long*));
    int i;
    initLongArray(topContId,20);
    for(i=0;i<10;i++){
        Avl a = getRegContribuidores(reg,i);
        foreachAvl(a,(Funcao2) checkCont,topContId);
        }
    long* t= removeCont(topContId);
    free(topContId);
    return t;
}
//interrogação nº5 que retorna o username de um contribuidor com determinado id
//feita:
char* contributor_name(long contributor_id, Registo reg){
    void* cont = getRegContEstrutura(reg,contributor_id);
    char* user = malloc(sizeof(char*));
    getUsername(cont, user);
    return user;
}


//interrogaçao nº6
//Feita:
void insereBytes(long id, long bytes,long* top){
    int i;
    long aux;
    top[19]=bytes;
    top[39]=id;
    for (i=18;i>=0 && (top[i]<top[i+1] || (top[i]==top[i+1] && top[i+21]<top[20]));i--) {
            aux=top[i+1];
            top[i+1]=top[i];
            top[i]=aux;
            aux=top[i+21];
            top[i+21]=top[i+20];
            top[i+20]=aux;
    }
}


void checkBytes (long id,Artigo art,long* topArt){
    long bytes = getBytes(art);
    if (bytes> topArt[19] || (bytes==topArt[9] && id>topArt[19]))
        insereBytes(id,bytes,topArt);
}

long* removeBytes (long* top) {
    int i;
    long* t;
    for (i=0;i<20;i++)
        t[i]=top[i+20];
    return t;
}

long* top_20_largest_articles(Registo reg){
    long* topArt= malloc(sizeof(long*));
    int i;
    initLongArray(topArt,40);
    for(i=0;i<10;i++){
        Avl a = getRegArtigos(reg,i);
        foreachAvl(a,(Funcao2) checkBytes,topArt);
        }
    long* t= removeBytes(topArt);
    free(topArt);
    return t;
}
//interrogação nº7 que retorna o titulo de um artigo com determinado id
//feita
char* article_title(long id,Registo reg) {
    void* artigo = getRegArtEstrutura(reg,id);
    return getTitulo(artigo);
}

//interrogação nº 8
// Feita:

void insereWords(long id, long words,long* top){
    int i;
    long aux;
    int n=top[0];
    top[n]=words;
    top[n+n]=id;
    for (i=n-1;i>0 && (top[i]<top[i+1] || (top[i]==top[i+1] && top[i+n+1]<top[i+n]));i--) {
            aux=top[i+1];
            top[i+1]=top[i];
            top[i]=aux;
            aux=top[i+n+1];
            top[i+n+1]=top[i+n];
            top[i+n]=aux;
    }
}


void checkWords (long id,Artigo art,long* topWords){
    long words = getWords(art);
    int n = topWords[0];
    if (words> topWords[n] || (words==topWords[n] && id>topWords[n+n]))
        insereWords(id,words,topWords);
}

long* removeWords (long* top,int n) {
    int i;
    long* t;
    for(i=0;i<n*2;i++)
        top[i]=top[i+1];
    for (i=0;i<n;i++)
        t[i]=top[i+n];
    return t;
}

long* top_N_articles_with_more_words(int n,Registo reg){
    long* topWords= malloc(n*2*sizeof(long*));
    int i;
    initLongArray(topWords,n*2+1);
    topWords[0]=n;
    for(i=0;i<10;i++){
        Avl a = getRegArtigos(reg,i);
        foreachAvl(a,(Funcao2) checkWords,topWords);
        }
    long* t= removeWords(topWords,n);
    free(topWords);
    return t;
}

//interrogaçao nº9
//insertArray nao funciona
/*void isPrefix (long id,Artigo art,Array a) {
    char* title = getTitulo(art);
    char* prefix;
    *prefix=getNameArray(a,0);
    if ((strncmp(prefix,title,strlen(prefix)))==0) {
        a=insertArray(a,title);
    }
}

char** titles_with_prefix(char* prefix,Registo reg) {
    Array a = initArray(2);
    a=insertArray(a,prefix);
    int i;
    for(i=0;i<10;i++) {
        Avl a = getRegArtigos(reg,i);
        foreachAvl(a,(Funcao2) isPrefix,a);
    }
    a = insertArray(a,NULL);
    char** t=cloneArray(a);
    freeArray(a);
    return t;
}*/

//interrogação nº10 que retorna o timestamp de uma certa revisão de um artigo
//feita
char* article_timestamp(long article_id,long revision_id,Registo reg) {
    void* artigo = getRegArtEstrutura(reg,article_id);
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
