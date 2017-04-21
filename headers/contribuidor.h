#ifndef _contribuidor_h_
#define _contribuidor_h_

typedef struct contribuidor *Contribuidor;

Contribuidor initContribuidor ();

void getUsername(Contribuidor c,char* new);

void setUsername(Contribuidor c,char* user);

int getCont(Contribuidor c);

void incrCont(Contribuidor c);

#endif
