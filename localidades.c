#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "localidades.h"




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



/*--------------------------------------------------------------------*/
/* Módulo de Tabela de Hash -> Funções de tabela de hash com chaining */
/*--------------------------------------------------------------------*/

char* allocStr(char *dest, char *src){
	if( (dest = malloc(strlen(src) + 1)) == NULL ){
		printf("Out of memory\n");
		return NULL;
	}
	strcpy(dest, src);
	return dest;
}


TabelaHashPTR hashtablecreator (int(*hash_function)(void*,int), int startcells, int (*func_compare)(void*,void*))
{
	TabelaHashPTR table; int i;

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




int hashtableinsertion (TabelaHashPTR table, void *externdata);
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

            if ((hashtableinsertion (table, aux->extdata))==0) return 0;
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



int hash_function(void*a,int b)
{
	//LocalidadePTR localA = (LocalidadePTR)a;
	//char *nomeA;
    //nomeA=(char*)localA->nome;
    return 0;
}

// ------------------------------------------------------------------
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ------------------------------------------------------------------


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
	if (hashtablesearch(table, localidade)!=NULL) return 0;

	return hashtableinsertion (table, localidade);

}


int removerlocalidade (TabelaHashPTR table, char *nome)
{
	LocalidadePTR aux;
	if ((aux = crialocalidade(nome))==NULL) return 0;

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
    
    if ((hashtablesearch(table, localidadeida)==NULL) || (hashtablesearch(table, localidadevinda)==NULL)) return 0;
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
        printf("%s\n",(char*)local->nome);
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




/*







	printf("Antes\n");
	hashprint(table);

	printf("Medio\n");
	inserelocalidade(table, localidadeE);
	hashprint(table);
	printf("Depois\n");


	removerlocalidade(table,localidadeC);
	inserirligacao(table, localidadeE, localidadeA, 10, 52);	
	inserirligacao(table, localidadeE, localidadeB, 100, 520);
	inserirligacao(table, localidadeE, localidadeA, 1000, 5200);
	inserirligacao(table, localidadeE, localidadeD, 10000, 52000);

	removerligacao(table,localidadeE, localidadeD);

	LinkedListPTR aux = hashtablesearch(table, crialocalidade(localidadeE));
	LocalidadePTR aux2= aux->extdata;
	LinkedListPTR aux3 = aux2->ligacoesida->elems;

	printf("%d\n",aux2->ligacoesida->nelems );
	imprimelistaligacoes(aux3);	



*/




	return 0;
}