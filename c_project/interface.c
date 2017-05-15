#include <stdlib.h>
#include <string.h>

#include "interface.h"
#include "./headers/global.h"
#include "./headers/registo.h"
#include "./headers/interpretador.h"
#include "./headers/ourparser.h"
#include "./headers/contribuidor.h"
#include "./headers/arraydinamico.h"

struct TCD_istruct{
    Registo reg;
};

static void contaArtigos(long id,Artigo art,long* soma);
static void contaRev(Avl a,Artigo art,long* soma);
static void initLongArray(long* top,int n);
static void insereCont(long id, long cont,long* top);
static void checkCont (long id,Contribuidor con,long* topContId);
static long* removeCont (long* top);
static void insereBytes(long id, long bytes,long* top);
static void checkBytes (long id,Artigo art,long* topArt);
static long* removeBytes (long* top);
static void insereWords(long id, long words,long* top);
static void checkWords (long id,Artigo art,long* topWords);
static long* removeWords (long* top,int n);
static void isPrefix (long id,Artigo art,Array a);
static void bubSort(char ** t, int used);


TAD_istruct init(){
    TAD_istruct qs = malloc(sizeof(struct TCD_istruct));
    qs->reg = initReg();
    return qs;
}

TAD_istruct load(TAD_istruct qs,int nsnaps,char * snaps_paths[]){
  // int estado = 1;
   qs->reg = parser(qs->reg,nsnaps,snaps_paths);
/*
   while(estado){
        estado = menuPrincipal(qs,nsnaps,snaps_paths,estado);
    }
*/
    return qs;
}

//interrogação nº1 total artigos
//feita
static void contaArtigos(long id,Artigo art,long* soma){
    *soma +=getN(art);
}

long all_articles(TAD_istruct qs){
    long i,t=0;
    for(i=0;i<10;i++){
        Avl a = getRegArtigos(qs->reg,i);
        foreachAvl(a,(Funcao2) contaArtigos,&t);
    }
    return t;
}

//interrogação nº2 artigos unicos
// feita
long unique_articles(TAD_istruct qs){
    return totalRegElemsArtigos(qs->reg);
}

//interrogação nº3 total de revisoes
//feita
static void contaRev(Avl a,Artigo art,long* soma) {
    int i,c=1;
    long *revid=malloc(getN(art)*sizeof(long*));
    int n=getN(art);
    if (n>1) {
    getRevId(art,revid);
    for (i=0;i<n-1;i++)
        if (revid[i]!=revid[i+1]) c++;
}
    *soma += c;
    free(revid);
}

long all_revisions(TAD_istruct qs) {
    long i,t=0;
    for(i=0;i<10;i++){
        Avl a = getRegArtigos(qs->reg,i);
        foreachAvl(a,(Funcao2) contaRev,&t);
    }
    return t;
}

//interrogação nº4 que retorna o top 10 contribuidores
//Feita:
static void initLongArray(long* top,int n) {
    int i;
    for(i=0;i<n;i++)
        top[i]=0;
}


static void insereCont(long id, long cont,long* top){
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


static void checkCont (long id,Contribuidor con,long* topContId){
    long cont = getCont(con);
    if (cont> topContId[9] || (cont==topContId[9] && id<topContId[19]))
        insereCont(id,cont,topContId);
}

static long* removeCont (long* top) {
    int i;
    long* t= malloc(10*sizeof(long));
    for (i=0;i<10;i++)
        t[i]=top[i+10];
    return t;
}

long* top_10_contributors(TAD_istruct qs) {
    long* topContId= malloc(sizeof(long*));
    int i;
    initLongArray(topContId,20);
    for(i=0;i<10;i++){
        Avl a = getRegContribuidores(qs->reg,i);
        foreachAvl(a,(Funcao2) checkCont,topContId);
        }
    long* t= removeCont(topContId);
    free(topContId);
    return t;
}

//interrogação nº5 que retorna o username de um contribuidor com determinado id
//feita:
char* contributor_name(long contributor_id, TAD_istruct qs){
    void* cont = getRegContEstrutura(qs->reg,contributor_id);
    if (cont) {
    char* user = malloc(sizeof(char*));
    getUsername(cont, user);
    return user;
}
    else return NULL;
}

//interrogaçao nº6
//Feita:
static void insereBytes(long id, long bytes,long* top){
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


static void checkBytes (long id,Artigo art,long* topArt){
    long bytes = getBytes(art);
    if (bytes> topArt[19] || (bytes==topArt[9] && id>topArt[19]))
        insereBytes(id,bytes,topArt);
}

static long* removeBytes (long* top) {
    int i;
    long* t = malloc(20*sizeof(long));
    for (i=0;i<20;i++)
        t[i]=top[i+20];
    return t;
}

long* top_20_largest_articles(TAD_istruct qs){
    long* topArt= malloc(sizeof(long*));
    int i;
    initLongArray(topArt,40);
    for(i=0;i<10;i++){
        Avl a = getRegArtigos(qs->reg,i);
        foreachAvl(a,(Funcao2) checkBytes,topArt);
        }
    long* t= removeBytes(topArt);
    free(topArt);
    return t;
}

//interrogação nº7 que retorna o titulo de um artigo com determinado id
//feita
char* article_title(long id,TAD_istruct qs) {
    void* artigo = getRegArtEstrutura(qs->reg,id);
    if (artigo!=NULL)
        return getTitulo(artigo);
    else return NULL;
}

//interrogação nº 8
// Feita:

static void insereWords(long id, long words,long* top){
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


static void checkWords (long id,Artigo art,long* topWords){
    long words = getWords(art);
    int n = topWords[0];
    if (words> topWords[n] || (words==topWords[n] && id>topWords[n+n]))
        insereWords(id,words,topWords);
}

static long* removeWords (long* top,int n) {
    int i;
    long* t=malloc(n*sizeof(long));
    for(i=0;i<n*2;i++)
        top[i]=top[i+1];
    for (i=0;i<n;i++)
        t[i]=top[i+n];
    return t;
}

long* top_N_articles_with_more_words(int n,TAD_istruct qs){
    long* topWords= malloc(n*2*sizeof(long*));
    int i;
    initLongArray(topWords,n*2+1);
    topWords[0]=n;
    for(i=0;i<10;i++){
        Avl a = getRegArtigos(qs->reg,i);
        foreachAvl(a,(Funcao2) checkWords,topWords);
        }
    long* t= removeWords(topWords,n);
    free(topWords);
    return t;
}

//interrogaçao nº9
static void isPrefix (long id,Artigo art,Array a) {
    char* title = getTitulo(art);
    char* prefix = getNameArray(a,0);
    if ((strncmp(prefix,title,strlen(prefix)))==0) {
        a=insertArray(a,title);
    }
}

char** titles_with_prefix(char* prefix, TAD_istruct qs) {
    int n = 0;

    Array a = initArray(2);
    a = insertArray(a, prefix);
    int i;
    for(i=0;i<10;i++) {
        Avl arv = getRegArtigos(qs->reg, i);
        foreachAvl(arv,(Funcao2) isPrefix,a);
    }
    n = getPosArray(a);
    char** t = cloneArray(a);

    bubSort(t,n);

    freeArray(a);
    return t;

}

static void bubSort(char ** t, int used){
	int i, j;
	char* temp = (char*) malloc(MAXSIZE* sizeof(char));
	for (i = 1; i < used; i++) {
      for (j = 1; j < used; j++) {
         if (strcmp(t[j-1], t[j]) > 0) {
            strcpy(temp, t[j-1]);
            strcpy(t[j-1], t[j]);
            strcpy(t[j],temp);
         }
      }
   }
}

//interrogação nº10 que retorna o timestamp de uma certa revisão de um artigo
//feita
char* article_timestamp(long article_id,long revision_id,TAD_istruct qs) {
    void* artigo = getRegArtEstrutura(qs->reg,article_id);
    long *revid=malloc(getN(artigo)*sizeof(long*));
    char* timeSt = NULL;
    int i;
    if (artigo) {
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
}
    return timeSt;
}

TAD_istruct clean(TAD_istruct qs){
    freeReg(qs->reg);

    return qs;
}
