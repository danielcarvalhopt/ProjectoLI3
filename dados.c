#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "mod_avl_n_dimensional.h"
#include "dados.h"
#include "utils.h"
#include "input.h"
#include "mod_error.h"
#include "mod_graph.h"

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

CamiaoPt camiao_novo( unsigned int id, char *matricula, double custo, double peso, char *local ){
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
    novoCamiaoPt->local = local;
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

ClientePt cliente_procuraNif( MainTreePt clientesPt, unsigned int nif){
    ClientePt aux = cliente_novo( nif, "", "", NULL );
    TreePt thisTreePt = tree_search( clientesPt, aux, 0);
    free(aux);
    return (ClientePt)thisTreePt->node;
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
    unsigned long long int res=11; int i, j=0; int hashing[]={2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109};

    nome=(char*)localA->nome;

    for (i=0;nome[i]!='\0' && j<27;i++)
    {
                if(((nome[i]>='A')&&(nome[i]<='Z'))||((nome[i]>='a')&&(nome[i]<='z'))){
                if(nome[i]!='a'||nome[i]!='e'||nome[i]!='e'||nome[i]!='o'||nome[i]!='u')
                {
                res+=abs(((int)nome[i])*(i+1)*hashing[j]);}
                if((nome[i]=='a'&&nome[i+1]=='\0') || ((nome[i]=='o'&&nome[i+1]=='\0')&&((strlen(nome)%7)==0)))
                    res+=abs(hashing[j]+nome[0]+(hashing[j]%30));

                j=hashing[j]%30;
            }
    }
    int hashkey= (int)(res%(unsigned long long int)hashsize);
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
    if (procuraTabelaHash(table, localidade)!=NULL) {freeLocalidade(localidade); return -1;}
    return insereElementoTabelaHash(table, localidade);
}

int removerlocalidade (TabelaHashPTR table, char *nome){
    LocalidadePTR aux,localidade;
    if ((aux = crialocalidade(nome))==NULL) return -1;

    if (procuraTabelaHash(table, aux)==NULL)  return 0;
    localidade=procuraTabelaHash(table,aux)->extdata;
    while(localidade->ligacoesvinda->elems!=NULL)
    {
        LigacoesvindaPTR auxlig = localidade->ligacoesvinda->elems->extdata;
        removerligacao(table,auxlig->nome, nome);
    }
    freeLocalidade(aux);
    return (apagaElementoTabelaHash(table, aux)); 
}

LigacoesidaPTR crialigacaoida (char* nome, double custo, double distancia){
    LigacoesidaPTR ligacao;

    ligacao = malloc (sizeof(struct Ligacoesida));
    ligacao->nome =allocStr(nome);
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

int inserirligacao(TabelaHashPTR table, char *nomeorigem, char *nomedestino, double custo, double distancia){
    LocalidadePTR localidadeida = crialocalidade(nomeorigem);
    LocalidadePTR localidadevinda = crialocalidade(nomedestino);
    LigacoesidaPTR localidadedestino = crialigacaoida(nomedestino, custo,distancia);
    LigacoesvindaPTR localidadeorigem = crialigacaovinda(nomeorigem);

    LocalidadePTR aux, aux2;

    if ((procuraTabelaHash(table, localidadeida)==NULL) || (procuraTabelaHash(table, localidadevinda)==NULL)) 
        {
            freeLocalidade(localidadeida);freeLocalidade(localidadevinda);
            freeLigacaoIda(localidadedestino);freeLigacaoVinda(localidadeorigem);
            return -1;
        }
    else{
        aux = (((LinkedListPTR)procuraTabelaHash(table, localidadeida))->extdata);
        aux2 = (((LinkedListPTR)procuraTabelaHash(table, localidadevinda))->extdata);
        if ((procuraElementoLista(aux->ligacoesida,localidadedestino)!=NULL) || (procuraElementoLista(aux2->ligacoesvinda, localidadeorigem)!=NULL))
            {
                freeLocalidade(localidadeida);freeLocalidade(localidadevinda);
                freeLigacaoIda(localidadedestino);freeLigacaoVinda(localidadeorigem); 
                return 0;
            }
        else{
            insereListaOrdenado(aux->ligacoesida,localidadedestino);
            insereListaOrdenado(aux2->ligacoesvinda, localidadeorigem);
        }
    }
    freeLocalidade(localidadeida);freeLocalidade(localidadevinda);
    return 1;
}



int removerligacao (TabelaHashPTR table, char *nomeorigem, char *nomedestino){

    LocalidadePTR localidadeida = crialocalidade(nomeorigem);
    LocalidadePTR localidadevinda = crialocalidade(nomedestino);
    LigacoesidaPTR localidadedestino = crialigacaoida(nomedestino, 0,0);
    LigacoesvindaPTR localidadeorigem = crialigacaovinda(nomeorigem);

    LocalidadePTR aux, aux2;

    if ((procuraTabelaHash(table, localidadeida)==NULL) || (procuraTabelaHash(table, localidadevinda)==NULL))
        {
            freeLocalidade(localidadeida);freeLocalidade(localidadevinda);
            freeLigacaoIda(localidadedestino);freeLigacaoVinda(localidadeorigem);
            return -1;
        }
    else{
        aux = (((LinkedListPTR)procuraTabelaHash(table, localidadeida))->extdata);
        aux2 = (((LinkedListPTR)procuraTabelaHash(table, localidadevinda))->extdata);
        if ((procuraElementoLista(aux->ligacoesida,localidadedestino)==NULL) || (procuraElementoLista(aux2->ligacoesvinda, localidadeorigem)==NULL))
            {
                freeLocalidade(localidadeida);freeLocalidade(localidadevinda);
                freeLigacaoIda(localidadedestino);freeLigacaoVinda(localidadeorigem);     
                return 0;
            }
        else{
            apagaElementoLista(aux->ligacoesida,localidadedestino);
            apagaElementoLista(aux2->ligacoesvinda, localidadeorigem);
        }
    }
    freeLocalidade(localidadeida);freeLocalidade(localidadevinda);
    freeLigacaoIda(localidadedestino);freeLigacaoVinda(localidadeorigem); 
    return 1;
}


void freeLigacaoIda(LigacoesidaPTR ligacao)
{
    free(ligacao->nome);
    free(ligacao);
}

void freeLigacaoVinda(LigacoesvindaPTR ligacao)
{
    free(ligacao->nome);
    free(ligacao);
}


void freeLocalidade(LocalidadePTR localidade)
{
    LinkedListPTR auxIda = localidade->ligacoesida->elems, auxVinda=localidade->ligacoesvinda->elems, ant;

    free(localidade->nome);
    while (auxIda != NULL) {
        free(auxIda->extdata);
        ant=auxIda;
        auxIda = auxIda->prox;
        free(ant);
    }
    while (auxVinda != NULL) {
        free(auxVinda->extdata);
        ant=auxVinda;
        auxVinda = auxVinda->prox;
        free(ant);
    }
    free(localidade);
}
//
// Caminho mais barato
//


double costCheapestPath(TabelaHashPTR localidades, char* localidadeorigem, char* localidadedestino, double custoCamiaoKm)
{
    GraphPTR graph; graph=cheapestPathGraph(localidades,localidadeorigem, localidadedestino, custoCamiaoKm);
    GraphElemPTR destino=(GraphElemPTR)(procuraTabelaHash(graph, newVertex(localidadedestino, "",0,0,0,0)))->extdata;

    while(strcmp(destino->nome,localidadeorigem)!=0)
    {
        printf("%s <- ",destino->nome);
        destino=(GraphElemPTR)(procuraTabelaHash(graph, newVertex(destino->nomeAnterior, "",0,0,0,0)))->extdata;
    }
}



//
// Funções dos serviços anteriores
//
int cliente_insereServico( MainTreePt clientesPt, unsigned int nif, char *camiao, double custo, double peso, char *origem, char *carga, char *destino ){
    ServicoPt thisServico;

    ClientePt thisCliente = cliente_procuraNif(clientesPt, nif);
    if( thisCliente == NULL )
        return -2;
    int ret = 1;
    if( (thisServico = (ServicoPt) malloc(sizeof(Servico))) != NULL ){
        if( putTime(&thisServico->datahora) == 1 ){
            thisServico->camiao = camiao;
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



