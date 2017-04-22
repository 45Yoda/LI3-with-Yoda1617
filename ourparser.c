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
    int c=0;
    art = getRegArtEstrutura(reg,idArt);

    setTitulo(art,title);
    int i = getN(art);
    setTimeStamp(art,timestamp,i);
    setRevId(art,idRev,i);
    incrN(art); 
    if (getWords(art)<wcount) setWords(art,wcount);
    if (getBytes(art)<bcount) setBytes(art,bcount);
}

/*void countWB(xmlChar* s, long* b, long* w){
    int i;
    long c=0;
    long l=0;
    for(i=0;s[i]!='\0';i++){
        if(s[i]!=' ' && (s[i+1]==' ' || s[i+1]=='\n' || s[i+1]=='\t')) c++;
        l++;
    }
    *w=c;
    *b=l;
}
*/

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
}



void parseText(xmlDocPtr doc,xmlNodePtr cur, long idArt,char* title,char* timestamp,long idRev,long idAutor,char* username,Registo reg){
    long wcount=0;
    long bcount=0;
    xmlChar* text;

    for(cur=cur->xmlChildrenNode;cur;cur=cur->next){
        if(cur->properties && (!xmlStrcmp(cur->properties->name,(const xmlChar*) "space"))){
            text=xmlNodeListGetString(doc,cur->xmlChildrenNode,1);
            countWB(text,&bcount,&wcount);

        }
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
    xmlChar* ip=NULL;
    xmlChar* username;
    char *user;
    xmlNodePtr aux;
    int artigos = 0;

    aux = cur->parent;
    int c=0;

    for(cur = cur->xmlChildrenNode; cur; cur = cur->next){

        if(!xmlStrcmp(cur->name,(const xmlChar *) "ip")){
            ip = xmlNodeListGetString(doc,cur->xmlChildrenNode,1);
        }

        if(!xmlStrcmp(cur->name,(const xmlChar *) "username")) {
            username = xmlNodeListGetString(doc,cur->xmlChildrenNode,1);
        }

        if(!xmlStrcmp(cur->name,(const xmlChar *) "id")) {
            idAutor = atol((char*) xmlNodeListGetString(doc,cur->xmlChildrenNode,1));
        }
    }

    if(!ip)  insereRegContribuidor(reg, idAutor, username);

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
                    title = xmlNodeListGetString(doc,cur->xmlChildrenNode,1);
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
    return titulos;
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

    char** tt=titles_with_prefix("SuperBow",reg);
    for(i=0;tt[i]!=NULL;i++)
        printf("%s\n",tt[i]);
/*
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
