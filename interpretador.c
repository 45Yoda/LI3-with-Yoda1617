#include "./headers/interpretador.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define sair 0
#define MenuPrincipal 1

static int menuArtigos(TAD_istruct reg);
static int menuContribuidores(TAD_istruct reg);

int menuPrincipal(TAD_istruct reg,int nsnaps,char** snaps_path,int estado){

    char option[20];

    while(estado){
        system("clear");
        printf("_______________________________________________\n");
		printf("\t\tMenu Principal \n");
        printf("-------------------------------------------\n");
        printf("Escolha uma categoria:\n");
        printf("   1. Artigos\n");
        printf("   2. Contribuidores\n");
        printf("-------------------------------------------\n");
        printf("\t\tQ - Sair\n");
        printf("_______________________________________________\n");

        printf("\nOpção > ");

        scanf("%s",option);

        switch(option[0]){

            case 'Q':
            case 'q': return sair; break;

            case '1': if(reg!=NULL){
                        estado = menuArtigos(reg);
                      }
                      else{
                          system("clear");
                          printf("\n Ainda não foram lidos dados\n");
                          printf("\n Prima qualquer tecla para voltar ao menu >> ");
                          scanf("%s",option);
                      }
                      break;

            case '2': if(reg!=NULL) estado = menuContribuidores(reg);
                      else{
                          system("clear");
                          printf("\n Ainda não foram lidos dados\n");
                          printf("\n Prima qualquer tecla para voltar ao menu >> ");
                          scanf("%s",option);
                      }
                      break;

            default: break;

        }
    }
    return estado;
}


static int menuArtigos(TAD_istruct reg){

    int estado = 1;
    char option[20];

    while(estado){

        system("clear");
        printf("_______________________________________________\n");
		printf("\t\tMenu Artigos \n");
        printf("-------------------------------------------\n");
        printf("Escolha o uma opção:\n");
        printf("   1. Total de Artigos\n");
        printf("   2. Artigos únicos\n");
        printf("   3. Total de Revisões\n");
        printf("   4. Top 20 Maiores Artigos\n");
        printf("   5. Titulo do Artigo\n");
        printf("   6. Top N Artigos com mais palavras\n");
        printf("   7. Titulos com um Prefixo\n");
        printf("   8. Timestamp de uma dada Revisão de um Artigo\n");
        printf("-------------------------------------------\n");
        printf("\t\tB - Menu Principal\t\t Q - Sair\n");
        printf("_______________________________________________\n");

        printf("\nOpção > ");

        scanf("%s",option);

        switch(option[0]){

            case 'Q':
            case 'q': return sair; break;

            case 'B':
            case 'b': return MenuPrincipal; break;

            case '1': estado = querie_1(reg);
                      return MenuPrincipal;
                      break;

            case '2': estado = querie_2(reg);
                      return MenuPrincipal;
                      break;

            case '3': estado = querie_3(reg);
                      return MenuPrincipal;
                      break;

            case '4': estado = querie_6(reg);
                      return MenuPrincipal;
                      break;

            case '5': estado = querie_7(reg);
                      return MenuPrincipal;
                      break;

            case '6': estado = querie_8(reg);
                      return MenuPrincipal;
                      break;

            case '7': estado = querie_9(reg);
                      return MenuPrincipal;
                      break;

            case '8': estado = querie_10(reg);
                      return MenuPrincipal;
                      break;

            default: break;

        }
    }
    return estado;
}

static int menuContribuidores(TAD_istruct reg){

    int estado = 1;
    char option[20];

    while(estado){

        system("clear");
        printf("_______________________________________________\n");
		printf("\t\tMenu Contribuidores \n");
        printf("-------------------------------------------\n");
        printf("Escolha o uma opção:\n");
        printf("   1. Top 10 Contribuidores\n");
        printf("   2. Username do Contribuidor\n");
        printf("-------------------------------------------\n");
        printf("\t\tB - Menu Principal\t\t Q - Sair\n");
        printf("_______________________________________________\n");

        printf("\nOpção > ");

        scanf("%s",option);

        switch(option[0]){

            case 'Q':
            case 'q': return sair; break;

            case 'B':
            case 'b': return MenuPrincipal; break;

            case '1': estado = querie_4(reg);
                      return MenuPrincipal;
                      break;

            case '2': estado = querie_5(reg);
                      return MenuPrincipal;
                      break;

            default: break;

        }
    }
    return estado;
}
