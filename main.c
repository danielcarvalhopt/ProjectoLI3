/**
 * @file main.c
 * @brief Ficheiro com a função main e inicializações de algumas variáveis
 * */
#include <stdio.h>
#include <string.h>
#include "mod_avl_n_dimensional.h"
#include "utils.h"
#include "menu.h"
#include "dados.h"
#include "input.h"


int main(){
    int input=0;
    
    /** Declarar arrays de apontadores para as funções de comparação de dados */
    int (*comparaCamioes[DIM])(void*,void*) = {camiao_compararId, camiao_compararMatricula};
    int (*comparaClientes[DIM])(void*,void*) = {cliente_compararNif, cliente_compararNome};
    
    /** Inicializar estruturas de controlo dos vários tipos de dados */
    MainTreePt camioes = tree_new( comparaCamioes );
    MainTreePt clientes = tree_new( comparaClientes );

    /** Inicializar os atalhos predefinidos do menu */
    inicializarAtalhos();

    while( input != -1 ){
        input = printMenu(input);
        input = getInput(input, camioes, clientes);
    }
    return 0;
}

