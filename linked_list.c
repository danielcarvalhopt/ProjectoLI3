#include <stdlib.h>
#include <stdio.h>
#include "linked_list.h"

MainListPTR crialistaligada(MainListPTR lista) {
    MainListPTR novo;

    if((novo= (MainListPTR) malloc(sizeof (struct MainList)))==NULL) return NULL;
    novo=lista;
    novo->elems = NULL;
    novo->nelems = 0;

    return novo;
}

 MainListPTR inserelistahead(MainListPTR lista, void *externdata) {
    LinkedListPTR novo;

    if ((novo =(LinkedListPTR) malloc(sizeof(struct linkedList)))==NULL) return NULL;

    novo->extdata = externdata;
    novo->prox = lista->elems;
    lista->elems = novo;
    lista->nelems++;
    return lista;
}


int main()
{
    char *nome="Daniel", *nome2="Carvalho", *nome3="Doomz";
    LinkedListPTR elemento;
    MainListPTR raiz;
    raiz = (MainListPTR) malloc (sizeof(struct MainList));
    crialistaligada(raiz);


    inserelistahead(raiz,nome);
    inserelistahead(raiz,nome2);
    inserelistahead(raiz,nome3);
    while (raiz->elems)
    {
        printf ("%s \n", (char*)raiz->elems->extdata);
        raiz->elems=raiz->elems->prox;
    }
    printf("%d\n",raiz->nelems);
    return 0;




}