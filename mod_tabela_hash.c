



/*--------------------------------------------------------------------*/
/* Módulo de Tabela de Hash -> Funções de tabela de hash com chaining */
/*--------------------------------------------------------------------*/



TabelaHashPTR hashtablecreator (int(*hash_function)(void*,int), int startcells)
{
	TabelaHashPTR table; void *datacells; int i;

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

    return 1;
}



LinkedListPTR hashtablesearch (TabelaHashPTR table, void *externdata)
{
    int hashkey=table->hash_function(externdata,table->totalcells);
    LinkedListPTR aux;
    aux=(procuraelemlista(table->arraycell[hashkey], externdata));
    if (aux!=NULL) return aux;  
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
    int v = *(char*)a;
    return (v%b);
}


/***********   ZONA DE TESTES **************/
/***********   ZONA DE TESTES **************/
/***********   ZONA DE TESTES **************/
/***********   ZONA DE TESTES **************/
/***********   ZONA DE TESTES **************/
/***********   ZONA DE TESTES **************/
/***********   ZONA DE TESTES **************/
/********************************************

/*
void hashprint(TabelaHashPTR table)
{
    MainListPTR *aux=table->arraycell;int i;
    for(i=0;i<table->totalcells;i++)
    {
        while(aux[i]->elems!=NULL){
            printf("%s\n",(char*)aux[i]->elems->extdata);
            aux[i]->elems=aux[i]->elems->prox;
            }
    }
}




int main()
{


int i;
    char *string;
    string=malloc(sizeof(10));
    strcpy(string,"1");
    char *string2;
    string2=malloc(sizeof(10));
    strcpy(string2,"2");
    char *string3;
    string3=malloc(sizeof(10));
    strcpy(string3,"3");
    char *string4;
    string4=malloc(sizeof(10));
    strcpy(string4,"4");
    char *string5;
    string5=malloc(sizeof(10));
    strcpy(string5,"5");
    char *string6;
    string6=malloc(sizeof(10));
    strcpy(string6,"6");
    char *string7;
    string7=malloc(sizeof(10));
    strcpy(string7,"LOL");
    char *string8;
    string8=malloc(sizeof(10));
    strcpy(string8,"8");
    TabelaHashPTR table;
    table = hashtablecreator (hash_function,1);
hashtableinsertion(table, "TROLOL");
for (i=0; i<3;i++){
    hashtableinsertion(table,string);
    hashtableinsertion(table,string2);
        hashtableinsertion(table,string3);
            hashtableinsertion(table,string4);
                hashtableinsertion(table,string5);
                    hashtableinsertion(table,string6);
                        hashtableinsertion(table,string7);
                            hashtableinsertion(table,string8);}

                                
    printf("%d %d %d\n", table->totalcells, hashtablecelluse(table), table->nelems );
    printf("%d\n", table->totalcells);
    printf("Search:%s\n",(char*)((hashtablesearch(table, "TROLOL"))->extdata));
    printf("%d\n",hashtableelemdeletion(table, "TROLOL"));
    hashtabledestroy(table);
        printf("%d %d %d\n", table->totalcells, hashtablecelluse(table), table->nelems );
    printf("%d\n", table->totalcells);
    if((((hashtablesearch(table, string7)))!=NULL))
    printf("Search:%s\n",(char*)((hashtablesearch(table, string7))->extdata));
    else printf("LOL\n");
    if((((hashtablesearch(table, "TROLOL")))!=NULL))
    printf("Search:%s\n",(char*)((hashtablesearch(table, "TROLOL"))->extdata));
    else printf("LOL TROLOL\n");




    return 0;
}*/


    