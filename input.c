/**
 * @file input.c
 * @brief Módulo de input (código)
 * */
#include <stdio.h>
#include <math.h>
#include <limits.h>
#include "utils.h"
#include "dados.h"
#include "input.h"
#include <stdlib.h>
#include <string.h>
#include "mod_error.h"

int lerStr(char **ptr){
    char strBuffer[1024];
    int i=0, excedeu=1;
    
    do{
        strBuffer[i] = getchar();
        i++;
    }while( strBuffer[i-1] != '\0' && strBuffer[i-1] != '\n' && i < 1023 );
    strBuffer[i-1] = '\0';
    if( i == 1023 ){
        clearInputBuffer();
        excedeu=-1;
    }
    
    if( (*ptr = allocStr(strBuffer)) == NULL )
        return 0;
    else
        return excedeu;
}


int readInt(){
    char c;
    int sinal=1, res=0;
    c=getchar();
    switch(c){
        case '-': sinal = -1;
        case '+': c=getchar();
                  break;
    }
    while( c != '\n' && res != INT_MAX){
        if( c >= '0' && c <= '9' ){
            res = res*10 + c - '0';
            c = getchar();
        }else{
            res = INT_MAX;
            clearInputBuffer();
        }
    }
    if( res != INT_MAX )
        res *= sinal;
    return res;
}

unsigned int readUInt(){
    char c;
    unsigned int res=0;
    c=getchar();
    switch(c){
        case '+': c=getchar();
                  break;
    }
    while( c != '\n' && res != INT_MAX){
        if( c >= '0' && c <= '9' ){
            res = res*10 + c - '0';
            c = getchar();
        }else{
            res = INT_MAX;
            clearInputBuffer();
        }
    }
    return res;
}

double readDouble(){
    double res;
    char strBuffer[128];
    char strDouble[128];
    char *ps = &strBuffer[0];
    char *pd = &strDouble[0];
    char ponto = 0;


    fgets(strBuffer, 127, stdin);

    if( *ps == '+' || *ps == '-' ){
        *pd = *ps;
        ps++;pd++;
    }

    while( *ps != '\n' && *ps != '\0' && ponto != 2){
        if( *ps >= '0' && *ps <= '9' ){
            *pd = *ps;
            pd++;ps++;
        }else if( *ps == '.' && ponto == 0 ){
            ponto = 1;
            *pd = '.';
            ps++;pd++;
        }else{
            ponto = 2;
        }
    }

    *pd = '\0'; //terminar a string do double

    if( ponto == 2 ) return NAN; //se o que foi lido nao for um numero, faz return NAN.

    sscanf(strDouble, "%lf", &res);
    return res;
}

//
//
// FUNÇÕES DE INPUT ESPEFÍFICAS
//
// LOCALIDADES

void inserelocalidadeinput (TabelaHashPTR table)
{   
    char *inputlocal=NULL;

    printf("Nome da localidade a inserir > ");
    lerStr(&inputlocal); 
    switch (inserelocalidade(table, inputlocal)){
        case -1: errorMessage(ERROR_LOCEXIST); break;
        case 0: errorMessage(ERROR_MEMALOC); break;
        case 1: errorMessage(ERROR_SUCCESS); break;
    }
}



void removelocalidadeinput(TabelaHashPTR table)
{
    char *inputlocal=NULL;

    printf("Nome da localidade a remover > ");
    lerStr(&inputlocal);
    switch (removerlocalidade(table, inputlocal))
    {
        case -1: errorMessage(ERROR_MEMALOC); break;
        case 0: errorMessage(ERROR_LOCNOTEXIST); break;
        case 1: errorMessage(ERROR_SUCCESS); break;
    }
}



void insereligacaoinput(TabelaHashPTR table){
    char *localorigem=NULL, *localdest=NULL;
    double custo, distancia;


    printf("Introduza localidade de origem > ");
    lerStr(&localorigem);
    printf("Introduza localidade de destino > ");
    lerStr(&localdest);
    printf("Introduza o custo de portagens > ");
    custo=readDouble();
    printf("Introduza a distância > ");
    distancia=readDouble();

    switch(inserirligacao(table,localorigem,localdest,custo,distancia)){
        case -2: errorMessage(ERROR_MEMALOC); break;
        case -1: errorMessage(ERROR_LOCNOTEXIST); break;
        case 0: errorMessage(ERROR_LIGLOCEXIST); break; 
        case 1: errorMessage(ERROR_SUCCESS); break;

    }

}


void removeligacaoinput(TabelaHashPTR table){
    char *localorigem=NULL, *localdest=NULL;
    printf("Introduza localidade de origem > ");
    lerStr(&localorigem);
    printf("Introduza localidade de destino > ");
    lerStr(&localdest);

    switch(removerligacao (table,localorigem, localdest)){
        case -1: errorMessage(ERROR_LOCNOTEXIST); break;
        case 0:  errorMessage(ERROR_LIGLOCNOTEXIST); break; 
        case 1: errorMessage(ERROR_SUCCESS); break;
    }
}



void editaligacaoinput(TabelaHashPTR localidades)
{
    char *localorigem=NULL, *localdest=NULL;
    printf("Introduza localidade de origem > ");
    lerStr(&localorigem);
    printf("Introduza localidade de destino > ");
    lerStr(&localdest);
    LocalidadePTR localidadeida = crialocalidade(localorigem);
    LocalidadePTR localidadevinda = crialocalidade(localdest);
    LigacoesidaPTR localidadedestino = crialigacaoida(localdest, 0,0);

    LocalidadePTR aux;
    double custo, distancia;

    if ((procuraTabelaHash(localidades, localidadeida)==NULL) || (procuraTabelaHash(localidades, localidadevinda)==NULL))
        errorMessage(ERROR_LOCNOTEXIST);
    else{
        aux = (((LinkedListPTR)procuraTabelaHash(localidades, localidadeida))->extdata);
        if ((procuraElementoLista(aux->ligacoesida,localidadedestino)==NULL))
            errorMessage(ERROR_LIGLOCNOTEXIST);
        else{
            printf("Irá alterar a ligação entre %s e %s.\n", localorigem,localdest );
            printf("Novo custo da ligação > ");
            custo=readDouble();
            printf("Nova distância da ligação > ");
            distancia=readDouble();
            removerligacao(localidades, localorigem, localdest);
            inserirligacao(localidades, localorigem, localdest,custo,distancia);
            errorMessage(ERROR_SUCCESS);
        }
    }

}

void imprimelistaligacoesinput(TabelaHashPTR localidades)
{
    char *nomelocalidade=NULL;
    printf("Introduza localidade de origem > ");
    lerStr(&nomelocalidade);
    LocalidadePTR localidade = crialocalidade(nomelocalidade);
    LocalidadePTR aux;

    if (procuraTabelaHash(localidades, localidade)==NULL)
        errorMessage(ERROR_LOCNOTEXIST);
    else
    {
        aux = (((LinkedListPTR)procuraTabelaHash(localidades, localidade))->extdata);
        if (aux->ligacoesida->elems==NULL) errorMessage(ERROR_NOLIGS);
        else
        imprimelistaligacoes(aux->ligacoesida->elems);
    }
}

void imprimeLocalidades (TabelaHashPTR table){
    int n= table->totalcells;
    MainListPTR *aux = table->arraycell;
    int i;
    for (i=0; i<n; i++){
        printf("%d\n", i);
        imprimelista(aux[i]->elems);
    }

}

void imprimelista(LinkedListPTR lista){
    LinkedListPTR aux=lista;
    LocalidadePTR local;
    while (aux){
        local = aux->extdata;
        printf("%s",(char*)local->nome);
        aux=aux->prox;
    }
}

void imprimelistaligacoes(LinkedListPTR lista){
    LinkedListPTR aux=lista;
    LigacoesidaPTR local;
    while (aux!=NULL){
        local = aux->extdata;
        printf("%s %0.2f %0.2f\n",(char*)local->nome, (double)local->custo, (double)local->distancia);
        aux=aux->prox;
    }
}

//
// CAMIOES
//

void camiaoi_insere(MainTreePt camioes, TabelaHashPTR localidades){
    unsigned int id;
    char *matricula=NULL, *local=NULL, vazia[1]={'\0'};
    LinkedListPTR localidade=NULL;
    double custo, peso;

    printf("Introduza o ID > ");
    while( isUInt(id = readUInt()) == 0 )
        printf("Erro: Valor inválido (veja as instruções acima)"); //erro

    printf("Introduza a matrícula > ");
    lerStr( &matricula);
    printf("matricula: %s\n", matricula);
    printf("Custo (por Km) > ");
    if( isDouble(custo = readDouble()) == 0 )
        printf("Erro: Valor inválido (veja as instruções acima)"); //erro
    printf("Peso máximo da carga > ");
    if( isDouble(peso = readDouble()) == 0 )
        printf("Erro: Valor inválido (veja as instruções acima)"); //erro
    
    printf("Localidade actual > ");
    lerStr( &local );
    while( (localidade = procuraTabelaHash( localidades, crialocalidade(local) ) ) == NULL && strcmp(local,vazia) != 0 ){
        printf("Erro: Localidade não foi encontrada. Para cancelar apenas pressione [ENTER].\nLocalidade actual > ");
        lerStr( &local );
    }
    free(localidade);
    if( strcmp(local,vazia) == 0 ){
        printf("Cancelou a introdução.\nPressione [ENTER] para voltar ao menu.");
        free(matricula);
        free(local);
    }else
        if( tree_insert( camioes, camiao_novo(id, matricula, custo, peso, local) ) == 1 )
            printf("Dados introduzidos com sucesso!");
        else
            printf("Já existe um Camião com esse ID ou Matrícula");
}


