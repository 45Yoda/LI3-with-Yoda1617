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
//Feita: 
void initTop(long* top,int n) {
    int i;
    for(i=0;i<10;i++)
        top[i]=0;
}


void insereCont(long id, long cont,long* top){
    int i,stop=0;
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
    if (cont> topContId[9] || cont==topContId[9] && id>topContId[9])
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
    initTop(topContId,20);
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

//interrogação nº7 que retorna o titulo de um artigo com determinado id
//feita
char* article_title(long id,Registo reg) {
    void* artigo = getRegArtEstrutura(reg,id);
    return getTitulo(artigo);
}


//interrogaçao nº9
void insereArt(char* title,char** titulos){
    int i;
    printf("%s\n",title);
    for(i=1;titulos[i]!=NULL;i++);
    titulos[i]=malloc(sizeof(char*));
    titulos[i]=title;
    //printf("%s\n",*titulos[i]);
    titulos[i+1]=NULL;

}

void isPrefix (long id,Artigo art,char** titulos) {
    char* title = getTitulo(art);
    char* prefix=titulos[0];
    if ((strncmp(prefix,title,strlen(prefix)))==0) {
        insereArt(title,titulos);
    }
}

char** titles_with_prefix(char* prefix,Registo reg) {
    char** titulos = malloc(sizeof(char**));
    titulos[0]=strdup(prefix);
    titulos[1]=NULL;
    printf("%s\n",titulos[0]);
    int i;
    for(i=0;i<10;i++) {
        Avl a = getRegArtigos(reg,i);
        foreachAvl(a,(Funcao2) isPrefix,titulos);
    }
    char** t=titulos;
    free(titulos);
    return t;
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
