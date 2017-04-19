#ifndef _contribuidor_h_
#define _contribuidor_h_

typedef struct contribuidor *Contribuidor;

Contribuidor initContribuidor ();

char* getUsername(Contribuidor c);

void setUsername(Contribuidor c,char* user);

int getCont(Contribuidor c);

void incrCont(Contribuidor c);

#endif
