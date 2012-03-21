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
    printf("{id=%d, matricula=\"%s\", consumo=%f}\n", thisCamiaoPt->id, thisCamiaoPt->matricula, thisCamiaoPt->custo );
}

CamiaoPt camiao_novo( unsigned int id, char *matricula, float custo ){
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

//
// Funções das Localidades
//



//
// Funções dos serviços anteriores
//



//
// Mais coisas?
// 



