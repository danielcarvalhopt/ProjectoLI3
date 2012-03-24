#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "utils.h"
#include "localidades.h"
#include "mod_tabela_hash.h"
#include "mod_lista_ligada.h"



int comparalocalidades (void *a, void *b)
{
	LocalidadePTR localA = (LocalidadePTR)a;
	LocalidadePTR localB = (LocalidadePTR)b;
	char *nomeA, *nomeB;
    nomeA=(char*)localA->nome;
    nomeB=(char*)localB->nome;
	
	return (strcmp(nomeA,nomeB));
}


int compareligacoesida (void *a, void *b)
{
	LigacoesidaPTR localA = (LigacoesidaPTR)a;
	LigacoesidaPTR localB = (LigacoesidaPTR)b;
	char *nomeA, *nomeB;
    nomeA=(char*)localA->nome;
    nomeB=(char*)localB->nome;
	
	return (strcmp(nomeA,nomeB));
}

int compareligacoesvinda (void *a, void *b)
{
	LigacoesvindaPTR localA = (LigacoesvindaPTR)a;
	LigacoesvindaPTR localB = (LigacoesvindaPTR)b;

	char *nomeA, *nomeB;
    nomeA=(char*)localA->nome;
    nomeB=(char*)localB->nome;
	
	return (strcmp(nomeA,nomeB));
}


LocalidadePTR crialocalidade (char* nome)
{
	LocalidadePTR localidade; char* nomelocalidade=NULL;

	localidade = (LocalidadePTR)malloc(sizeof(struct Localidade));
	localidade->nome=allocStr(nomelocalidade,nome);
	localidade->ligacoesida=crialistaligada(compareligacoesida);
	localidade->ligacoesvinda=crialistaligada(compareligacoesvinda);

	return localidade;
}


int inserelocalidade (TabelaHashPTR table, char *nome)
{
	LocalidadePTR localidade = crialocalidade(nome);
	if (hashtablesearch(table, localidade)!=NULL) return -1;

	return hashtableinsertion (table, localidade);

}


int removerlocalidade (TabelaHashPTR table, char *nome)
{
	LocalidadePTR aux;
	if ((aux = crialocalidade(nome))==NULL) return -1;

	if (hashtablesearch(table, aux)==NULL) return 0;

	return (hashtableelemdeletion(table, aux)); 
}


LigacoesidaPTR crialigacaoida (char* nome, float custo, float distancia)
{
	LigacoesidaPTR ligacao; char *nomelocalidade=NULL;

	ligacao = malloc (sizeof(struct Ligacoesida));
	ligacao->nome = allocStr(nomelocalidade,nome);
	ligacao->custo=custo;
	ligacao->distancia=distancia;

	return ligacao;
}

LigacoesvindaPTR crialigacaovinda (char* nome)
{
	LigacoesvindaPTR ligacao; char *nomelocalidade=NULL;

	ligacao = (LigacoesvindaPTR)malloc(sizeof(struct Ligacoesvinda));
	ligacao->nome=allocStr(nomelocalidade,nome);

	return ligacao;
}


int inserirligacao(TabelaHashPTR table, char *nomeorigem, char *nomedestino, float custo, float distancia)
{
	LocalidadePTR localidadeida = crialocalidade(nomeorigem);
	LocalidadePTR localidadevinda = crialocalidade(nomedestino);
	LigacoesidaPTR localidadedestino = crialigacaoida(nomedestino, custo,distancia);
	LigacoesvindaPTR localidadeorigem = crialigacaovinda(nomeorigem);

	LocalidadePTR aux, aux2;
    
    if ((hashtablesearch(table, localidadeida)==NULL) || (hashtablesearch(table, localidadevinda)==NULL)) return -1;
    else
    {
        aux = (((LinkedListPTR)hashtablesearch(table, localidadeida))->extdata);
        aux2 = (((LinkedListPTR)hashtablesearch(table, localidadevinda))->extdata);
        if ((procuraelemlista(aux->ligacoesida,localidadedestino)!=NULL) || (procuraelemlista(aux2->ligacoesvinda, localidadeorigem)!=NULL))
            return 0;
        else
        {
           inserelistahead(aux->ligacoesida,localidadedestino);
           inserelistahead(aux2->ligacoesvinda, localidadeorigem);
        }


    }
	return 1;
}


int removerligacao (TabelaHashPTR table, char *nomeorigem, char *nomedestino)
{

	LocalidadePTR localidadeida = crialocalidade(nomeorigem);
	LocalidadePTR localidadevinda = crialocalidade(nomedestino);
	LigacoesidaPTR localidadedestino = crialigacaoida(nomedestino, 0,0);
	LigacoesvindaPTR localidadeorigem = crialigacaovinda(nomeorigem);

	LocalidadePTR aux, aux2;

    if ((hashtablesearch(table, localidadeida)!=NULL) || (hashtablesearch(table, localidadevinda)!=NULL)) return 0;
    else
    {
        aux = (((LinkedListPTR)hashtablesearch(table, localidadeida))->extdata);
        aux2 = (((LinkedListPTR)hashtablesearch(table, localidadevinda))->extdata);
        if ((procuraelemlista(aux->ligacoesida,localidadedestino)==NULL) || (procuraelemlista(aux2->ligacoesvinda, localidadeorigem)==NULL))
            return 0;
        else
        {
            apagaelemlista(aux->ligacoesida,localidadedestino);
            apagaelemlista(aux2->ligacoesvinda, localidadeorigem);
        }


    }
	return 1;
}





void imprimelista(LinkedListPTR lista)
{
    LinkedListPTR aux=lista;
    LocalidadePTR local;
    while (aux)
    {
    	local = aux->extdata;
        printf("%s",(char*)local->nome);
        aux=aux->prox;
    }
}

void hashprint (TabelaHashPTR table)
{
	int n= table->totalcells;
	MainListPTR *aux = table->arraycell;
	int i;
	for (i=0; i<n; i++)
	{
		imprimelista(aux[i]->elems);
	}

}

void imprimelistaligacoes(LinkedListPTR lista)
{
    LinkedListPTR aux=lista;
    LigacoesidaPTR local;
    while (aux!=NULL)
    {
    	local = aux->extdata;
        printf("%s %f %f\n",(char*)local->nome, (float)local->custo, (float)local->distancia);
        aux=aux->prox;
    }
}


/*

int main()
{
	char *localidadeA, *localidadeB,*localidadeC,*localidadeD,*localidadeE,*localidadeF,*localidadeG;
	localidadeA=(char*)malloc(10); strcpy(localidadeA, "LocalA");
	localidadeB=(char*)malloc(10); strcpy(localidadeB, "LocalB");
	localidadeC=(char*)malloc(10); strcpy(localidadeC, "LocalC");
	localidadeD=(char*)malloc(10); strcpy(localidadeD, "LocalD");
	localidadeE=(char*)malloc(10); strcpy(localidadeE, "LocalE");
    localidadeF=(char*)malloc(10); strcpy(localidadeD, "LocalF");
    localidadeG=(char*)malloc(10); strcpy(localidadeE, "LocalG");

	TabelaHashPTR table = hashtablecreator(hash_function, 1, comparalocalidades);
	

    inserelocalidade(table, localidadeA);
	inserelocalidade(table, localidadeB);
	inserelocalidade(table, localidadeC);
	inserelocalidade(table, localidadeD);
	inserelocalidade(table, localidadeE);


    inserelocalidade(table, localidadeF);
    inserelocalidade(table, localidadeG);
    inserelocalidade(table, localidadeF);
	removerlocalidade(table,localidadeE);
    removerlocalidade(table,localidadeG);


    inserirligacao(table, localidadeA, localidadeB, 1, 1);
    inserirligacao(table, localidadeA, localidadeB, 1, 1);
    inserirligacao(table, localidadeA, localidadeE, 1, 1);
    inserirligacao(table, localidadeA, localidadeG, 2, 2);
    inserirligacao(table, localidadeE, localidadeA, 1, 1);
    inserirligacao(table, localidadeG, localidadeE, 1, 1);
    inserelocalidade(table, localidadeE);


    LinkedListPTR aux = hashtablesearch(table, crialocalidade(localidadeA));
    LocalidadePTR aux2= aux->extdata;
    LinkedListPTR aux3 = aux2->ligacoesida->elems;

    LinkedListPTR aux4 = hashtablesearch(table, crialocalidade(localidadeB));
    LocalidadePTR aux5= aux4->extdata;
    LinkedListPTR aux6 = aux5->ligacoesida->elems;

    printf("%d\n",aux2->ligacoesida->nelems );
    imprimelistaligacoes(aux3); 
    printf("%d\n",aux5->ligacoesida->nelems );
    imprimelistaligacoes(aux6);

    hashprint(table);
    printf("Teste\n");
    removerlocalidade(table, localidadeA);
    hashprint(table);

	return 0;
}*/