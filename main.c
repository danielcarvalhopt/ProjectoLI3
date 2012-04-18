/**
 * @file main.c
 * @brief Ficheiro com a função main e inicializações de algumas variáveis
 * */

/**
 * \mainpage Membros do Grupo 42
 * 
 * <CENTER><B>
 * Bruno Ferreira - a61055<BR>
 * Daniel Carvalho - a61008<BR>
 * Mariana Medeiros - a61041
 * </B></CENTER>
 * */

#include <stdio.h>
#include <string.h>
 #include <stdlib.h>

#include "dados.h"
#include "input.h"
#include "menu.h"
#include "utils.h"
#include "serial.h"

#include "mod_avl_n_dimensional.h"
#include "mod_lista_ligada.h"
#include "mod_tabela_hash.h"
#include "mod_graph.h"

int main(){
    int input=0;

    comparaCamioes[0] = camiao_compararId;
    comparaCamioes[1] = camiao_compararMatricula;
    comparaClientes[0] = cliente_compararNif;
    comparaClientes[1] = cliente_compararNome;
    
    /** Inicializar estruturas de controlo dos vários tipos de dados */ 
    MainTreePt camioes = tree_new( comparaCamioes );
    MainTreePt clientes = tree_new( comparaClientes );
    TabelaHashPTR localidades = criaTabelaHash(hash_function, 10000, comparalocalidades);
    
    //TabelaHashPTR localidades = NULL;
    //readSampleLocalidades(&localidades, comparalocalidades, hash_function);
    //MainTreePt clientes = NULL;
    //readSampleClientes(&clientes, comparaClientes);
    //MainTreePt camioes = NULL;
    //readSampleCamioes(&camioes, comparaCamioes);
    
    /** Inicializar os atalhos predefinidos do menu */
    inicializarAtalhos();

    while( input != -1 ){
        input = printMenu(input);
        input = getInput(input, &camioes, &clientes, &localidades);
    }
    return 0;
}

