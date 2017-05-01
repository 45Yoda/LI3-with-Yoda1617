#ifndef _contribuidor_h_
#define _contribuidor_h_

//Declaração da estrutura Contribuidor
typedef struct contribuidor *Contribuidor;

/* Função que inicializa toda uma nova estrutura Contribuidor alocando espaço para todas as componentes necessárias*/
Contribuidor initContribuidor ();

/* recebe um Contribuidor e um char* new e copia o username do Contribuidor para o new*/ 
void getUsername(Contribuidor c,char* new);

/* recebe um Contribuidor e um char* new e atualiza o username com o new fornecido*/
void setUsername(Contribuidor c,char* user);

/* recebe um Contribuidor e retorna o numero de contribuições desse mesmo contribuidor*/
int getCont(Contribuidor c);

/* recebe um Contribuidor e incrementa as suas contribuições*/
void incrCont(Contribuidor c);

/* recebe um Contribuidor e liberta toda a memória utilizada pelo mesmo*/
void freeCont(Contribuidor c);

#endif
