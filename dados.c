#include "dados.h"
#include "utils.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

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

CamiaoPt camiao_novo( unsigned int id, char *matricula, float custo, float peso ){
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
    novoCamiaoPt->volume = volume;
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

ClientePt cliente_novo( unsigned int nif, char *nome, char *morada ){
    ClientePt novoClientePt = NULL;
    if( (novoClientePt = malloc( sizeof(Cliente)) ) == NULL ) return NULL;

    // meter só o apontador
    novoClientePt->nome = nome;
    novoClientePt->nif = nif;
    novoClientePt->morada = morada;
    return novoClientePt;
}

int cliente_substituiPeloNome( MainTreePt clientesPt, char *procuraNome, unsigned int nif, char *nome, char *morada ){
    ClientePt aux = cliente_novo( 0, procuraNome, "" );
    TreePt thisTreePt = tree_search( clientesPt, aux, 1);
    free(aux);
    if( thisTreePt == NULL ) return NULL;
    ClientePt modificado = cliente_novo( nif, nome, morada );
    cliente_setServico( modificado, thisTreePt );
    tree_dispose( thisTreePt );
    return tree_insert( clientesPt, modificado );
}

void cliente_setServico( ClientePt thisClientePt, TreePt thisTreePt ){
    if( thisClientePt == NULL || thisTreePt == NULL ) return;
    thisClientePt->servicos = ((ClientePt)tree_getElem(thisTreePt))->servicos;
}

ClientePt cliente_substituiPeloNif( MainTreePt thisMainTreePt, unsigned int procuraNif, unsigned int nif, char *nome, char *morada ){
    return NULL;
}


//
// Funções das Localidades
//



//
// Funções dos serviços anteriores
//



//
// Mais coisas?
// 



