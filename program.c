#include "./headers/interpretador.h"
#include "./headers/registo.h"


int main(int argc,char **argv){

    //int estado = 1;

    Registo reg=init();

    reg=load(reg,argc,argv);

    /*while(estado){
    estado = menuPrincipal(reg,argc,argv,estado);
}*/


    //freeReg(reg);

    return 0;
}
