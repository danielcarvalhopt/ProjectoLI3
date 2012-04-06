#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "mod_avl_n_dimensional.h"
#include "dados.h"
#include "utils.h"
#include "input.h"

//
// Funções dos camiões
//

int camiao_compararId(void* camiaoUm, void* camiaoDois){
    return uintcmp( ((CamiaoPt)camiaoUm)->id, ((CamiaoPt)camiaoDois)->id );
}

int camiao_compararMatricula(void* camiaoUm, void* camiaoDois){
    return strcmp( ((CamiaoPt)camiaoUm)->matricula, ((CamiaoPt)camiaoDois)->matricula );
}

void camiao_dump( void* camiao ){
    CamiaoPt thisCamiaoPt = (CamiaoPt)camiao;
    printf("{id=%3d, matricula=\"%s\", consumo=%f}\n", thisCamiaoPt->id, thisCamiaoPt->matricula, thisCamiaoPt->custo );
}

CamiaoPt camiao_novo( unsigned int id, char *matricula, double custo, double peso ){
    CamiaoPt novoCamiaoPt = NULL;
    if( (novoCamiaoPt = malloc( sizeof(Camiao)) ) == NULL ) return NULL;

    /*tentar alocar espaço para a matricula
    if( (novoCamiaoPt->matricula = allocStr( novoCamiaoPt->matricula, matricula ) ) == NULL ){
        free(novoCamiaoPt);
        return NULL;
    }
    */

    // ou meter só o apontador
    novoCamiaoPt->matricula = matricula;
    novoCamiaoPt->id = id;
    novoCamiaoPt->custo = custo;
    novoCamiaoPt->peso = peso;
    return novoCamiaoPt;
}

//
// Funções dos clientes
//

int cliente_compararNif(void* clienteUm, void* clienteDois){
    return uintcmp( ((ClientePt)clienteUm)->nif, ((ClientePt)clienteDois)->nif );
}

int cliente_compararNome(void* clienteUm, void* clienteDois){
    return strcmp( ((ClientePt)clienteUm)->nome, ((ClientePt)clienteDois)->nome );
}

void cliente_dump( void* cliente ){
    ClientePt thisClientePt = (ClientePt)cliente;
    printf("{id=%09d, nome=\"%s\", morada=\"%s\"}\n", thisClientePt->nif, thisClientePt->nome, thisClientePt->morada );
}

ClientePt cliente_novo( unsigned int nif, char *nome, char *morada, MainListPTR servicos ){
    ClientePt novoClientePt = NULL;
    if( (novoClientePt = malloc( sizeof(Cliente)) ) == NULL ) return NULL;

    // meter só o apontador
    novoClientePt->nome = nome;
    novoClientePt->nif = nif;
    novoClientePt->morada = morada;
    novoClientePt->servicos = servicos;
    return novoClientePt;
}

int cliente_substituiPeloNome( MainTreePt clientesPt, char *procuraNome, unsigned int nif, char *nome, char *morada ){
    ClientePt aux = cliente_novo( 0, procuraNome, "", NULL );
    TreePt thisTreePt = tree_search( clientesPt, aux, 1);
    free(aux);
    if( thisTreePt == NULL ) return -1;
    ClientePt modificado = cliente_novo( nif, nome, morada, cliente_getServico( thisTreePt ) );
    tree_remove( clientesPt, thisTreePt->node );
    return tree_insert( clientesPt, modificado );
}

MainListPTR cliente_getServico( TreePt thisTreePt ){
    if( thisTreePt == NULL ) return NULL;
    return ((ClientePt)tree_getElem(thisTreePt))->servicos;
}

int cliente_substituiPeloNif( MainTreePt clientesPt, unsigned int procuraNif, unsigned int nif, char *nome, char *morada ){
    ClientePt aux = cliente_novo( procuraNif, "", "", NULL );
    TreePt thisTreePt = tree_search( clientesPt, aux, 0);
    free(aux);
    if( thisTreePt == NULL ) return -1;
    ClientePt modificado = cliente_novo( nif, nome, morada, cliente_getServico( thisTreePt ) );
    tree_remove( clientesPt, thisTreePt->node );
    return tree_insert( clientesPt, modificado );
}


//
// Funções das Localidades
//

int hash_function (void *localidade, int hashsize)
{
    LocalidadePTR localA = (LocalidadePTR)localidade; 
    char *nome;
    long int res=1; int i;

    nome=(char*)localA->nome;
    for (i=0; nome[i]!='\0'; i++)
    {
        res+=((int)nome[i])*(i+1)*13;
    }
    int hashkey= (int)(res%(long int)hashsize);
    return hashkey;
}






int comparalocalidades (void *a, void *b){
    LocalidadePTR localA = (LocalidadePTR)a;
    LocalidadePTR localB = (LocalidadePTR)b;
    char *nomeA, *nomeB;
    nomeA=(char*)localA->nome;
    nomeB=(char*)localB->nome;

    return (strcmp(nomeA,nomeB));
}

int compareligacoesida (void *a, void *b){
    LigacoesidaPTR localA = (LigacoesidaPTR)a;
    LigacoesidaPTR localB = (LigacoesidaPTR)b;
    char *nomeA, *nomeB;
    nomeA=(char*)localA->nome;
    nomeB=(char*)localB->nome;

    return (strcmp(nomeA,nomeB));
}

int compareligacoesvinda (void *a, void *b){
    LigacoesvindaPTR localA = (LigacoesvindaPTR)a;
    LigacoesvindaPTR localB = (LigacoesvindaPTR)b;

    char *nomeA, *nomeB;
    nomeA=(char*)localA->nome;
    nomeB=(char*)localB->nome;

    return (strcmp(nomeA,nomeB));
}

LocalidadePTR crialocalidade (char* nome){
    LocalidadePTR localidade;

    localidade = (LocalidadePTR)malloc(sizeof(struct Localidade));
    localidade->nome=allocStr(nome);
    localidade->ligacoesida=criaListaLigada(compareligacoesida);
    localidade->ligacoesvinda=criaListaLigada(compareligacoesvinda);

    return localidade;
}

int inserelocalidade (TabelaHashPTR table, char *nome){
    LocalidadePTR localidade = crialocalidade(nome);
    if (procuraTabelaHash(table, localidade)!=NULL) return -1;

    return insereElementoTabelaHash (table, localidade);
}

int removerlocalidade (TabelaHashPTR table, char *nome){
    LocalidadePTR aux,localidade;
    if ((aux = crialocalidade(nome))==NULL) return -1;

    if (procuraTabelaHash(table, aux)==NULL) return 0;
    localidade=procuraTabelaHash(table,aux)->extdata;
    while(localidade->ligacoesvinda->elems!=NULL)
    {
        LigacoesvindaPTR auxlig = localidade->ligacoesvinda->elems->extdata;
        removerligacao(table,auxlig->nome, nome);
    }

    return (apagaElementoTabelaHash(table, aux)); 
}

LigacoesidaPTR crialigacaoida (char* nome, float custo, float distancia){
    LigacoesidaPTR ligacao;

    ligacao = malloc (sizeof(struct Ligacoesida));
    ligacao->nome = allocStr(nome);
    ligacao->custo=custo;
    ligacao->distancia=distancia;

    return ligacao;
}

LigacoesvindaPTR crialigacaovinda (char* nome){
    LigacoesvindaPTR ligacao;

    ligacao = (LigacoesvindaPTR)malloc(sizeof(struct Ligacoesvinda));
    ligacao->nome=allocStr(nome);

    return ligacao;
}

int inserirligacao(TabelaHashPTR table, char *nomeorigem, char *nomedestino, float custo, float distancia){
    LocalidadePTR localidadeida = crialocalidade(nomeorigem);
    LocalidadePTR localidadevinda = crialocalidade(nomedestino);
    LigacoesidaPTR localidadedestino = crialigacaoida(nomedestino, custo,distancia);
    LigacoesvindaPTR localidadeorigem = crialigacaovinda(nomeorigem);

    LocalidadePTR aux, aux2;

    if ((procuraTabelaHash(table, localidadeida)==NULL) || (procuraTabelaHash(table, localidadevinda)==NULL)) return -1;
    else{
        aux = (((LinkedListPTR)procuraTabelaHash(table, localidadeida))->extdata);
        aux2 = (((LinkedListPTR)procuraTabelaHash(table, localidadevinda))->extdata);
        if ((procuraElementoLista(aux->ligacoesida,localidadedestino)!=NULL) || (procuraElementoLista(aux2->ligacoesvinda, localidadeorigem)!=NULL))
            return 0;
        else{
            insereListaOrdenado(aux->ligacoesida,localidadedestino);
            insereListaOrdenado(aux2->ligacoesvinda, localidadeorigem);
        }
    }
    return 1;
}



int removerligacao (TabelaHashPTR table, char *nomeorigem, char *nomedestino){

    LocalidadePTR localidadeida = crialocalidade(nomeorigem);
    LocalidadePTR localidadevinda = crialocalidade(nomedestino);
    LigacoesidaPTR localidadedestino = crialigacaoida(nomedestino, 0,0);
    LigacoesvindaPTR localidadeorigem = crialigacaovinda(nomeorigem);

    LocalidadePTR aux, aux2;

    if ((procuraTabelaHash(table, localidadeida)==NULL) || (procuraTabelaHash(table, localidadevinda)==NULL)) return -1;
    else{
        aux = (((LinkedListPTR)procuraTabelaHash(table, localidadeida))->extdata);
        aux2 = (((LinkedListPTR)procuraTabelaHash(table, localidadevinda))->extdata);
        if ((procuraElementoLista(aux->ligacoesida,localidadedestino)==NULL) || (procuraElementoLista(aux2->ligacoesvinda, localidadeorigem)==NULL))
            return 0;
        else{
            apagaElementoLista(aux->ligacoesida,localidadedestino);
            apagaElementoLista(aux2->ligacoesvinda, localidadeorigem);
        }
    }
    return 1;
}





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
    float custo, distancia;


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
    float custo, distancia;

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


void imprimelista(LinkedListPTR lista){
    LinkedListPTR aux=lista;
    LocalidadePTR local;
    while (aux){
        local = aux->extdata;
        printf("%s",(char*)local->nome);
        aux=aux->prox;
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

void imprimelistaligacoes(LinkedListPTR lista){
    LinkedListPTR aux=lista;
    LigacoesidaPTR local;
    while (aux!=NULL){
        local = aux->extdata;
        printf("%s %0.2f %0.2f\n",(char*)local->nome, (float)local->custo, (float)local->distancia);
        aux=aux->prox;
    }
}

LocalidadePTR cloneLocalidade (LocalidadePTR localidade)
{
    LocalidadePTR novo;
    novo=(LocalidadePTR)malloc(sizeof(localidade));

    

}


//
// Funções dos serviços anteriores
//
int cliente_insereServico( ClientePt thisCliente, CamiaoPt thisCamiao, double custo, double peso, LocalidadePTR origem, LocalidadePTR carga, LocalidadePTR destino ){
    ServicoPt thisServico;
    int ret = 1;
    if( (thisServico = (ServicoPt) malloc(sizeof(Servico))) != NULL ){
        if( putTime(&thisServico->datahora) == 1 ){
            thisServico->camiao = thisCamiao;
            thisServico->custo = custo;
            thisServico->peso = peso;
            thisServico->origem = origem;
            thisServico->carga = carga;
            thisServico->destino = destino;

            if( insereListaInicio( thisCliente->servicos, thisServico ) == 1 )
                ret = 1;
            else
                ret = 0;
        }else ret = 0;
    }else ret = -1;

    if( ret == 0 ){ //nao conseguiu inserir ou nao conseguiu gerar a data e hora
        free(thisServico->datahora);
        free(thisServico);
    }

    return ret;
}

int cliente_comparaServico( void* servUm, void* servDois ){
    return strcmp( ((ServicoPt)servUm)->datahora, ((ServicoPt)servDois)->datahora );
}

//
// Mais coisas?
// 



