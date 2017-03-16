typedef struct TCD_istruct * TAD_istruct;

TAD_istruct init();//inicializa a estrutura
TAD_istruct load(TAD_istruct qs, int nsnaps, char* snaps_paths[]);
long all_articles(TAD_istruct qs); //retorna todos os artigos nos backups
long unique_articles(TAD_istruct qs); // artigos unicos(com id unico) encontrados nos backups
long all_revisions(TAD_istruct qs); //número total de revisões (nr total de versoes diferentes encontradas nos backups)
long* top_10_contributors(TAD_istruct qs);//array com id dos 10 autores com mais contribuiçoes
char* contributor_name(long contributor_id, TAD_istruct qs);//nome do autor com determinado id (n existe return NULL)
long* top_20_largest_articles(TAD_istruct qs); //array com ids dos 20 artigos com maior tamanho
char* article_title(long article_id, TAD_istruct qs);//devolve titulo com determinado id
long* top_N_articles_with_more_words(int n,TAD_istruct qs);//devolve array com os ids dos n artigos com maior numero de palavras
char** titles_with_prefix(char* prefix,TAD_istruct qs);//devolve lista de titulos de artigos q começam com um prefixo especifico (ordem alfabetica)
char* article_timestamp(long article_id,long revision_id,TAD_istruct qs);//devolve o timestamp para uma certa revisao de um artigo
TAD_istruct clean(TAD_istruct qs);//liberta todos os recursos associados à estrutura;
