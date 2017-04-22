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


//exemplo de interrogaçao
/*
int x=0;
foreach(a,contaContribuicoes,&x);

*/

//interrogação nº4 que retorna o top 10 contribuidores

//top10 contribuidores
void initTop(long* top) {
    int i;
    for(i=0;i<10;i++)
        top[i]=0;
}


void insereCont(long id, long cont,long* top){
    int i,stop=0;
    long aux;
    top[9]=id;
    for (i=8;i>=0 && stop==0;i--) {
        void* con2 = getRegContEstrutura(reg,topContId[i]);
        if (cont>getCont(con2)) {
            aux=top[i+1];
            top[i+1]=top[i];
            top[i]=aux;
    }else stop=1;
    }
}


void checkCont (long id,Contribuidor con,long* topContId){
    long cont = getCont(con);
    void* con2 = getAvlEstrutura(firsDigit(topContId[9]),topContId[9]);
    if (cont> getCont(con2) || cont==top[9] && id>topContId[9])
        insereCont(id,cont,topContId);
}


long* top_10_contributors(Registo reg) {
    long* topContId= malloc(sizeof(long*));
    int i;
    initTop(top);
    for(i=0;i<10;i++){
        Avl a = getRegContribuidores(reg,i);
        foreachAvl(a,(Funcao2) checkCont,topContId);
        }
    return topContId;
}

//interrogação nº5 que retorna o username de um contribuidor com determinado id
//feita:
char* contributor_name(long contributor_id, Registo reg){
    void* cont = getRegContEstrutura(reg,contributor_id);
    char* user = malloc(sizeof(char*));
    getUsername(cont, user);
    return user;
}

//interrogação nº7 que retorna o titulo de um artigo com determinado id
//feita
char* article_title(long id,Registo reg) {
    void* artigo = getRegArtEstrutura(reg,id);
    return getTitulo(artigo);
}

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
