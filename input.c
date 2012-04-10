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

char* readStr(char *ptr){
    char strBuffer[1024];
    int i=0;
    
    do{
        strBuffer[i] = getchar();
        i++;
    }while( strBuffer[i-1] != '\0' && strBuffer[i-1] != '\n' && i < 1023 );
    strBuffer[i] = '\0';
    
    //fgets(strBuffer, 1023, stdin);
    ptr = allocStr(strBuffer);
    return ptr;
}

int lerStr(char *ptr){
    char strBuffer[1024];
    int i=0, excedeu=1;
    
    do{
        strBuffer[i] = getchar();
        i++;
    }while( strBuffer[i-1] != '\0' && strBuffer[i-1] != '\n' && i < 1023 );
    strBuffer[i] = '\0';
    if( i == 1023 ){
        clearInputBuffer();
        excedeu=-1;
    }
    
    if( (ptr = allocStr(strBuffer)) == NULL )
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
        }else if( (*ps == ',' || *ps == '.') && ponto == 0 ){
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
//

void inserelocalidadeinput (TabelaHashPTR table)
{   
    char *inputlocal=NULL,*aux=NULL;

    printf("Nome da localidade a inserir > ");
    aux=readStr(inputlocal); 
    switch (inserelocalidade(table, aux)){
        case -1: printf("Localidade já existe!"); break;
        case 0: printf("Não foi possível inserir a localidade por falta de memória!");break;
        case 1: printf("Localidade inserida com sucesso!");break;
    }
}



void removelocalidadeinput(TabelaHashPTR table)
{
    char *inputlocal=NULL,*aux=NULL;

    printf("Nome da localidade a remover > ");
    aux=readStr(inputlocal);
    switch (removerlocalidade(table, aux))
    {
        case -1: printf("Não foi possível completar a operação por falta de memória!");break;
        case 0: printf("Localidade não existe!"); break;
        case 1: printf("Localidade removida com sucesso!");break;
    }
}



void insereligacaoinput(TabelaHashPTR table){
    char *localorigem=NULL, *localdest=NULL, *aux=NULL,*aux2=NULL;
    double custo, distancia;


    printf("Introduza localidade de origem > ");
    localorigem= readStr(aux);
    printf("Introduza localidade de destino > ");
    localdest= readStr(aux2);
    printf("Introduza o custo de portagens > ");
    custo=readDouble();
    printf("Introduza a distância > ");
    distancia=readDouble();

    switch(inserirligacao(table,localorigem,localdest,custo,distancia)){
        case -2:printf("Não foi possível completar a operação por falta de memória! ");break;
        case -1: printf("Uma ou ambas as localidades não existem!");break;
        case 0: printf("A ligação já existe!");break; 
        case 1: printf("A ligação foi inserida com sucesso!");break;

    }

}


void removeligacaoinput(TabelaHashPTR table){
    char *localorigem=NULL, *localdest=NULL, *aux=NULL,*aux2=NULL;
    printf("Introduza localidade de origem > ");
    localorigem= readStr(aux);
    printf("Introduza localidade de destino > ");
    localdest= readStr(aux2);

    switch(removerligacao (table,localorigem, localdest)){
        case -1: printf("Uma ou ambas as localidades não existem!");break;
        case 0: printf("A ligação não existe!");break; 
        case 1: printf("A ligação foi removida com sucesso!");break;
    }
}



void editaligacaoinput(TabelaHashPTR localidades)
{
    char *localorigem=NULL, *localdest=NULL, *auxc=NULL,*aux2c=NULL;
    printf("Introduza localidade de origem > ");
    localorigem= readStr(auxc);
    printf("Introduza localidade de destino > ");
    localdest= readStr(aux2c);
    LocalidadePTR localidadeida = crialocalidade(localorigem);
    LocalidadePTR localidadevinda = crialocalidade(localdest);
    LigacoesidaPTR localidadedestino = crialigacaoida(localdest, 0,0);

    LocalidadePTR aux;
    double custo, distancia;

    if ((procuraTabelaHash(localidades, localidadeida)==NULL) || (procuraTabelaHash(localidades, localidadevinda)==NULL)) printf("Uma ou ambas as localidades não existem!");
    else{
        aux = (((LinkedListPTR)procuraTabelaHash(localidades, localidadeida))->extdata);
        if ((procuraElementoLista(aux->ligacoesida,localidadedestino)==NULL))
            printf("A ligação que quer editar não existe!");
        else{
            printf("Irá alterara a ligação entre %s e %s.\n", localorigem,localdest );
            printf("Novo custo da ligação > ");
            custo=readDouble();
            printf("Nova distância da ligação > ");
            distancia=readDouble();
            removerligacao(localidades, localorigem, localdest);
            inserirligacao(localidades, localorigem, localdest,custo,distancia);
            printf("Ligação alterada\n");
        }
    }

}

void imprimelistaligacoesinput(TabelaHashPTR localidades)
{
    char *nomelocalidade=NULL, *auxc=NULL;
    printf("Introduza localidade de origem > ");
    nomelocalidade=readStr(auxc);
    LocalidadePTR localidade = crialocalidade(nomelocalidade);
    LocalidadePTR aux;

    if (procuraTabelaHash(localidades, localidade)==NULL) {printf("Localidade não existe");}
    else
    {
        aux = (((LinkedListPTR)procuraTabelaHash(localidades, localidade))->extdata);
        if (aux->ligacoesida->elems==NULL) printf("Não existem ligações nesta localidade!");
        else
        imprimelistaligacoes(aux->ligacoesida->elems);
    }
}

void imprimeLocalidades (TabelaHashPTR table){
    int n= table->totalcells;
    MainListPTR *aux = table->arraycell;
    int i;
    for (i=0; i<n; i++){
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





