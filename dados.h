#ifndef DADOS_H_INCLUDED
#define DADOS_H_INCLUDED

#include "mod_lista_ligada.h"
#include "mod_avl_n_dimensional.h"
// metemos aqui as definições das estruturas de dados e das funções de comparação, output, clone, etc
//
// as definições das funções devem ser do género:
// tipo transporte_novo(argumentos)
// tipo transporte_compara(argumentos)
//
//


//
// Funções e estruturas dos camiões
//

typedef struct sCamiao{
    unsigned int id;
    char *matricula;
    float custo; //por Km
    float peso; //peso máximo que pode transportar
    //falta localidade actual
} Camiao, *CamiaoPt;

void camiao_dump( void* camiao );
int camiao_compararId(void* camiaoUm, void* camiaoDois);
int camiao_compararMatricula(void* camiaoUm, void* camiaoDois);
CamiaoPt camiao_novo( unsigned int id, char *matricula, float custo, float peso );

//
// Funções e estruturas dos clientes
//

typedef struct sCliente{
    unsigned int nif; //numero de identificacao fiscal = contribuinte
    char *nome;
    char *morada;
    MainListPTR servicos;
} Cliente, *ClientePt;

int cliente_compararNif(void* clienteUm, void* clienteDois);
int cliente_compararNome(void* clienteUm, void* clienteDois);
void cliente_dump( void* cliente );
ClientePt cliente_novo( unsigned int nif, char *nome, char *morada, MainListPTR servicos );
int cliente_substituiPeloNome( MainTreePt clientesPt, char *procuraNome, unsigned int nif, char *nome, char *morada );
int cliente_substituiPeloNif( MainTreePt clientesPt, unsigned int procuraNif, unsigned int nif, char *nome, char *morada );
MainListPTR cliente_getServico( TreePt thisTreePt );



//
// Funções e estruturas das Localidades
//

typedef struct sLocal{

} Local, *LocalPt;

//
// Funções e estruturas dos serviços anteriores
//

typedef struct sServico{

} Servico, *ServicoPt;

//
// Mais coisas?
// 


#endif /* DADOS_H_INCLUDED */
