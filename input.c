/**
 * @file input.c
 * @brief Módulo de input (código)
 * */
#include <stdio.h>
#include <math.h>
#include <limits.h>
#include "utils.h"
#include "dados.h"
#include "input.h"
#include <stdlib.h>
#include <string.h>
#include "mod_error.h"

int lerStr(char **ptr){
    char strBuffer[1024];
    int i=0, excedeu=1;
    
    do{
        strBuffer[i] = getchar();
        i++;
    }while( strBuffer[i-1] != '\0' && strBuffer[i-1] != '\n' && i < 1023 );
    strBuffer[i-1] = '\0';
    if( i == 1023 ){
        clearInputBuffer();
        excedeu=-1;
    }
    
    if( (*ptr = allocStr(strBuffer)) == NULL )
        return 0;
    else
        return excedeu;
}


int readInt(){
    char c;
    int sinal=1, res=0;
    c=getchar();
    switch(c){
        case '-': sinal = -1;
        case '+': c=getchar();
                  break;
    }
    while( c != '\n' && res != INT_MAX){
        if( c >= '0' && c <= '9' ){
            res = res*10 + c - '0';
            c = getchar();
        }else{
            res = INT_MAX;
            clearInputBuffer();
        }
    }
    if( res != INT_MAX )
        res *= sinal;
    return res;
}

unsigned int readUInt(){
    char c;
    unsigned int res=0;
    c=getchar();
    switch(c){
        case '+': c=getchar();
                  break;
    }
    while( c != '\n' && res != INT_MAX){
        if( c >= '0' && c <= '9' ){
            res = res*10 + c - '0';
            c = getchar();
        }else{
            res = INT_MAX;
            clearInputBuffer();
        }
    }
    return res;
}

double readDouble(){
    double res;
    char strBuffer[128];
    char strDouble[128];
    char *ps = &strBuffer[0];
    char *pd = &strDouble[0];
    char ponto = 0;


    fgets(strBuffer, 127, stdin);

    if( *ps == '+' || *ps == '-' ){
        *pd = *ps;
        ps++;pd++;
    }

    while( *ps != '\n' && *ps != '\0' && ponto != 2){
        if( *ps >= '0' && *ps <= '9' ){
            *pd = *ps;
            pd++;ps++;
        }else if( *ps == '.' && ponto == 0 ){
            ponto = 1;
            *pd = '.';
            ps++;pd++;
        }else{
            ponto = 2;
        }
    }

    *pd = '\0'; //terminar a string do double

    if( ponto == 2 ) return NAN; //se o que foi lido nao for um numero, faz return NAN.

    sscanf(strDouble, "%lf", &res);
    return res;
}

//
//
// FUNÇÕES PARA LER OS DADOS DE TESTE
//
//


int reSampleLocalidades(int flag){
    //id_local:Nome:lista de ligacoes a partir de id_local (9 ligacoes)
    FILE *f = fopen("localidades.txt", "r");
    struct sSampleLocalidades d[18515];

    //id_origem:id_destino:KM:custo
    FILE *l = fopen("custosligacao.txt", "r");
    int lig[166626][4];

    //misc.
    int i;
    
    // necessário para os 2
    for( i=1; i<18515; i++ )
        fscanf(f, "%*d:%[^:]:%d:%d:%d:%d:%d:%d:%d:%d:%d", d[i].nome,
                &d[i].lig[0], &d[i].lig[1], &d[i].lig[2], &d[i].lig[3], &d[i].lig[4], &d[i].lig[5], &d[i].lig[6], &d[i].lig[7], &d[i].lig[8] );

    // output localidades
    // nome:adj[0]:...:adj[9]
    if( flag==0 ){
        for( i=1; i<18515; i++ )
            printf( "%s:%s:%s:%s:%s:%s:%s:%s:%s:%s\n", d[i].nome, d[d[i].lig[0]].nome, d[d[i].lig[1]].nome, d[d[i].lig[2]].nome, d[d[i].lig[3]].nome,
                    d[d[i].lig[4]].nome, d[d[i].lig[5]].nome, d[d[i].lig[6]].nome, d[d[i].lig[7]].nome, d[d[i].lig[8]].nome);
    }

    // output ligacoes
    // origem:destino:km:custo
    if( flag==1 ){
        for( i=0; i<166626; i++ )
            fscanf(l, "%d:%d:%d:%d", &lig[i][0], &lig[i][1], &lig[i][2], &lig[i][3]); 
        
        for( i=0; i<166626; i++ )
            printf( "%s:%s:%d:%d\n", d[lig[i][0]].nome, d[lig[i][1]].nome, lig[i][2], lig[i][3] ); 
    }

    fclose(f);
    fclose(l);

    return 0;    
}

int reSampleUser(){
    FILE *f = fopen("utilizadores.txt","r");
    unsigned int nif[18484];
    int i;
    char nome[18484][100];
    char email[50];
    char morada[18484][100];
    
    for( i=0; i<18484; i++ )
        fscanf(f,"%d\t%[^\t]\t%[^\t]\t%[^\t]", &nif[i], nome[i], email, morada[i]);
    for( i=0; i<18484; i++ )
        printf("%d:%s:%s", nif[i], nome[i], morada[i]);

    return 1;
}

int readSampleLocalidades(TabelaHashPTR *table, int (*comparaLocalidades)(void*,void*), int(*hash_function)(void*,int)){
    FILE *local = fopen("local.txt", "r");
    FILE *liga = fopen("ligacoes.txt", "r");
    char *str[2];
    char fstr[2][106];
    double custo, km;
    
    *table = criaTabelaHash(hash_function, 10000, comparaLocalidades);

    while( fscanf(local,"%[^\n]\n", fstr[0] ) > 0){
        str[0] = allocStr(fstr[0]);
        inserelocalidade( *table, str[0] );
    }
    
    while( fscanf(liga, "%[^:]:%[^:]:%lg:%lg\n", fstr[0], fstr[1], &km, &custo) > 0 ){
        str[0] = allocStr(fstr[0]);
        str[1] = allocStr(fstr[1]);
        inserirligacao(*table, str[0], str[1], custo, km);
    }

    return 1;
}

int readSampleClientes(MainTreePt *clientes, int (*comparaClientes[DIM])(void*,void*)){
    FILE *cfile = fopen("utilizadores.txt", "r");
    char fstr[2][63];
    unsigned int nif;
    char *str[2];

    *clientes = tree_new( comparaClientes );

    while( fscanf(cfile, "%u:%[^:]:%[^\n]\n", &nif, fstr[0], fstr[1]) > 0){
        str[0] = allocStr(fstr[0]);
        str[1] = allocStr(fstr[1]);
        tree_insert( *clientes, cliente_novo( nif, str[0], str[1], criaListaLigada( cliente_comparaServico ) ));
    }

    return 1;
}

int readSampleCamioes(MainTreePt *camioes, int (*comparaCamioes[DIM])(void*,void*)){
    int i=0;
    
    char matricula[10][20] = {
        "00-00-00",
        "AA-01-01",
        "BB-02-02",
        "CC-03-03",
        "DD-04-04",
        "EE-05-05",
        "FF-06-06",
        "GG-07-07",
        "HH-08-08",
        "II-09-09"
    };

    char local[10][50] = {
        "Taipa",
        "Praia de Porto Chão",
        "Ponta do Fogo",
        "Póvoa da Pégada",
        "Alto do Vale de Sardão",
        "Vale de Mouros",
        "Sabacheira",
        "Costa do Valado",
        "Estreito",
        "Benavila"
    };
    
    *camioes = tree_new( comparaCamioes );
    for( i=0; i<10; i++){
        tree_insert(*camioes, camiao_novo(i, allocStr(matricula[i]), i*0.1, i*10, allocStr(local[i])));
    }


    return 1;
}


//
//
// FUNÇÕES DE INPUT ESPEFÍFICAS
//
// LOCALIDADES

void inserelocalidadeinput (TabelaHashPTR table)
{   
    char *inputlocal=NULL;

    printf("Nome da localidade a inserir > ");
    lerStr(&inputlocal); 
    switch (inserelocalidade(table, inputlocal)){
        case -1: errorMessage(ERROR_LOCEXIST); break;
        case 0: errorMessage(ERROR_MEMALOC); break;
        case 1: errorMessage(ERROR_SUCCESS); break;
    }
}



void removelocalidadeinput(TabelaHashPTR table)
{
    char *inputlocal=NULL;

    printf("Nome da localidade a remover > ");
    lerStr(&inputlocal);
    switch (removerlocalidade(table, inputlocal))
    {
        case -1: errorMessage(ERROR_MEMALOC); break;
        case 0: errorMessage(ERROR_LOCNOTEXIST); break;
        case 1: errorMessage(ERROR_SUCCESS); break;
    }
}



void insereligacaoinput(TabelaHashPTR table){
    char *localorigem=NULL, *localdest=NULL;
    double custo, distancia;


    printf("Introduza localidade de origem > ");
    lerStr(&localorigem);
    printf("Introduza localidade de destino > ");
    lerStr(&localdest);
    printf("Introduza o custo de portagens > ");
    custo=readDouble();
    printf("Introduza a distância > ");
    distancia=readDouble();

    switch(inserirligacao(table,localorigem,localdest,custo,distancia)){
        case -2: errorMessage(ERROR_MEMALOC); break;
        case -1: errorMessage(ERROR_LOCNOTEXIST); break;
        case 0: errorMessage(ERROR_LIGLOCEXIST); break; 
        case 1: errorMessage(ERROR_SUCCESS); break;

    }

}


void removeligacaoinput(TabelaHashPTR table){
    char *localorigem=NULL, *localdest=NULL;
    printf("Introduza localidade de origem > ");
    lerStr(&localorigem);
    printf("Introduza localidade de destino > ");
    lerStr(&localdest);

    switch(removerligacao (table,localorigem, localdest)){
        case -1: errorMessage(ERROR_LOCNOTEXIST); break;
        case 0:  errorMessage(ERROR_LIGLOCNOTEXIST); break; 
        case 1: errorMessage(ERROR_SUCCESS); break;
    }
}



void editaligacaoinput(TabelaHashPTR localidades)
{
    char *localorigem=NULL, *localdest=NULL;
    printf("Introduza localidade de origem > ");
    lerStr(&localorigem);
    printf("Introduza localidade de destino > ");
    lerStr(&localdest);
    LocalidadePTR localidadeida = crialocalidade(localorigem);
    LocalidadePTR localidadevinda = crialocalidade(localdest);
    LigacoesidaPTR localidadedestino = crialigacaoida(localdest, 0,0);

    LocalidadePTR aux;
    double custo, distancia;

    if ((procuraTabelaHash(localidades, localidadeida)==NULL) || (procuraTabelaHash(localidades, localidadevinda)==NULL))
        errorMessage(ERROR_LOCNOTEXIST);
    else{
        aux = (((LinkedListPTR)procuraTabelaHash(localidades, localidadeida))->extdata);
        if ((procuraElementoLista(aux->ligacoesida,localidadedestino)==NULL))
            errorMessage(ERROR_LIGLOCNOTEXIST);
        else{
            printf("Irá alterar a ligação entre %s e %s.\n", localorigem,localdest );
            printf("Novo custo da ligação > ");
            custo=readDouble();
            printf("Nova distância da ligação > ");
            distancia=readDouble();
            removerligacao(localidades, localorigem, localdest);
            inserirligacao(localidades, localorigem, localdest,custo,distancia);
            errorMessage(ERROR_SUCCESS);
        }
    }

}

void imprimelistaligacoesinput(TabelaHashPTR localidades)
{
    char *nomelocalidade=NULL;
    printf("Introduza localidade de origem > ");
    lerStr(&nomelocalidade);
    LocalidadePTR localidade = crialocalidade(nomelocalidade);
    LocalidadePTR aux;

    if (procuraTabelaHash(localidades, localidade)==NULL)
        errorMessage(ERROR_LOCNOTEXIST);
    else
    {
        aux = (((LinkedListPTR)procuraTabelaHash(localidades, localidade))->extdata);
        if (aux->ligacoesida->elems==NULL) errorMessage(ERROR_NOLIGS);
        else
        imprimelistaligacoes(aux->ligacoesida->elems);
    }
}

void imprimeLocalidades (TabelaHashPTR table){
    int n= table->totalcells;
    MainListPTR *aux = table->arraycell;
    int i;
    for (i=0; i<n; i++){
        printf("%d\n", i);
        imprimelista(aux[i]->elems);
    }

}

void imprimelista(LinkedListPTR lista){
    LinkedListPTR aux=lista;
    LocalidadePTR local;
    while (aux){
        local = aux->extdata;
        printf("%s",(char*)local->nome);
        aux=aux->prox;
    }
}

void imprimelistaligacoes(LinkedListPTR lista){
    LinkedListPTR aux=lista;
    LigacoesidaPTR local;
    while (aux!=NULL){
        local = aux->extdata;
        printf("%s %0.2f %0.2f\n",(char*)local->nome, (double)local->custo, (double)local->distancia);
        aux=aux->prox;
    }
}

//
// CAMIOES
//

void camiaoi_insere(MainTreePt camioes, TabelaHashPTR localidades){
    unsigned int id;
    char *matricula=NULL, *local=NULL, vazia[1]={'\0'};
    LinkedListPTR localidade=NULL;
    double custo, peso;

    printf("Introduza o ID > ");
    while( isUInt(id = readUInt()) == 0 )
        printf("Erro: Valor inválido (veja as instruções acima)"); //erro

    printf("Introduza a matrícula > ");
    lerStr( &matricula);
    printf("Custo (por Km) > ");
    if( isDouble(custo = readDouble()) == 0 )
        printf("Erro: Valor inválido (veja as instruções acima)"); //erro
    printf("Peso máximo da carga > ");
    if( isDouble(peso = readDouble()) == 0 )
        printf("Erro: Valor inválido (veja as instruções acima)"); //erro
    
    printf("Localidade actual > ");
    lerStr( &local );
    while( (localidade = procuraTabelaHash( localidades, crialocalidade(local) ) ) == NULL && strcmp(local,vazia) != 0 ){
        printf("Erro: Localidade não foi encontrada. Para cancelar apenas pressione [ENTER].\nLocalidade actual > ");
        lerStr( &local );
    }
    free(localidade);
    if( strcmp(local,vazia) == 0 ){
        printf("Cancelou a introdução.\n");
        free(matricula);
        free(local);
    }else
        if( tree_insert( camioes, camiao_novo(id, matricula, custo, peso, local) ) == 1 )
            printf("Dados introduzidos com sucesso!");
        else
            printf("Já existe um Camião com esse ID ou Matrícula");
}

void camiaoi_lista(MainTreePt camiao){
    int input=-1;
    printf("Pretende os resultados ordenados por ID(0) ou matrícula(1)? > ");
    while( isInt(input = readInt()) == 0 && input != 0 && input != 1 )
        printf("Erro: Valor inválido. Valores possíveis: 0 ou 1\n"); //erro
    if( input == 0)
        tree_applyToAllOrdered( camiao, 0, camiao_dump);
    else if(input == 1)
        tree_applyToAllOrdered( camiao, 1, camiao_dump);
}

void camiaoi_remove(MainTreePt camiao){
    char *input=NULL;
    int tmpi;
    CamiaoPt tmp=NULL;
    printf("ID ou Matricula do camião > ");
    lerStr( &input );

    printf("Introduziu um ID (0) ou matricula (1)? > ");
    while( isInt(tmpi = readInt()) == 0 && tmpi != 0 && tmpi != 1 )
        printf("Erro: Valor inválido. Valores possíveis: 0 ou 1\n"); //erro

    if( tmpi == 0 ){
        tmp = camiao_novo( (int)strtol(input, NULL, 10), "", 0,0,NULL);
    }else{
        tmp = camiao_novo(0, input, 0,0,NULL);
    }
    tree_remove(camiao, tmp, tmpi);
    free(tmp);
    printf("Foi removido\n");
}

void camiaoi_modifica(MainTreePt camioes, TabelaHashPTR localidades){
    char *matricula=NULL, *local=NULL, vazia[1]={'\0'};
    LinkedListPTR localidade=NULL;
    double custo, peso;

    printf("Introduza a matricula do camiao a modificar > ");
    lerStr( &matricula);

    printf("Custo (por Km) > ");
    if( isDouble(custo = readDouble()) == 0 )
        printf("Erro: Valor inválido (veja as instruções acima)"); //erro
    printf("Peso máximo da carga > ");
    if( isDouble(peso = readDouble()) == 0 )
        printf("Erro: Valor inválido (veja as instruções acima)"); //erro
    
    printf("Localidade actual > ");
    lerStr( &local );
    while( (localidade = procuraTabelaHash( localidades, crialocalidade(local) ) ) == NULL && strcmp(local,vazia) != 0 ){
        printf("Erro: Localidade não foi encontrada. Para cancelar apenas pressione [ENTER].\nLocalidade actual > ");
        lerStr( &local );
    }
    free(localidade);
    if( strcmp(local,vazia) == 0 ){
        printf("Cancelou a introdução.\n");
        free(matricula);
        free(local);
    }else{
        camiao_substituiPelaMatricula( camioes, matricula, custo, peso, local );
        printf("Modificado!");
    }
}
