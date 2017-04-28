#ifndef _queries_h_
#define _queries_h_


Registo init();

Registo load(Registo reg,int nsnaps, char* snaps_paths[]);

long all_Articles(Registo reg);

long unique_articles(Registo reg);

long all_revisions(Registo reg);

long* top_20_largest_articles(Registo reg);

long* top_N_articles_with_more_words(int n,Registo reg);

char** titles_with_prefix(char* prefix,Registo reg);

long* top_10_contributors(Registo reg);

char* contributor_name(long contributor_id, Registo reg);


#endif
