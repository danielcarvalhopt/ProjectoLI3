#include <stdlib.h>
#include "mod_lista_ligada.h"
/*--------------------------------------------------------*/
/* Módulo de Lista Ligada -> Funções sobre Listas Ligadas */
/*--------------------------------------------------------*/




MainListPTR crialistaligada(int(*func_compare)(void*,void*)) {
    MainListPTR novo;

    if((novo= (MainListPTR) malloc(sizeof (struct MainList)))==NULL) return NULL;

    novo->elems = NULL;
    novo->nelems = 0;
    novo->func_compare=func_compare;

    return novo;
}



 int inserelistahead(MainListPTR lista, void *externdata) {
    LinkedListPTR novo;

    if ((novo =(LinkedListPTR) malloc(sizeof(struct linkedList)))==NULL) return 0;

    novo->extdata = externdata;
    novo->prox = lista->elems;
    lista->elems = novo;
    lista->nelems++;
    return 1;
}



void apagaelem (LinkedListPTR *elem)
{
    
    //free((*elem)->extdata);
    free (*elem);
    *elem=NULL;
}




int apagaelemlista (MainListPTR lista, void* externdata)
{
    LinkedListPTR ant = NULL, actelem= lista->elems;
    int apagado=0;

    if (actelem==NULL) return 1;
    
    if (lista->func_compare(actelem->extdata, externdata)==0)
    {
        lista->elems=lista->elems->prox;
        apagaelem(&actelem);
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
            apagaelem(&actelem);
            lista->nelems--;
            apagado=1;
        }
    }
    return apagado;
}



LinkedListPTR procuraelemlista (MainListPTR lista, void *externdata)
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



void apagalistaaux(LinkedListPTR *lista)
{
    LinkedListPTR aux;

    while (*lista!=NULL)
    {
        aux=*lista;
        *lista=(*lista)->prox;
        apagaelem(&aux);
    }

}



void apagalista(MainListPTR lista)
{
    apagalistaaux(&(lista->elems));
    lista->nelems=0;
}




/********************************************


int func_compareaux(void* a, void *b)
{
    char *aa, *bb;
    aa = (char*)a;
    bb=(char*)b;
    if(strcmp(aa,bb)==0) return 0;
    if(strcmp(aa,bb)==-1) return -1; 
    else return 1;
}

void imprimelista(LinkedListPTR lista)
{
    LinkedListPTR aux=lista;
    while (aux)
    {
        printf("%s\n",(char*)aux->extdata );
        aux=aux->prox;
    }
}

int main()
{

    char *a,*b,*c,*d,*e;
    a=(char*)malloc(sizeof(strlen("D1")+1));
    strcpy(a,"D1");
    b=(char*)malloc(sizeof(strlen("D1")+1));
    strcpy(b,"D2");    
    c=(char*)malloc(sizeof(strlen("D1")+1));
    strcpy(c,"D3");
    d=(char*)malloc(sizeof(strlen("D1")+1));
    strcpy(d,"D4");
    e=(char*)malloc(sizeof(strlen("D1")+1));
    strcpy(e,"D5");

    LinkedListPTR elemento;
    MainListPTR raiz;
    raiz = (MainListPTR) malloc (sizeof(struct MainList));
    crialistaligada(raiz,func_compareaux);

    inserelistahead(raiz,a);
    inserelistahead(raiz,b);
    inserelistahead(raiz,c);
    apagaelemlista(raiz,c);
    imprimelista(raiz->elems);
    printf("Elem: %s\n",(char*)procuraelemlista(raiz,a)->extdata);

    apagalista(raiz);
        printf("Elem: %s\n",(char*)(procuraelemlista(raiz,a)));
        printf("%d\n",raiz->nelems );
        imprimelista(raiz->elems);
    return 0;

}
************************************/
