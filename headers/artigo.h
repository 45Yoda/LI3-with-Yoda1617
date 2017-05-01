#ifndef _artigo_h_
#define _artigo_h_

//Declaração do tipo da estrutura
typedef struct artigo *Artigo;

/* Função que inicializa toda uma nova estrutura Artigo alocando espaço para todas as componentes necessárias*/
Artigo init_Artigo (int size);

/* recebe como argumento um artigo e retorna o seu respetivo Título*/
char* getTitulo (Artigo a);

/* recebe como argumento um artigo e um title e substitui o tilulo presente no artigo pelo novo title*/
void setTitulo(Artigo a, char* title);

/* recebe como argumento um artigo e retorna o numero de vezes que o artigo aparece */
int getN(Artigo a);

/* recebe como argumento um artigo e incrementa o numero de aparições do artigo*/
void incrN(Artigo a);

/* recebe como argumento um artigo e um array de char* e copia para esse array os timestamps do artigo*/
void getTimeStamp(Artigo a, char* t[]);

/* recebe como argumento um artigo, um char* times e um int pos que traduz o tamanho do array e coloca o times na ultima posição do array de timestamp do artigo fornecido*/
void setTimeStamp(Artigo a, char* timestamp,int pos);

/* recebe como argumento um artigo e um array de longs e copia para esse array os ID's das revisões desse artigo*/
void getRevId(Artigo a,long c[]);

/* recebe como argumento um artigo, um ID e um int pos e coloca na posição pos do array de ID's das revisões o novo ID fornecido*/
void setRevId(Artigo a,long id, int pos);

/* recebe como argumento um artigo e retorna o numero de bytes do mesmo */
long getBytes(Artigo a);

/* recebe como argumento um artigo e um long bytes e coloca na estrutura artigo o numero de bytes do artigo com o valor de bytes fornecido*/
void setBytes(Artigo a, long bytes);

/* recebe como argumento um artigo e retorna o numero de palavras do mesmo */ 
long getWords(Artigo a);

/* recebe como argumento um artigo e um long words e coloca na estrutura artigo o numero de palavras com o novo valor words fornecido*/
void setWords(Artigo a, long words);

/* recebe como argumento um artigo e liberta toda a memória que estava a ser ocupado por aquela estrutura Artigo*/
void freeArt(Artigo a);

#endif
