#include <stdio.h>
#include <string.h>
#include "mod_avl_n_dimensional.h"
#include "utils.h"
#include "menu.h"
#include "dados.h"
#include "localidades.h"
#include "input.h"
#include "mod_tabela_hash.h"
#include "mod_lista_ligada.h"


char rodape[51] = "Programa iniciado";

int main(/*int argc, char **argv*/){
    int input=0;
     
    int (*comparaCamioes[DIM])(void*,void*) = {camiao_compararId, camiao_compararMatricula};
    int (*comparaClientes[DIM])(void*,void*) = {cliente_compararNif, cliente_compararNome};

    MainTreePt camioes = tree_new( comparaCamioes );
    MainTreePt clientes = tree_new( comparaClientes );
    TabelaHashPTR table = hashtablecreator (hash_function, 85, comparalocalidades);
    inicializarAtalhos();
    while( input != -1 ){
        //stop = -1;
        input = printMenu(input);
        input = getInput(input, camioes, clientes, table);
    }
    return 0;
}

