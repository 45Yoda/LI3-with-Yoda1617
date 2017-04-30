#include "./headers/interface.h"


int main(int argc,char **argv){

    //int estado = 1;

    TAD_istruct reg=init();

    load(reg,argc,argv);

    /*while(estado){
    estado = menuPrincipal(reg,argc,argv,estado);
}*/


    //reg = clean(reg);

    return 0;
}
