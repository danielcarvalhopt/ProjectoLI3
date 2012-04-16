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
#include "mod_dijkstra.h"




void insereficheiro(TabelaHashPTR localidades)
{
    FILE *ficheiro; 
    char linha[80];

    ficheiro = fopen ("teste.txt", "rt");  
    while(fgets(linha, 80, ficheiro) != NULL)
    {
        linha[(strlen(linha)-1)]='\0';
        inserelocalidade(localidades, linha);
    }
    fclose(ficheiro); 
    imprimeColisoes(localidades); 
} 



int main(){
    int input=0;
    
    /** Declarar arrays de apontadores para as funções de comparação de dados */
    int (*comparaCamioes[DIM])(void*,void*) = {camiao_compararId, camiao_compararMatricula};
    int (*comparaClientes[DIM])(void*,void*) = {cliente_compararNif, cliente_compararNome};
    
    /** Inicializar estruturas de controlo dos vários tipos de dados */ 
    MainTreePt camioes = tree_new( comparaCamioes );
    MainTreePt clientes = tree_new( comparaClientes );
    TabelaHashPTR localidades = criaTabelaHash(hash_function, 10000, comparalocalidades);

    /** Inicializar os atalhos predefinidos do menu */
    inicializarAtalhos();
    insereficheiro(localidades);
    //samples
    //reSampleLocalidades(1);
    //reSampleUser();
    //return 0;

    while( input != -1 ){
        input = printMenu(input);
        input = getInput(input, camioes, clientes, localidades);
    }
    return 0;
}

