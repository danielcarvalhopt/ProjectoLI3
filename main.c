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




void insereLocalidadesFicheiro(TabelaHashPTR localidades)
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
     
} 



void insereLigacoesFicheiro(TabelaHashPTR localidades)
{
    FILE *ficheiro; 
    char linha[1000];
    int i,j,k,l, res=0, res2=0;
    ficheiro = fopen ("ligacoes.txt", "rt");  
    while(fgets(linha, 1000, ficheiro) != NULL)
    {
        char origem[200]={'\0'};
        char destino[200]={'\0'};
        res=res2=0;
        for(i=0; linha[i]!=':';i++)
            {
                origem[i]=linha[i];origem[(strlen(origem)+1)]='\0';
            }
        i++;
        for(j=0; linha[i]!=':';j++,i++)
            {
                destino[j]=linha[i];
                destino[(strlen(destino)+1)]='\0';
            }
        i++;
        for(k=0; linha[i]!=':'; k++,i++)
            res=res*10+(linha[i]-'0');
        i++;
        for(l=0; linha[i]!='\n'; l++,i++)
            res2=res2*10+(linha[i]-'0');
        i++;
        inserirligacao(localidades, origem, destino, res2, res);
    }
    fclose(ficheiro);  
} 

//using namespace std; 

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
    insereLocalidadesFicheiro(localidades);
    insereLigacoesFicheiro(localidades);
    //
 /*   inserelocalidade(localidades,"START");
    inserelocalidade(localidades,"A");
    inserelocalidade(localidades,"B");
    inserelocalidade(localidades,"C");
    inserelocalidade(localidades,"D");
    inserelocalidade(localidades,"E");    inserelocalidade(localidades,"F");
    inserelocalidade(localidades,"END");
    inserirligacao(localidades,"START","A",3,4);
    inserirligacao(localidades,"A","B",1,10);
    inserirligacao(localidades,"B","END",3,20);
    inserirligacao(localidades,"START","C",10,2);
    inserirligacao(localidades,"C","END",10,40);
    inserirligacao(localidades,"C","D",3,2);
    inserirligacao(localidades,"D","E",2,2);
    inserirligacao(localidades,"E","END",2,3);*/
    costCheapestPath(localidades, "Bedoiros", "Soutaria",1);
    //samples
    //reSampleLocalidades(1);
    //reSampleUser();
    //return 0;
imprimeColisoes(localidades);
    while( input != -1 ){
        input = printMenu(input);
        input = getInput(input, camioes, clientes, localidades);
    }
    return 0;
}

