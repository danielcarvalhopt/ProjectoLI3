#include <stdlib.h>

#include "dados.h"
#include "mod_tabela_hash.h"
#include "utils.h"


TabelaHashPTR criaTabelaHash (int(*hash_function)(void*,int), int startcells, int (*func_compare)(void*,void*))
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
        table->arraycell[i]=(criaListaLigada(func_compare));
    }

    return table;
}



int ocupacaoTabelaHash (TabelaHashPTR table)
{
    float res = (float)table->nelems / (float)table->totalcells;
    if (res > 0.5) return 1;
    if (res < 0.225) return -1;
    return 0;

} 



int aumentaTabelaHash (TabelaHashPTR table)
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
        table->arraycell[i]=(criaListaLigada(func_compare));        
    }

    for (i=0; i < acttotalcells; i++)
    {
        
        aux=dados[i]->elems;
        while(aux!=NULL)
        {
            insereElementoTabelaHash(table, aux->extdata);
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



int diminuiTabelaHash (TabelaHashPTR table)
{
    int acttotalcells = table->totalcells;
    int realloccells = acttotalcells/2; int i;
    void *func_compare=(table->arraycell[0]->func_compare);
    MainListPTR *dados=table->arraycell;
    LinkedListPTR aux, auxfree;

    table->arraycell=(void*)malloc(sizeof(void*)*(realloccells));
    table->totalcells=realloccells;
    table->nelems=0;

    for (i=0; i < realloccells; i++)
    {        
        table->arraycell[i]=(criaListaLigada(func_compare));        
    }

    for (i=0; i < acttotalcells; i++)
    {
        
        aux=dados[i]->elems;
        while(aux!=NULL)
        {
            insereElementoTabelaHash(table, aux->extdata);
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


int insereElementoTabelaHash (TabelaHashPTR table, void *externdata)
{
    void *func_compare=table->arraycell[0]->func_compare;

    if(ocupacaoTabelaHash(table)==1){
        aumentaTabelaHash(table);
    }
    int hashkey=table->hash_function(externdata,table->totalcells);
    if (table->arraycell[hashkey]==NULL)
    {
        table->arraycell[hashkey]=(criaListaLigada(func_compare));
    }
    int success = insereListaOrdenado(table->arraycell[hashkey], externdata);
    if (success==1){
        table->nelems++;
    }
    else return 0;

    return 1;
}



LinkedListPTR procuraTabelaHash (TabelaHashPTR table, void *externdata){
    int hashkey;
    if( externdata==NULL ) return NULL;
    hashkey=(int)(table->hash_function(externdata,table->totalcells));
    return procuraElementoLista(table->arraycell[hashkey], externdata);  
}



int apagaElementoTabelaHash (TabelaHashPTR table, void* externdata)
{
    int apagado=0;
    int hashkey=table->hash_function(externdata,table->totalcells);

    if(apagaElementoLista(table->arraycell[hashkey],externdata)==1)
    {
        apagado=1; 
        table->nelems--;
    }
    if((ocupacaoTabelaHash(table)==-1) && ((table->totalcells)>10000)){
        diminuiTabelaHash(table);
    }
    return apagado;
}



void apagaTabelaHash(TabelaHashPTR table)
{
    MainListPTR *aux=table->arraycell; int i;

    for(i=0;i<(table->totalcells);i++)
    {
        apagaLista(aux[i]);
    }
    table->nelems=0;

    while((ocupacaoTabelaHash(table)==-1) && ((table->totalcells)>10000)){
        diminuiTabelaHash(table);
    }
}

/*
void imprimeHash(TabelaHashPTR table)
{
    MainListPTR *aux=table->arraycell; int i;

    for(i=0;i<(table->totalcells);i++)
    {
        imprimelista(aux[i]->elems);
    }
}


int hash_function (void *externdata, int b)
{
    char *a=externdata; double res=0; int i=0;
    while (i < strlen(a))
    {
        res+=a[i];
        i++;
    }
    return (int)res%(b-1);
}
*/
