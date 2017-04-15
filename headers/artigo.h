#ifndef _artigo_h_
#define _artigo_h_

typedef struct artigo *Artigo;

Artigo init_Artigo (int size);

char* getTitulo (Artigo a);
void setTitulo(Artigo a, char* title);
int getN(Artigo a);
void incrN(Artigo a);
void getTimeStamp(Artigo a, char* t[]);
void setTimeStamp(Artigo a, char* timestamp,int pos);
void getAutores(Artigo a,char* aut[]);
void setAutores(Artigo a, char* autor, int pos);
void getAutId(Artigo a,long c[]);
void setAutId(Artigo a, long id, int pos);
void getRevId(Artigo a,long c[]); //novo
void setRevId(Artigo a,long id, int pos);//novo
long getBytes(Artigo a);
void setBytes(Artigo a, long bytes);
long getWords(Artigo a);
void setWords(Artigo a, long words);

#endif
