#include <stdio.h>
#include <string.h>
#include "ndavl.h"
#include "utils.h"
#include "menu.h"
#include "dados.h"


char rodape[51] = "Programa iniciado";

int main(/*int argc, char **argv*/){
    int input=0;//stop=-1;
        //MainTree camioes = {
    //    {NULL,NULL},
    //    {camiao_compararId, camiao_compararMatricula},
    //    {camiao_dump, camiao_dump}
    //};
    
    int (*funcCompara[DIM])(void*,void*) = {camiao_compararId, camiao_compararMatricula};
    void (*funcPrint[DIM])(void*) = {camiao_dump, camiao_dump};


    MainTreePt camioes = tree_new( funcCompara, funcPrint );
    while( input != -1 ){
        //stop = -1;
        input = printMenu(input);
        input = getInput(input, camioes);
    }
    return 0;
}

