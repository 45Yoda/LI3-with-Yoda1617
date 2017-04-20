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



void parseFinal(long idArt, char* title, char* timestamp, long idRev, long idAutor, char* username, Registo reg, long wcount, long bcount) {
    void* art;
    void* con;
    int c=0;
    art = getRegArtEstrutura(reg,idArt);
    con = getRegContEstrutura(reg, idAutor);

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
    //printf("%d\n",getN(art));
    incrN(art); //funcemina

    setUsername(con,username);
    incrCont(con);



    //printf("%d\n", getN(art));
    //printf("acaba\n");
    //printf("----------------------------------------------\n" );
}

void parseText(xmlDocPtr doc,xmlNodePtr cur, long idArt,char* title,char* timestamp,long idRev,long idAutor,char* username,Registo reg){
    long wcount=0;
    long bcount=0;
    for(cur=cur->xmlChildrenNode;cur;cur=cur->next){
        if((!xmlStrcmp(cur->name,(const xmlChar *) "text")));
    }
    parseFinal(idArt,title,timestamp,idRev,idAutor,username,reg,wcount,bcount);
}
/*
long wcount(String str){

}
*/


void parseContributor(xmlDocPtr doc, xmlNodePtr cur,long idArt,char* title,char* timestamp,long idRev, Registo reg){
    void* con;
    long idAutor;
    xmlChar* username;
    char *user;
    xmlNodePtr aux;
    int artigos = 0;
    aux = cur->parent;

    for(cur = cur->xmlChildrenNode; cur; cur = cur->next){

        if(!xmlStrcmp(cur->name,(const xmlChar *)"username")) {
            username = xmlNodeListGetString(doc,cur->xmlChildrenNode,1);
        }

        if(!xmlStrcmp(cur->name,(const xmlChar *) "id")) {
            idAutor = atol((char*) xmlNodeListGetString(doc,cur->xmlChildrenNode,1));
            void* c = getRegContribuidores(reg,idAutor);
            if(!avlSearch(c,idAutor)){
                Contribuidor stCont = initContribuidor();
                reg = insereRegContribuidor(reg,idAutor,stCont);
            }
        }
    }
    parseText(doc,aux,idArt,title,timestamp,idRev,idAutor,username,reg);
    return;
}


void parseRevision(xmlDocPtr doc, xmlNodePtr cur,long idArt,char* title,Registo reg){
    char* timestamp;
    long idRev;

    for(cur=cur->xmlChildrenNode;cur;cur=cur->next){
        if(!xmlStrcmp(cur->name,(const xmlChar *) "id")){
            idRev= atol((char*) xmlNodeListGetString(doc,cur->xmlChildrenNode,1));
        }
        if((!xmlStrcmp(cur->name,(const xmlChar *) "timestamp"))) {
            timestamp=(char*) xmlNodeListGetString(doc,cur->xmlChildrenNode,1);
        }
        if((!xmlStrcmp(cur->name,(const xmlChar *) "contributor"))) {
            parseContributor(doc,cur,idArt,title,timestamp,idRev,reg);
        }
    }

    return;
}


void parseDoc(int i,char *docname,int argc, Registo reg){

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
                    idArt = atol ((char*) xmlNodeListGetString(doc,cur->xmlChildrenNode,1));
                    void* a = getRegArtigos(reg,idArt);

                    if(i==1){
                        Artigo stArt = init_Artigo(argc);
                        reg=insereRegArtigo(reg,idArt,stArt);
                    }
                    else{
                        if(!avlSearch(a,idArt)){
                            Artigo stArt = init_Artigo(argc);
                            reg=insereRegArtigo(reg,idArt,stArt);
                        }
                    }
                }
                if((!xmlStrcmp(cur->name,(const xmlChar *) "revision"))){
                    parseRevision(doc,cur,idArt,title,reg);
                }

            }
        }

        cur=aux->next;
        //printf("%s = %ld\n",title,idArt);

    }
    xmlFreeDoc(doc);
    return;
}

int main(int argc, char **argv){
    int i;
    char *docname;
    clock_t tpf;

    if(argc <= 1){
        perror("Uso incorrecto\n");
        return 0;
    }

    Registo reg = initReg();
    tpf =clock();
    for(i=1;argc>1;argc--,i++){
        docname=argv[i];
        parseDoc(i,docname,argc,reg);
        printf("faz %d\n",i);
    }
    printf("acaba parser\n");
    /*
    printf("caralho\n");
    long nome = all_articles(a);
    printf("Total: %ld\n",nome);
    nome = unique_articles(a);
    printf("artigos unicos: %ld\n",nome);
    nome = all_revisions(a);
    printf("revisoes: %ld\n",nome);

    */
    ////29128
    int z=0;
    void* art = getRegArtEstrutura(reg,29128);
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
