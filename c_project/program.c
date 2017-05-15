#include "interface.h"


int main(int argc,char **argv){

    TAD_istruct reg=init();

    load(reg,argc,argv);

    clean(reg);

    return 0;
}
