#include <stdlib.h>
#include "mod_lista_ligada.h"
#include <string.h>
#include <stdio.h>
/*--------------------------------------------------------*/
/* Módulo de Lista Ligada -> Funções sobre Listas Ligadas */
/*--------------------------------------------------------*/




MainListPTR criaListaLigada(int(*func_compare)(void*,void*)) 
{
    MainListPTR novo;

    if((novo= (MainListPTR) malloc(sizeof (struct MainList)))==NULL) return NULL;

    novo->elems = NULL;
    novo->nelems = 0;
    novo->func_compare=func_compare;

    return novo;
}



 int insereListaInicio(MainListPTR lista, void *externdata) 
 {
    LinkedListPTR novo;

    if ((novo =(LinkedListPTR) malloc(sizeof(struct linkedList)))==NULL) return 0;

    novo->extdata = externdata;
    novo->prox = lista->elems;
    lista->elems = novo;
    lista->nelems++;
    return 1;
}

int insereListaOrdenado (MainListPTR lista, void *externdata)
{
    MainListPTR aux = lista;
    LinkedListPTR novo, anterior = NULL, actual = aux->elems;

    if((novo =(LinkedListPTR) malloc(sizeof(struct linkedList)))==NULL) return 0;
    novo->extdata = externdata;
    novo->prox = NULL;
    while ((actual!=NULL) && ((aux->func_compare(novo->extdata,actual->extdata))!=-1))
    {
        anterior = actual;
        actual = actual->prox;
    }
    if (anterior==NULL)
    {
        novo->prox = aux->elems;
        aux->elems=novo;
        aux->nelems++;
    }
    else
    {
        novo->prox=actual;
        anterior->prox = novo;
        aux->nelems++;
    }
    return 1;
}


void apagaElemento (LinkedListPTR *elem)
{
    free (*elem);
    *elem=NULL;
}




int apagaElementoLista (MainListPTR lista, void* externdata)
{
    LinkedListPTR ant = NULL, actelem= lista->elems;
    int apagado=0;

    if (actelem==NULL) return 0;
    
    if (lista->func_compare(actelem->extdata, externdata)==0)
    {
        lista->elems=lista->elems->prox;
        apagaElemento(&actelem);
        lista->nelems--;
        apagado=1;
    }

    else
    {
        while (actelem!=NULL && (lista->func_compare(actelem->extdata, externdata)!=0))
        {
            ant=actelem;
            actelem=actelem->prox;
        }
    
        if (actelem!=NULL)
        {
            ant->prox=actelem->prox;
            apagaElemento(&actelem);
            lista->nelems--;
            apagado=1;
        }
    }
    return apagado;
}



LinkedListPTR procuraElementoLista (MainListPTR lista, void *externdata)
{
    LinkedListPTR aux= lista->elems;
    
    while(aux!=NULL)
    {
        if (lista->func_compare(aux->extdata,externdata)==0)
            return aux;
        aux=aux->prox;
    }

    return NULL;
}



void aplicaFuncLista(MainListPTR lista, void (*applyFunction)(void *, void *), void *parametros) 
{
    LinkedListPTR aux = lista->elems;

    while (aux != NULL) {
        applyFunction(aux->extdata, parametros);
        aux = aux->prox;
    }
}


void apagaListaAux(LinkedListPTR *lista)
{
    LinkedListPTR aux;

    while (*lista!=NULL)
    {
        aux=*lista;
        *lista=(*lista)->prox;
        apagaElemento(&aux);
    }

}



void apagaLista(MainListPTR lista)
{
    apagaListaAux(&(lista->elems));
    lista->nelems=0;
}

