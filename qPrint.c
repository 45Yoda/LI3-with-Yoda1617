#include "./headers/qPrint.h"
#include "interface.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



//All Articles
int querie_1(TAD_istruct reg){

    char opcao[20];
    int estado = 1;
    long valor;

    valor = all_articles(reg);

    while(estado){
        system("clear");
        printf( "_____________________________________________\n" );
        printf( "\t\tTotal de Artigos\n");
        printf( "\t\t     %ld\n",valor);
        printf( "---------------------------------------------\n" );
        printf( "_____________________________________________\n" );

        printf( "\n(prima qualquer tecla para continuar)");

        scanf("%s",opcao);

        return estado;
    }
    return 1;
}


//Artigos Únicos
int querie_2(TAD_istruct reg){

    char opcao[20];
    int estado = 1;
    long valor;

    valor = unique_articles(reg);

    while(estado){
        system("clear");
        printf( "_____________________________________________\n" );
        printf( "\t\tArtigos Únicos\n");
        printf( "\t\t     %ld\n",valor);
        printf( "_____________________________________________\n" );

        printf( "\n(prima qualquer tecla para continuar)");

        scanf("%s",opcao);

        return estado;
    }


    return 1;
}

//Total de Revisões
int querie_3(TAD_istruct reg){

    char opcao[20];
    int estado = 1;
    long valor;

    valor = all_revisions(reg);

    system("clear");
    printf( "_____________________________________________\n" );
    printf( "\t\tTotal de Revisões\n");
    printf( "\t\t     %ld\n",valor);
    printf( "_____________________________________________\n" );

    printf( "\n(prima qualquer tecla para continuar)");

    scanf("%s",opcao);


    return estado;
}

//Top 10 contribuidores (mais contribuições)
int querie_4(TAD_istruct reg){

    char opcao[20];
    int estado = 1;
    int i =0;
    long* t = malloc(10*sizeof(long));
    t = top_10_contributors(reg);
    system("clear");
    printf( "_____________________________________________\n" );
    printf( "\t\tTop 10 Contribuidores\n");
    for(i=0;i<10;i++){
        printf("%d=%ld\n",i+1,t[i]);
    }
    printf( "_____________________________________________\n" );

    free(t);
    printf( "\n(prima qualquer tecla para continuar)");

    scanf("%s",opcao);

    return estado;
}

//Username do Contribuidor
int querie_5(TAD_istruct reg){

    char opcao[20];
    int estado = 1;
    long valor;
    char* user;

    system("clear");
    printf("Indique o ID do contribuidor > ");
    scanf("%ld",&valor);
    user = contributor_name(valor,reg);
    if (user) {
    system("clear");
    printf( "_____________________________________________\n" );
    printf( "\t\tID: %ld \n",valor);
    printf( "\t\tUsername: %s \n",user);
    printf( "_____________________________________________\n" );

    free(user);
}
    else printf("ID de contribuidor inválido.\n");
    printf( "\n(prima qualquer tecla para continuar)");

    scanf("%s",opcao);


    return estado;
}

//Top 20 artigos
int querie_6(TAD_istruct reg){

    char opcao[20];
    int estado = 1;
    int i =0;
    long* t = malloc(20*sizeof(long));
    t = top_20_largest_articles(reg);
    system("clear");
    printf( "_____________________________________________\n" );
    printf( "\t\tTop 20 Maiores Artigos\n");
    for(i=0;i<20;i++){
        printf("%d=%ld\n",i+1,t[i]);
    }
    printf( "_____________________________________________\n" );

    free(t);
    printf( "\n(prima qualquer tecla para continuar)");

    scanf("%s",opcao);

    return estado;
}

//Titulo do artigo
int querie_7(TAD_istruct reg){

    char opcao[20];
    int estado = 1;
    long valor;
    char* art;

    system("clear");
    printf("Indique o ID do Artigo > ");
    scanf("%ld",&valor);
    art = article_title(valor,reg);
    if (art!=NULL) {
    system("clear");
    printf( "_____________________________________________\n" );
    printf( "\t\tID: %ld \n",valor);
    printf( "\t\tTitulo: %s \n",art);
    printf( "_____________________________________________\n" );
    free(art);
}
    else printf("O ID de esse artigo não é valido.\n");
    printf( "\n(prima qualquer tecla para continuar)");

    scanf("%s",opcao);


    return estado;
}

//Top N Artigos com mais palavras
int querie_8(TAD_istruct reg){

    char opcao[20];
    int estado = 1;
    int i =0,n=0;

    system("clear");
    printf("Indique o número de artigos para o Top > ");
    scanf("%d",&n);

    long* t = malloc(n*sizeof(long));
    t = top_N_articles_with_more_words(n,reg);
    system("clear");
    printf( "_____________________________________________\n" );
    printf( "\tTop %d Artigos com mais palavras\n",n);
    for(i=0;i<n;i++){
        printf("%d=%ld\n",i+1,t[i]);
    }
    printf( "_____________________________________________\n" );

    free(t);
    printf( "\n(prima qualquer tecla para continuar)");

    scanf("%s",opcao);

    return estado;
}

//Titulos com um Prefixo
int querie_9(TAD_istruct reg){

    char opcao[20];
    int estado = 1;
    int i =0;
    char** t;
    char* pref = malloc(sizeof(char*));
    char buffer[MAXSIZE];
    pref = buffer;

    system("clear");
    printf("Insira o prefixo > ");
    scanf("%s",pref);

    t = titles_with_prefix(pref, reg);

    if (t) {
        system("clear");
        printf( "_____________________________________________\n" );
        printf( "\tTitulos com prefixo \"%s\"\n",pref);
        for(i=1;t[i]!=NULL;i++){
            printf("%s\n",t[i]);
        }
        printf( "_____________________________________________\n" );

        for(i=0;t[i]!=NULL;i++){
            free(t[i]);
        }
        free(t);
    }

    else printf("Não existe nenhum titulo com esse prefixo.\n");

    printf( "\n(prima qualquer tecla para continuar)");

    scanf("%s",opcao);

    return estado;

}



//Timestamp de uma dada Revisão de um Artigo
int querie_10(TAD_istruct reg){

    char opcao[20];
    int estado = 1;
    long valorA,valorR;
    char* times;

    system("clear");
    printf("Indique o ID do Artigo > ");
    scanf("%ld",&valorA);
    printf("Indique o ID da revisão > ");
    scanf("%ld",&valorR);
    times = article_timestamp(valorA,valorR,reg);
    if (times) {
    system("clear");
    printf( "_____________________________________________\n" );
    printf( "\tID do Artigo: %ld \n",valorA);
    printf( "\tID de Revisão: %ld \n",valorR);
    printf( "\tTimestamp: %s \n",times);
    printf( "_____________________________________________\n" );
}
else printf("ID's inválidos.\n");
    printf( "\n(prima qualquer tecla para continuar)");

    free(times);
    scanf("%s",opcao);


    return estado;
}
