#include "dados.h"

//
// Funções dos camiões
//

int camiao_compararId(void* camiaoUm, void* camiaoDois){
    return intcmp( (CamiaoPt)camiaoUm->id, (CamiaoPt)camiaoDois->id );
}

int camiao_compararMatricula(void* camiaoUm, void* camiaoDois){
    return strcmp( (CamiaoPt)camiaoUm->matricula, (CamiaoPt)camiaoDois->matricula );
}

//
// Funções dos clientes
//

int cliente_compararNif(void* clienteUm, void* clienteDois){
    return uintcmp( (ClientePt)clienteUm->nif, (ClientePt)clienteDois->nif );
}

int cliente_compararNome(void* clienteUm, void* clienteDois){
    return strcmp( (ClientePt)clienteUm->nome, (ClientePt)clienteDois->nome );
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



