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
#include "./headers/global.h"



void parseFinal(long idArt, char* title, char* timestamp, long idRev, Registo reg, long wcount, long bcount) {
    void* art;
    art = getRegArtEstrutura(reg,idArt);

    setTitulo(art,title);
    int i = getN(art);
    setTimeStamp(art,timestamp,i);
    setRevId(art,idRev,i);
    incrN(art);
    if (getWords(art)<wcount) setWords(art,wcount);
    if (getBytes(art)<bcount) setBytes(art,bcount);
}


void countWB(char* s,long* b,long* w){
    int n = 0;
    int l=0;
    l=strlen(s);
    for(s=strtok(s, " \n\t"); s; s=strtok(NULL, " \n\t"))
        n++;
    *b=l;
    *w=n;
}

void parseText(xmlDocPtr doc,xmlNodePtr cur, long idArt,char* title,char* timestamp,long idRev,Registo reg){
    long wcount=0;
    long bcount=0;
    char* text;

    for(cur=cur->xmlChildrenNode;cur;cur=cur->next){
        if(cur->properties && (!xmlStrcmp(cur->properties->name,(const xmlChar*) "space"))){
            text=(char*) xmlNodeListGetString(doc,cur->xmlChildrenNode,1);
            countWB(text,&bcount,&wcount);

        }
    }
    parseFinal(idArt,title,timestamp,idRev,reg,wcount,bcount);
}


void parseContributor(xmlDocPtr doc, xmlNodePtr cur,long idArt,char* title,char* timestamp,long idRev, Registo reg){
    long idAutor;
    char* username;
    xmlNodePtr aux;

    aux = cur->parent;


    for(cur = cur->xmlChildrenNode; cur; cur = cur->next){

        if(!xmlStrcmp(cur->name,(const xmlChar *) "username")) {
            username = (char*) xmlNodeListGetString(doc,cur->xmlChildrenNode,1);
        }

        if(!xmlStrcmp(cur->name,(const xmlChar *) "id")) {
            idAutor = atol((char*) xmlNodeListGetString(doc,cur->xmlChildrenNode,1));
        }
    }

    if(username)  {
        void* c = getRegContribuidores(reg,idAutor);

        if (!avlSearch(c,idAutor)) {
            Contribuidor con = initContribuidor(username);
            reg=insereRegContribuidor(reg,idAutor,con);
        
        }
        else {
            Contribuidor con =getAvlEstrutura(c,idAutor);
            incrCont(con);
        }
}

    parseText(doc,aux,idArt,title,timestamp,idRev,reg);

    return;
}


void parseRevision(xmlDocPtr doc, xmlNodePtr cur,long idArt,char* title,Registo reg){
    char* timestamp;
    long idRev;

    for(cur=cur->xmlChildrenNode;cur;cur=cur->next){
        if((!xmlStrcmp(cur->name,(const xmlChar *) "id"))){
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

    char* title;
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
        perror("Empty document\n");
        xmlFreeDoc(doc);
        return;
    }

    cur = cur->xmlChildrenNode;
    cur = cur->next;
    for(;cur!=NULL;cur=cur->next){
        aux=cur;
        if(!xmlStrcmp(cur->name,(const xmlChar *) "page")){
            for(cur=cur->xmlChildrenNode; cur; cur= cur->next){

                if((!xmlStrcmp(cur->name,(const xmlChar *) "title"))){
                    title = (char*) xmlNodeListGetString(doc,cur->xmlChildrenNode,1);
                }

                if((!xmlStrcmp(cur->name,(const xmlChar *) "id"))){
                    idArt = atol ((char*) xmlNodeListGetString(doc,cur->xmlChildrenNode,1));
                    void* a = getRegArtigos(reg,idArt);

                    if(i == 1 || !avlSearch(a,idArt)){
                        Artigo stArt = init_Artigo(argc);
                        reg=insereRegArtigo(reg,idArt,stArt);
                    }
                }
                if((!xmlStrcmp(cur->name,(const xmlChar *) "revision"))){
                    parseRevision(doc,cur,idArt,title,reg);
                }

            }
        }

        cur=aux;
    }
    xmlFreeDoc(doc);
    return;
}

Registo parser(Registo reg,int argc, char **argv){
    int i;
    char *docname;
    clock_t tpf;

    if(argc <= 1){
        perror("Uso incorrecto\n");
        return NULL;
    }

    tpf =clock();
    for(i=1;argc>1;argc--,i++){
        docname=argv[i];
        parseDoc(i,docname,argc,reg);
        printf("faz %d\n",i);
    }
    printf("acaba parser\n");

    tpf =clock() -tpf;
    printf("Demorou %f segundos a ler\n",((float)tpf)/CLOCKS_PER_SEC);

    return reg;
}
