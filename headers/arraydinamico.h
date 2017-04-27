#ifndef _arraydinamico_h_
#define _arraydinamico_h_

#include "global.h"


typedef struct array *Array;

Array initArray(int initialSize);

Array insertArray(Array a,char* str);

Boolean existeArray(Array a,char* val);

void freeArray(Array a);

int getPosArray(Array a);

char* getNameArray(Array a,int pos);

char** cloneArray(Array a);

#endif
