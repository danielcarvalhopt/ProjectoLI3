#include <stdlib.h>

#include "dados.h"
#include "mod_tabela_hash.h"
#include "utils.h"
/*--------------------------------------------------------------------*/
/* Módulo de Tabela de Hash -> Funções de tabela de hash com chaining */
/*--------------------------------------------------------------------*/

TabelaHashPTR hashtablecreator (int(*hash_function)(void*,int), int startcells, int (*func_compare)(void*,void*))
{
    TabelaHashPTR table;
    int i;

    table = (TabelaHashPTR)malloc(sizeof(struct TabelaHash));


    table->hash_function = hash_function;
    table->nelems=0;
    table->totalcells=startcells;
    table->arraycell = (MainListPTR*)malloc(sizeof(MainListPTR) * startcells);

    for(i=0;i<startcells;i++)
    {
        table->arraycell[i]=(crialistaligada(func_compare));
    }

    return table;
}



int hashtablecelluse (TabelaHashPTR table)
{
    return ( 0.5 < ( (float)table->nelems / (float)table->totalcells) );
} 



int hashtablerealloc (TabelaHashPTR table)
{
    int acttotalcells = table->totalcells;
    int realloccells = acttotalcells*2; int i;
    void *func_compare=(table->arraycell[0]->func_compare);

    MainListPTR *dados=table->arraycell;
    LinkedListPTR aux, auxfree;

    table->arraycell=(void*)malloc(sizeof(void*)*(realloccells));
    table->totalcells=realloccells;
    table->nelems=0;

    for (i=0; i < realloccells; i++)
    {        
        table->arraycell[i]=(crialistaligada(func_compare));        
    }

    for (i=0; i < acttotalcells; i++)
    {
        
        aux=dados[i]->elems;
        while(aux!=NULL)
        {
            hashtableinsertion (table, aux->extdata);
            auxfree=aux;
            aux=aux->prox;
            free(auxfree);
        }
    }
    table->totalcells=realloccells;
    free(aux);
    free(dados);

    return 1;
}



int hashtableinsertion (TabelaHashPTR table, void *externdata)
{
    void *func_compare=table->arraycell[0]->func_compare;

    if(hashtablecelluse(table)==1){
        hashtablerealloc(table);
    }
    int hashkey=table->hash_function(externdata,table->totalcells);
    if (table->arraycell[hashkey]==NULL)
    {
        table->arraycell[hashkey]=(crialistaligada(func_compare));
    }
    int success = inserelistahead(table->arraycell[hashkey], externdata);
    if (success==1){
        table->nelems++;
    }
    else return 0;

    return 1;
}



LinkedListPTR hashtablesearch (TabelaHashPTR table, void *externdata)
{
    int hashkey=(int)(table->hash_function(externdata,table->totalcells));
    LinkedListPTR aux;
    if ((aux=(procuraelemlista(table->arraycell[hashkey], externdata)))!=NULL) return aux;  
    else return NULL;
}



int hashtableelemdeletion (TabelaHashPTR table, void* externdata)
{
    int apagado=0;
    int hashkey=table->hash_function(externdata,table->totalcells);
    if(apagaelemlista(table->arraycell[hashkey],externdata)==1)
    {
        apagado=1; 
        table->nelems--;
    }
    return apagado;
}



void hashtabledestroy(TabelaHashPTR table)
{
    MainListPTR *aux=table->arraycell; int i;

    for(i=0;i<(table->totalcells);i++)
    {
        apagalista(aux[i]);
    }
}


/*
int hash_function(void*a,int b){
    LocalidadePTR localA = (LocalidadePTR)a;
    char *nomeA;
    nomeA=(char*)localA->nome;
    return 0;
}*/

