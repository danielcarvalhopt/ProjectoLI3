#include <stdio.h>
#include <string.h>
#include "ndavl.h"
#include "utils.h"
#include "menu.h"
#include "dados.h"


char rodape[51] = "Programa iniciado";

int main(/*int argc, char **argv*/){
    int input=0, i,stop=-1;
    Camiao a[20] = {
        {0, "00-60-00", 1.0},
        {1, "60-00-00", 1.5},
        {2, "00-00-60", 2.0},
        {3, "00-85-00", 2.5},
        {4, "94-00-00", 3.0},
        {5, "00-63-85", 3.5},
        {6, "63-00-60", 4.0},
        {7, "60-94-00", 4.5},
        {8, "85-85-85", 5.0},
        {9, "85-AA-85", 5.5},
        {10, "60-BB-00", 6.0},
        {11, "00-BB-60", 6.5},
        {12, "94-CC-00", 7.0},
        {13, "00-DC-00", 7.5},
        {14, "00-NY-00", 8.0},
        {15, "00-FK-00", 8.5},
        {16, "85-XX-00", 9.0},
        {17, "94-94-94", 9.5},
        {18, "85-85-85",10.0},
        {19, "60-60-60",10.5} };
    //MainTree camioes = {
    //    {NULL,NULL},
    //    {camiao_compararId, camiao_compararMatricula},
    //    {camiao_dump, camiao_dump}
    //};
    
    int (*funcCompara[DIM])(void*,void*) = {camiao_compararId, camiao_compararMatricula};
    void (*funcPrint[DIM])(void*) = {camiao_dump, camiao_dump};


    MainTreePt camioes = tree_new( funcCompara, funcPrint );
    while( input != -1 ){
        stop = -1;
        input = printMenu(input);
        switch(input){
            case 31: //recolheria os dados, por agora insere alguns
                for(i=0; i<20; i++)
                    tree_insert( camioes, camiao_novo( a[i].id, a[i].matricula, a[i].custo ) );
                stop = 3;
                break;
            case 33:
                tree_printOrdered( camioes, 1);
                stop = 3;
                break;
            default: break;
        }
        
        if( stop != -1 ){
            getchar(); clearInputBuffer();
            input = stop;
        }

    }
    return 0;
}

