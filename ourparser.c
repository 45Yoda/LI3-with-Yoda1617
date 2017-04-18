#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include "./headers/ourparser.h"
#include "./headers/artigo.h"

void parseFinal(long idArt,char* title,char* timestamp,long idRev,char* username,long idAutor,long wcount,long bcount,Avl a){
    void* art;
    int c;
    art= (Artigo) getAvlEstrutura(a,idArt);
    //TODO fazer funçoes dentro do artigo.c que façam isto;
    setTitulo(art,title);
    //printf("%s\n",getTitulo(art));
    int i = getN(art);
    setTimeStamp(art,timestamp,i);
    //setAutores(art,username,i);
    //setAutId(art,idAutor,i);
    setRevId(art,idRev,i);
    //a->tree->info->bytes=bcount;
    //a->tree->info->words=wcount;

    incrN(art); //funcemina


    //printf("----------------------------------------------\n" );

}

void parseText(xmlDocPtr doc,xmlNodePtr cur, long idArt,char* title,char* timestamp,long idRev,char* username, long idAutor,Avl a){
    long wcount=0;
    long bcount=0;
    for(cur=cur->xmlChildrenNode;cur;cur=cur->next){
        if((!xmlStrcmp(cur->name,(const xmlChar *) "text")));
    }
    parseFinal(idArt,title,timestamp,idRev,username,idAutor,wcount,bcount,a);
}
/*
long wcount(String str){

}*/


void parseContributor(xmlDocPtr doc, xmlNodePtr cur,long idArt,char* title,char* timestamp,long idRev, Avl a){

    long idAutor;
    char *username;
    xmlNodePtr aux;
    int artigos = 0;

    aux = cur->parent;

    for(cur= cur->xmlChildrenNode; cur;cur = cur->next){

        if(!xmlStrcmp(cur->name,(const xmlChar *)"username"))
            username = (char*) xmlNodeListGetString(doc,cur->xmlChildrenNode,1);

        if(!xmlStrcmp(cur->name,(const xmlChar *) "id"))
            idAutor = atol((char*) xmlNodeListGetString(doc,cur->xmlChildrenNode,1));
    }
    parseText(doc,aux,idArt,title,timestamp,idRev,username,idAutor,a);
    return;
}


void parseRevision(xmlDocPtr doc, xmlNodePtr cur,long idArt,char* title,Avl a){
    char* timestamp;
    long idRev;

    for(cur=cur->xmlChildrenNode;cur;cur=cur->next){
        if(!xmlStrcmp(cur->name,(const xmlChar *) "id"))
            idRev= atol((char*) xmlNodeListGetString(doc,cur->xmlChildrenNode,1));
        if((!xmlStrcmp(cur->name,(const xmlChar *) "timestamp")))
            timestamp=(char*) xmlNodeListGetString(doc,cur->xmlChildrenNode,1);
        if((!xmlStrcmp(cur->name,(const xmlChar *) "contributor")))
            parseContributor(doc,cur,idArt,title,timestamp,idRev,a);
        }

    return;
}


void parseDoc(int i,char *docname,int argc, Avl a){

    long idArt;
    clock_t tpf;

    xmlChar *id;
    xmlChar *title;
    xmlDocPtr doc;
    xmlNodePtr cur;
    xmlNodePtr aux;


    tpf =clock();

    doc = xmlParseFile(docname);

    tpf =clock() -tpf;

    printf("Demorou %f segundos a ler\n",((float)tpf)/CLOCKS_PER_SEC);

    if (doc == NULL){
        fprintf(stderr,"Document not parsed sucessfully. \n");
        return;
    }

    cur = xmlDocGetRootElement(doc);

    if(cur==NULL){
        perror("Empty document\n"); //usar perror funciona?
        xmlFreeDoc(doc);
        return;
    }

    cur = cur->xmlChildrenNode;
    cur = cur->next;

    for(cur;cur!=NULL;cur=cur->next){
        aux=cur;
        if(!xmlStrcmp(cur->name,(const xmlChar *) "page")){
            for(cur=cur->xmlChildrenNode; cur; cur= cur->next){

                if((!xmlStrcmp(cur->name,(const xmlChar *) "title"))){
                    title = xmlNodeListGetString(doc,cur->xmlChildrenNode,1);

                }

                if((!xmlStrcmp(cur->name,(const xmlChar *) "id"))){
                    idArt=atol((char*) xmlNodeListGetString(doc,cur->xmlChildrenNode,1));

                    a=insertAvl(a,idArt);

                    }
                if((!xmlStrcmp(cur->name,(const xmlChar *) "revision"))){
                    parseRevision(doc,cur,idArt,title,a);
                }

            }
        }

        cur=aux->next;
        //printf("%s = %ld\n",title,idArt);

    }
    xmlFreeDoc(doc);
    return;
}


long contaArt(Avl a, NODO n) {
    long t=0;
    if (n!=NULL){
        void* artigo;
        long id = getId(n);
        artigo = getAvlEstrutura(a,id);
        t=getN(artigo)+contaArt(a,getNodoEsq(n))+contaArt(a,getNodoDir(n));
    }
    return t;
}

long all_articles( Avl a ){
    long tot=0;
    if (a!=NULL){
        NODO n=getNodo(a);
        tot=contaArt(a,n);
    }
    return tot;
}

//-----------------------------------------------
//esta tambem nao // come nos 19 artigos
long unicosArt(Avl a, NODO n) {
    long t=0;
    if (n!=NULL){
        t=1+unicosArt(a,getNodoEsq(n))+unicosArt(a,getNodoDir(n));
    }
    return t;
}

long unique_articles( Avl a){
    long tot=0;
    if (a!=NULL){
        NODO n=getNodo(a);
        tot=unicosArt(a,n);
    }
    return tot;
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

int main(int argc, char **argv){
    int i;
    char *docname;
    clock_t tpf;

    if(argc <= 1){
        perror("Uso incorrecto\n");
        return 0;
    }
    Avl a = initAvl();

    tpf =clock();
    for(i=1;argc>1;argc--,i++){
        docname=argv[i];
        parseDoc(i,docname,argc,a);
    }
    printf("caralho\n");
    long nome = all_articles(a);
    printf("Total: %ld\n",nome);
    nome = unique_articles(a);
    printf("artigos unicos: %ld\n",nome);
    nome = all_revisions(a);
    printf("revisoes: %ld\n",nome);


    ////29128
    int z=0;
    Artigo art = getAvlEstrutura(a,29128);
    char* t = getTitulo(art);
    printf("%s\n",t);
    int nn = getN(art);
    printf("%d\n", nn);
    char**  tim=malloc(nn*sizeof(char*));
    //char** aut=malloc(nn*sizeof(char*));
    //long* autid=malloc(nn*sizeof(long*));
    long* revid=malloc(nn*sizeof(long*));
    getTimeStamp (art,tim);
//    getAutores(art,aut);
//    getAutId(art,autid);
    getRevId(art,revid);
    for(z=0;z<nn;z++){
        printf("%s\n",tim[z]);
//        printf("%s\n",aut[z]);
//        printf("%lu\n",autid[z]);
        printf("%lu\n",revid[z]);
        printf("------------------------\n");
    }
    tpf =clock() -tpf;
    printf("Demorou %f segundos a ler\n",((float)tpf)/CLOCKS_PER_SEC);
    return 1;
}
