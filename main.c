/**
 * @file main.c
 * @brief Ficheiro com a função main e inicializações de algumas variáveis
 * */

/**
 * \mainpage Membros do Grupo
 * 
 *
 * \image html membros.png Grupo 42
 *
 * <CENTER><B>
 * Bruno Ferreira - a61055<BR>
 * Daniel Carvalho - a61008<BR>
 * Mariana Medeiros - a61041
 * </B></CENTER>
 * */

#include <stdio.h>
#include <string.h>

#include "dados.h"
#include "input.h"
#include "menu.h"
#include "utils.h"
#include "serial.h"

#include "mod_avl_n_dimensional.h"
#include "mod_lista_ligada.h"
#include "mod_tabela_hash.h"

int main(){
    int input=0;
    
    /** Declarar arrays de apontadores para as funções de comparação de dados */
    int (*comparaCamioes[DIM])(void*,void*) = {camiao_compararId, camiao_compararMatricula};
    int (*comparaClientes[DIM])(void*,void*) = {cliente_compararNif, cliente_compararNome};
    
    /* testes (des-serialização) */
    MainTreePt camioes = NULL;
    MainTreePt clientes = NULL;
    TabelaHashPTR localidades = NULL;

    deserialize( &camioes, comparaCamioes, &clientes, comparaClientes, &localidades, comparalocalidades, hash_function );
    return 1;
    /* fim de testes (des-serialização) */

    /** Inicializar estruturas de controlo dos vários tipos de dados 
    MainTreePt camioes = tree_new( comparaCamioes );
    MainTreePt clientes = tree_new( comparaClientes );
    TabelaHashPTR localidades = criaTabelaHash(hash_function, 10000, comparalocalidades);

    /** Inicializar os atalhos predefinidos do menu */
    inicializarAtalhos();
    

    /*testes (serialização) 
    int i;
    Camiao camiao_teste[20] = {
        {0, "00-60-00", 1.0, 10, "Fátima"},
        {1, "60-00-00", 1.5, 10, "Fátima"},
        {2, "00-00-60", 2.0, 10, "Fátima"},
        {3, "00-85-00", 2.5, 10, "Fátima"},
        {4, "94-00-00", 3.0, 10, "Fátima"},
        {5, "00-63-85", 3.5, 10, "Fátima"},
        {6, "63-00-60", 4.0, 10, "Fátima"},
        {7, "60-94-00", 4.5, 10, "Fátima"},
        {8, "85-85-85", 5.0, 10, "Fátima"},
        {9, "85-AA-85", 5.5, 10, "Fátima"},
        {10, "60-BB-00", 6.0, 10, "Fátima"},
        {11, "00-BB-60", 6.5, 10, "Fátima"},
        {12, "94-CC-00", 7.0, 10, "Fátima"},
        {13, "00-DC-00", 7.5, 10, "Fátima"},
        {14, "00-BB-00", 8.0, 10, "Fátima"},
        {15, "00-AA-00", 8.5, 10, "Fátima"},
        {16, "85-XX-00", 9.0, 10, "Fátima"},
        {17, "94-94-94", 9.5, 10, "Fátima"},
        {18, "85-85-85",10.0, 10, "Fátima"},
        {19, "60-60-60",10.5, 10, "Fátima"} };
    Cliente cliente_teste[20] = {
        {111111111, "luis", "Rua de baixo", NULL},
        {222222222, "paulo", "Rua de cima", NULL},
        {333333333, "joaquim", "Rua da esquerda", NULL},
        {444444444, "albertina", "Rua da direita", NULL},
        {726347623, "daniel", "praça do centro", NULL},
        {638649271, "bruno", "praça ao lado", NULL},
        {119372931, "fernando", "rua do fernando", NULL},
        {682643264, "vanessa", "cidade feliz", NULL},
        { 64826471, "claudia", "rua atravessada", NULL},
        {101928498, "bernardo", "estrada do ar", NULL},
        {628303648, "rui", "rua sem nome", NULL},
        {356456456, "josé", "mais um nome de rua", NULL},
        {554555423, "antonio", "um nome de cidade", NULL},
        {729372984, "joao", "lisboa", NULL},
        {380934803, "jorge", "porto", NULL},
        {987654321, "joana", "santarem", NULL},
        {456789121, "antonia", "leiria", NULL},
        {732738231, "fernanda", "braga", NULL},
        {452134541, "bruna", "guimarães", NULL},
        {454645231, "vasco", "ultima rua à direita", NULL}
    };
    
    char locais[6][30] = { "Lisboa", "Fátima", "Coimbra", "Ourém", "Braga", "Faro" };

    TabelaHashPTR local_teste = criaTabelaHash(hash_function, 10000, comparalocalidades);
    for(i=0; i<6; i++)
        inserelocalidade(local_teste, locais[i]);

    for(i=1; i<6; i++)
        inserirligacao(local_teste, locais[i-1], locais[i], i*0.1, i*10);

    for(i=2; i<6; i++)
        inserirligacao(local_teste, locais[i-2], locais[i], i*0.1, i*10);

    for(i=0; i<20; i++)
        tree_insert(clientes, cliente_novo( cliente_teste[i].nif, cliente_teste[i].nome, cliente_teste[i].morada, cliente_teste[i].servicos ));

    for(i=0; i<20; i++)
        tree_insert( camioes, camiao_novo( camiao_teste[i].id, camiao_teste[i].matricula, camiao_teste[i].custo, camiao_teste[i].peso, camiao_teste[i].local ) );
    
    //for(i=0; i<20000; i++){
        serialize(local_teste, camioes, clientes);

        //deserialize();
    //}

    return 1;
    /* fim de testes de serialização */

    while( input != -1 ){
        input = printMenu(input);
        input = getInput(input, camioes, clientes, localidades);
    }
    return 0;
}

