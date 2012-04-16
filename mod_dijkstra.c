#include <stdlib.h>
#include <string.h>

#include "mod_dijkstra.h"
#include "mod_lista_ligada.h"
#include "dados.h"



int hash_function_dij (void *elemDij, int hashsize)
{
    GraphElemPTR vertex = (GraphElemPTR)elemDij; 
    char *nome;
    long int res=11; int i=0, j=0; int hashing[]={2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109};
    
    nome=(char*)vertex->nome;

    while (nome[i]!='\0')
    {
        if(nome[i]!='a'||nome[i]!='e'||nome[i]!='e'||nome[i]!='o'||nome[i]!='u')
        {
        res+=abs((int)((i+j+(nome[i]^i)*hashing[j]-(i+j))*hashing[j])*hashing[j+1]-i+j+hashing[j]+nome[i]);}
        if((nome[i]=='a'&&nome[i+1]=='\0') || ((nome[i]=='o'&&nome[i+1]=='\0')&&((strlen(nome)%7)==0)))
            res+=abs(hashing[j]*nome[0]-hashing[j]-i-hashing[j+2]);

        i++; j=(((nome[i]*hashing[j])+i)%30);


    }
    int hashkey= (int)(res%(long int)hashsize);
    return hashkey;
}


int comparaGraphElem (void *a, void *b){
    GraphElemPTR vertexA = (GraphElemPTR)a;
    GraphElemPTR vertexB = (GraphElemPTR)b;
    char *nomeA, *nomeB,*nomeC,*nomeD;
    nomeA=(char*)vertexA->nome;
    nomeB=(char*)vertexB->nome;
    nomeC=(char*)vertexA->nomeAnterior;
    nomeD=(char*)vertexB->nomeAnterior;

    return (strcmp(nomeA,nomeB)+strcmp(nomeC,nomeD));
}



GraphDijkstraPTR startGraphDijkstra(TabelaHashPTR localidades, int(*hash_function_dij)(void*,int), int startcells, int (*comparaGraphElem)(void*,void*),char* localidadeorigem, char*localidadedestino, double custocamiao)
{
    GraphDijkstraPTR graphDijkstra= criaTabelaHash(hash_function_dij, startcells, comparaGraphElem);
    GraphDijkstraPTR endDijkstra = cheapestPathDijsktra(localidades ,graphDijkstra, localidadeorigem, localidadedestino, custocamiao);
    return endDijkstra;
}
    


GraphDijkstraPTR cheapestPathDijsktra(TabelaHashPTR localidades, GraphDijkstraPTR graphDijkstra, char* localidadeorigem, char* localidadedestino, double custoCamiaoKm) 
{
    GraphElemPTR novo;
    if((novo = (GraphElemPTR)malloc(sizeof(struct GraphElem)))==NULL) return NULL;
    LocalidadePTR localidadeAux, localidadeAux2;

    int naOrla;
 
    strcpy(novo->nome,localidadeorigem);
    novo->nomeAnterior=NULL;
    novo->distancia = 0;    
    novo->custoligacao = 0;   
    novo->custoCamiaoKm = custoCamiaoKm;    
    novo->estado = ORLA;    

    insereElementoTabelaHash(graphDijkstra, novo);

    naOrla=1;
    while (naOrla>0) 
    {
        void **params = (void**) malloc (sizeof(void*)*3);
        params[0] = graphDijkstra;
        params[1] = novo;
        params[2] = &naOrla;

        //novo = NULL;
        aplicaFuncTabelaHash(graphDijkstra, &nextVertexDijkstra, &params[1]);
        localidadeAux2=(LocalidadePTR)crialocalidade(novo->nome);
        localidadeAux =(LocalidadePTR)procuraTabelaHash(localidades, localidadeAux2);
		
        aplicaFuncLista(localidadeAux->ligacoesida, &cheapestPathDijsktraAux, params);
        novo->estado = VISITADO;
     
        if (strcmp(novo->nome,localidadedestino)==0) return graphDijkstra;
        else naOrla=0;
    }
    
    return graphDijkstra;
}

void nextVertexDijkstra(void *elem, void *parametros) 
{
    GraphElemPTR nextVertex = (GraphElemPTR) elem;
    GraphElemPTR vertex = (GraphElemPTR) parametros;

    if (nextVertex->estado!=VISITADO && ((vertex == NULL) || (vertex->custoligacao + (vertex->distancia * vertex->custoCamiaoKm) > nextVertex->custoligacao + (nextVertex->distancia * nextVertex->custoCamiaoKm))))
        vertex=nextVertex;
}

void cheapestPathDijsktraAux(void *elem, void *parametros) {
    
    LigacoesidaPTR ligacao=(LigacoesidaPTR)elem;
    
    GraphDijkstraPTR graph = (GraphDijkstraPTR) ((void **) parametros)[0];
    GraphElemPTR vertex = (GraphElemPTR) ((void **) parametros)[1];
    int *naOrla = (int *) ((void **) parametros)[2];

    double totalkm = ligacao->distancia + vertex->distancia;
    double totalcustoligacao = ligacao->custo + vertex->custoligacao;
    double custocamiaoKm = vertex->custoCamiaoKm;
    double totalcusto = totalcustoligacao+(totalkm*custocamiaoKm);

    GraphElemPTR nextVertex = (GraphElemPTR) procuraTabelaHash(graph, ligacao->nome);
    
    if ((nextVertex!=NULL) && (nextVertex->estado != VISITADO) && (nextVertex->custoligacao+(nextVertex->custoCamiaoKm*nextVertex->distancia)) > totalcusto && nextVertex->distancia != -1) {
        nextVertex->distancia = totalkm;
        strcpy(nextVertex->nomeAnterior,vertex->nome);
    }
    else if (nextVertex==NULL) {
        nextVertex = (GraphElemPTR)malloc(sizeof(struct GraphElem));
        nextVertex->distancia = totalkm;
        nextVertex->custoligacao = totalcustoligacao;
        strcpy(nextVertex->nome,ligacao->nome);
        strcpy(nextVertex->nomeAnterior,vertex->nome);
        nextVertex->estado = ORLA;

        (*naOrla)++;

        insereElementoTabelaHash(graph, nextVertex);
    }
}

