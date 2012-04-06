/**
 * @file serial.c
 * @brief Definições estáticas e código das funções de serialização e de-serialização
 *
 * */
#include <stdio.h>
#include <string.h>

#include "serial.h"
#include "dados.h"
#include "mod_avl_n_dimensional.h"
#include "mod_lista_ligada.h"
#include "mod_tabela_hash.h"

void serialize(TabelaHashPTR tabela, MainTreePt camioes, MainTreePt clientes){
    FILE *file;
    int i, nAdj;
    short int strl;
    MainListPTR *lista = tabela->arraycell;
    LinkedListPTR listaAux = NULL;
    LinkedListPTR adjacencia = NULL;

    file = fopen("stest", "w+");
    if( file == 0 ) return;
    
    //tamanho do array de hash
    fwrite(&tabela->totalcells, sizeof(int), 1, file);

    //numero de elementos da tabela de hash
    fwrite(&tabela->nelems, sizeof(int), 1, file);
    for(i=0; i<tabela->totalcells; i++){
        listaAux = lista[i]->elems;
        while( listaAux ){
            strl = strlen(((LocalidadePTR)(listaAux->extdata))->nome)+1;
            fwrite( &strl, sizeof(short int), 1, file );
            //printf("%d", strl);
            fwrite( ((LocalidadePTR)(listaAux->extdata))->nome, sizeof(char), strl, file );
            //printf("%s\n", ((LocalidadePTR)(listaAux->extdata))->nome );
            
            nAdj = ((LocalidadePTR)(listaAux->extdata))->ligacoesida->nelems;
            fwrite( &nAdj, sizeof(int), 1, file );
            adjacencia = ((LocalidadePTR)(listaAux->extdata))->ligacoesida->elems;
            
            while( adjacencia ){
                strl = strlen( ((LigacoesidaPTR)adjacencia->extdata)->nome ) +1;
                fwrite( &strl, sizeof(short int), 1, file );
                
                fwrite( ((LigacoesidaPTR)adjacencia->extdata)->nome, sizeof(char), strl, file );

                fwrite( &((LigacoesidaPTR)adjacencia->extdata)->custo, sizeof(float), 1, file );
                fwrite( &((LigacoesidaPTR)adjacencia->extdata)->distancia, sizeof(float), 1, file );

                adjacencia = adjacencia->prox;
            }
            listaAux = listaAux->prox;
        }
    }

    fclose(file);
}

void deserialize(){
    int strl, i;
    char str[100];
    FILE *file;
    file = fopen("stest", "r");
    if( file == 0 ) return;

    int x;
    fread( &x, sizeof(int), 1, file );
    printf("Tamanho da tabela: %d\n", x );
    fread( &x, sizeof(int), 1, file );
    printf("Número de elementos: %d\n", x );

    for( i=0; i<x; i++ ){
        fread( &strl, sizeof(int), 1, file );
        fread( str, sizeof(char), strl, file );
        printf( "%d%s\n", strl, str );
    }
}
