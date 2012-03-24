
#ifndef LOCALIDADES_H_INCLUDED
#define LOCALIDADES_H_INCLUDED

#include "mod_lista_ligada.h"
#include "mod_tabela_hash.h"

typedef struct Ligacoesida
{
	char* nome;
	float custo;
	float distancia;
}*LigacoesidaPTR;

typedef struct Ligacoesvinda
{
	char* nome;
}*LigacoesvindaPTR;


typedef struct Localidade
{
	char* nome;
	MainListPTR ligacoesida;
	MainListPTR ligacoesvinda;
}*LocalidadePTR;



int inserelocalidade (TabelaHashPTR table, char *nome);
int comparalocalidades (void *a, void *b);
void hashprint (TabelaHashPTR table);
int removerlocalidade (TabelaHashPTR table, char *nome);
int inserirligacao(TabelaHashPTR table, char *nomeorigem, char *nomedestino, float custo, float distancia);


#endif /* LOCALIDADES_H_INCLUDED */