#ifndef _queries_h_
#define _queries_h_



void initLongArray(long* top,int n);

long* top_20_largest_articles(Registo reg);

long* top_N_articles_with_more_words(int n,Registo reg);

char** titles_with_prefix(char* prefix,Registo reg);

long* top_10_contributors(Registo reg);

char* contributor_name(long contributor_id, Registo reg);


#endif
