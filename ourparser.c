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
    art = getRegArtEstrutura(reg,idArt);

    setTitulo(art,title);
    int i = getN(art);
    setTimeStamp(art,timestamp,i);
    setRevId(art,idRev,i);
    incrN(art);
    if (getWords(art)<wcount) setWords(art,wcount);
    if (getBytes(art)<bcount) setBytes(art,bcount);
}


void countWB(xmlChar* s,int* b,int* w)
{   int n = 0;
    int l=0;
    l=strlen(s);
    for(s=strtok(s, " \n\t"); s; s=strtok(NULL, " \n\t"))
        n++;
    *b=l;
    *w=n;
}

/*
void countWB(xmlChar* s, long* b, long* w){
    int i;
    char* q = s;
    long c=0;
    long l=0;
    for(i=0;s[i]!='\0';i++){
        if(s[i]!=' ' && (s[i+1]==' ' || s[i+1]=='\n' || s[i+1]=='\t')) c++;

    }
    l=strlen(q);
    *w=c;
    *b=l;
}

void countWB(xmlChar* s, long* b, long* w){
    char delim[3]=" \n\t";
    char* token;
    int c=0;
    int l=0;
    token = strtok(s,delim);
    while(token != NULL){
        l+=strlen(token);
        l++;
        c++;
        token=strtok(NULL,delim);
    }
    l--;
    *w=c;
    *b=l;
}*/



void parseText(xmlDocPtr doc,xmlNodePtr cur, long idArt,char* title,char* timestamp,long idRev,long idAutor,char* username,Registo reg){
    int wcount=0;
    int bcount=0;
    xmlChar* text;

    for(cur=cur->xmlChildrenNode;cur;cur=cur->next){
        if(cur->properties && (!xmlStrcmp(cur->properties->name,(const xmlChar*) "space"))){
            text=xmlNodeListGetString(doc,cur->xmlChildrenNode,1);
            countWB(text,&bcount,&wcount);

        }
    }
    parseFinal(idArt,title,timestamp,idRev,idAutor,username,reg,wcount,bcount);
}


void parseContributor(xmlDocPtr doc, xmlNodePtr cur,long idArt,char* title,char* timestamp,long idRev, Registo reg){
    long idAutor;
    xmlChar* username;
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

    if(username)  insereRegContribuidor(reg, idAutor, username);

    parseText(doc,aux,idArt,title,timestamp,idRev,idAutor,username,reg);

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
    for(cur;cur!=NULL;cur=cur->next){
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


    long* conts=top_10_contributors(reg);
    for(i=0;i<10;i++)
        printf("%ld\n",conts[i]);
    /*
    long nome = all_Articles(reg);
    printf("Total: %ld\n",nome);
    nome = totalRegElemsArtigos(reg);
    printf("artigos unicos: %ld\n",nome);
    nome = all_revisions(reg);
    printf("revisoes: %ld\n",nome);
    */

    ////29128
    /*
    int z=0;
    void* art = getRegArtEstrutura(reg,29128);
    void* cont = getRegContEstrutura(reg,24198);
    char* u = malloc(sizeof(char*));
    //if(!cont){printf("fuiteaocu\n");} else{
    getUsername(cont,u);
    printf("%s\n",u);
    char* t = getTitulo(art);
    printf("%s\n",t);
    int nn = getN(art);
    printf("%d\n", nn);
    char**  tim=malloc(nn*sizeof(char*));
    long* revid=malloc(nn*sizeof(long*));
    getTimeStamp (art,tim);
    getRevId(art,revid);
    for(z=0;z<nn;z++){
        printf("%s\n",tim[z]);
        printf("%lu\n",revid[z]);
        printf("------------------------\n");
    }*/
    tpf =clock() -tpf;
    printf("Demorou %f segundos a ler\n",((float)tpf)/CLOCKS_PER_SEC);

    return 1;
}
