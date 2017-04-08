#include<stdio.h>
#include<stdlib.h>
#include<strings.h>
#include "interface.h"



int main(){
    TAD_istruct qs = init();
    qs = load(qs,argc-1,&argv[1]);
    char id[100]= fgets(id,100,stdin);
    printf("total_articles %lu",all_articles(qs));

    printf("unique_articles %lu",unique_articles(qs));

    printf("unique_revisions %lu",all_revisions(qs));

    long *contributors=top_10_contributors(qs);

    printf("top_10_contributors ids: \n");

    for(int i=0; i<10; i++){
        printf("%lu = %s\n",contributors[i],contributor_name);
    }

    printf("contributor_name %s",contributor_name(id,qs));

    printf("top_20_largest_articles: \n");
    long *articles = top_20_largest_articles(qs);

    for(int i=0;i<20;i++){
        printf("%s",top_20_largest_articles[i]);
    }

    printf("article_title %s",article_title(id,qs));

    printf("top_N_articles_with_more_words :\n");

    for(int i=0;i<N;i++){
        printf("")
    }

}
