#ifndef _artigo_h_
#define _artigo_h_

typedef struct artigo *Artigo;

Artigo init_Artigo (int size);

char* getTitulo (Artigo a);
void* setTitulo(Artigo a, char* title);

#endif
