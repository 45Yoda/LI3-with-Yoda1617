#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include "./headers/artigo.h"
#include "./headers/avl.h"

void parseContributor(xmlDocPtr doc, xmlNodePtr cur,long idArt,char* title,Avl a){

    long id;
    Char *username;
    xmlNodePtr aux;
    int ipMode = 0;
    int artigos = 0;

    aux = cur->parent;

    for(cur= cur->xmlChildrenNode; cur;cur = cur->next){

        if(!xmlStrcmp(cur->name,(const xmlChar *)"username"))
            username = (char*) xmlNodeListGetString(doc,cur->xmlChildrenNode,1);

        if(!xmlStrcmp(cur->name,(const xmlChar *) "id"))
            id = atol((char*) xmlNodeListGetString(doc,cur->xmlChildrenNode,1));
    }

    parseText(doc,aux,idArt,title,username,id,a);
    return;
}

void parseRevision(xmlDocPtr doc, xmlNodePtr cur,long idArt,char* title,Avl a){

    for(cur=cur->xmlChildrenNode;cur;cur=cur->next){
        if((!xmlStrcmp(cur->name,(const xmlChar *) "contributor")))
            parseContributor(doc,cur,idArt,title,a);
        }

    return;
}


void parseDoc(char *docname,int argc, Avl a){

    long idArt;
    clock_t tpf;

    xmlChar *id;
    xmlChar *title;
    char* idA;
    xmlDocPtr doc;
    xmlNodePtr cur;
    xmlNodePtr aux;

    Artigo stArt = init_Artigo(argc);

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

    for(cur;cur;cur=cur->next){
        aux=cur;
        if(!xmlStrcmp(cur->name,(const xmlChar *) "page")){
            for(cur=cur->xmlChildrenNode; cur; cur= cur->next){

                if((!xmlStrcmp(cur->name,(const xmlChar *) "title"))){
                    title = xmlNodeListGetString(doc,cur->xmlChildrenNode,1);

                }

                if((!xmlStrcmp(cur->name,(const xmlChar *) "id"))){
                    idA=(char*) xmlNodeListGetString(doc,cur->xmlChildrenNode,1);
                    idArt= atol(idA);
                    if (!avlSearch(a,idArt)) {
                        a=insertAvl(a,idArt,stArt);  
                }   

                if((!xmlStrcmp(cur->name,(const xmlChar *) "revision"))){
                    parseRevision(doc,cur,idArt,title,a);
                }
            }
        }
        cur=aux->next;
        printf("%s = %ld\n",title,idArt);

    }

    xmlFreeDoc(doc);
    return;
}

int main(Avl a, int argc, char **argv){
    int i;
    char *docname;

    if(argc <= 1){
        perror("Uso incorrecto\n");
        return 0;
    }

for(i=1;argc>1;argc--,i++){
    docname=argv[i];
    parseDoc(docname,argc,a);
}

    return 1;
}
