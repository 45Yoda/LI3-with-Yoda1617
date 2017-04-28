#include "./headers/qPrint.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//All Articles
int querie_1(Registo reg){

    char opcao[20];
    int estado = 1;
    long valor;

    valor = all_Articles(reg);

    while(estado){
        system("clear");
        printf( "_____________________________________________\n" );
        printf( "\tTotal de Artigos\n");
        printf( "\t%ld\n",valor);
        printf( "-----------------------------------------------\n" );
        printf( "_____________________________________________\n" );

        printf( "\n(prima qualquer tecla para continuar)");

        scanf("%s",opcao);

        return estado;
    }
    return 1;
}


//Artigos Únicos
int querie_2(Registo reg){

    char opcao[20];
    int estado = 1;
    long valor;

    valor = unique_articles(reg);

    while(estado){
        system("clear");
        printf( "_____________________________________________\n" );
        printf( "\tArtigos Únicos\n");
        printf( "\t%ld\n",valor);
        printf( "_____________________________________________\n" );

        printf( "\n(prima qualquer tecla para continuar)");

        scanf("%s",opcao);

        return estado;
    }


    return 1;
}

//Total de Revisões
int querie_3(Registo reg){

    char opcao[20];
    int estado = 1;
    long valor;

    valor = all_revisions(reg);

    system("clear");
    printf( "_____________________________________________\n" );
    printf( "\tTotal de Revisões\n");
    printf( "\t\t%ld\n",valor);
    printf( "_____________________________________________\n" );

    printf( "\n(prima qualquer tecla para continuar)");

    scanf("%s",opcao);


    return estado;
}
