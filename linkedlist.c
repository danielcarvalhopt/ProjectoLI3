#include <stdlib.h>
#include <stdio.h>




/* Lista ligada */
typedef struct sListaLigada{
	void *extdata;
	struct sListaLigada *prox;
} ListaLigada, *ListaLigadaPTR;


ListaLigadaPTR crialistaligada(ListaLigadaPTR raiz){    
    ListaLigadaPTR novo,aux;
 
    novo = (ListaLigadaPTR) malloc( sizeof( ListaLigada ));   
 
    if(novo == NULL) exit(0);   
 
    aux = raiz;               
    aux->prox = novo;
    novo->prox = NULL;        
 
    return (aux);
}


void inserirfimlistaligada(struct ListaLigada **raiz, void *extdataptr){
    ListaLigada *novo;
    novo = (ListaLigada *) malloc(sizeof(ListaLigada));
    if(novo == NULL) exit(0);
    novo->extdata = extdataptr;
    novo->prox = NULL;
 
    if(*raiz == NULL){
        *raiz = novo;
    }else{
        ListaLigada *aux;
        aux = *raiz;
        while(aux->prox != NULL){
            aux = aux->prox;
        }
        aux->prox = novo;
    }
}






int main()
{
    ListaLigadaPTR raiz;
    raiz = (ListaLigadaPTR) malloc( sizeof(ListaLigada) ); 
    raiz = crialistaligada( raiz );
	return 0;
}