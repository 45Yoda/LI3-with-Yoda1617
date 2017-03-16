#include<stdio.h>
#include<stdlib.h>
#include<strings.h>
#include "interface.h"



int main(){
    TAD_istruct qs = init();
    qs = load(qs,argc-1,&argv[1]);
    printf("total_articles %lu",all_articles(qs));

    printf("unique_articles %lu",unique_articles(qs));

    printf("unique_revisions %lu",all_revisions(qs));

    long *contributors=top_10_contributors(qs);

    printf("top_10_contributors ids: \n");

    for(int i=0; i<10; i++){
        printf("%lu = %s\n",contributors[i],contributor_name)
    }
}
