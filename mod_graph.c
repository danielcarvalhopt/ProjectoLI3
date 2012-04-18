#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <limits.h>


#include "mod_graph.h"
#include "mod_lista_ligada.h"
#include "dados.h"



int hashFunctionGraph (void *elem, int hashsize)
{
    GraphElemPTR vertice = (GraphElemPTR)elem; 

    unsigned long long int res=11; 
    int i, j=0; 
    int hashing[]={2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 
    47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109};
    
    char* nome=(char*)vertice->nome;
    for (i=0;nome[i]!='\0' && j<27;i++)
    {
                if(((nome[i]>='A')&&(nome[i]<='Z'))||((nome[i]>='a')&&(nome[i]<='z'))){
                if(nome[i]!='a'||nome[i]!='e'||nome[i]!='e'||nome[i]!='o'||nome[i]!='u')
                {
                res+=abs(((int)nome[i])*(i+1)*hashing[j]);}
                if((nome[i]=='a'&&nome[i+1]=='\0') || ((nome[i]=='o'&&nome[i+1]=='\0')&&((strlen(nome)%7)==0)))
                    res+=abs(hashing[j]+nome[0]+(hashing[j]%30));

                j=hashing[j]%30;
            }
    }
    int hashkey= (int)(res%(unsigned long long int)hashsize);
    return hashkey;
}

int compareVertexCost(GraphElemPTR a, GraphElemPTR b)
{
    return ((a->custoCaminho+(a->custoCamiaoKm*a->distancia))>(b->custoCaminho+(b->custoCamiaoKm*b->distancia)));
}


int searchGraphElemAux (void *a, void *b){
    GraphElemPTR verticeA = (GraphElemPTR)a;
    GraphElemPTR verticeB = (GraphElemPTR)b;

    char* nomeA=(char*)verticeA->nome;
    char* nomeB=(char*)verticeB->nome;

    return (strcmp(nomeA,nomeB));
}



GraphElemPTR newVertex(char* nome, char* nomeAnterior, double distancia, double custoCaminho, double custoCamiaoKm, int estado)
{
    GraphElemPTR novo = (GraphElemPTR) malloc(sizeof(struct GraphElem));
    if (novo==NULL) return NULL;

    novo->nome=malloc(strlen(nome)+1);
    strcpy(novo->nome, nome);

    novo->nomeAnterior=malloc(strlen(nome)+1);
    strcpy(novo->nomeAnterior, nomeAnterior);

    novo->distancia=distancia;
    novo->custoCaminho=custoCaminho;
    novo->custoCamiaoKm=custoCamiaoKm;
    novo->estado=estado;

    return novo;
}



int buildPathGraph(GraphPTR graph, LigacoesidaPTR ligacao,GraphElemPTR vertex, int naOrla) 
{
    GraphElemPTR nextVertex, aux;
    LinkedListPTR auxvertex;

    double novoDistancia = ligacao->distancia+vertex->distancia;
    double novoCustoCaminho= vertex->custoCaminho + ligacao->custo + (ligacao->distancia*vertex->custoCamiaoKm);

    aux=(GraphElemPTR)newVertex(ligacao->nome, "",0,0,0,0);
    if((auxvertex = (LinkedListPTR)(procuraTabelaHash(graph, aux)))==NULL)
    {
        nextVertex=newVertex(ligacao->nome, vertex->nome, novoDistancia, novoCustoCaminho, vertex->custoCamiaoKm, ORLA);
        naOrla++;
        insereElementoTabelaHash(graph, nextVertex);
    }
    else {
            nextVertex=(GraphElemPTR)auxvertex->extdata;
            if ((nextVertex->estado != VISITADO) && (novoCustoCaminho < nextVertex->custoCaminho))
            {
                nextVertex->nomeAnterior=NULL;
                nextVertex->nomeAnterior=(char*)malloc(strlen(vertex->nome)+1);
                strcpy(nextVertex->nomeAnterior,vertex->nome);
                nextVertex->custoCaminho=novoCustoCaminho;
                nextVertex->distancia = vertex->distancia + ligacao->distancia;
            }
        }
    return naOrla;
}




GraphElemPTR chooseNextCheapestVertex (GraphPTR graph, GraphElemPTR proxVertice)
{
        LinkedListPTR throughCells; int i;
        for(i=0; i<(graph->totalcells);i++)
        {
            throughCells=graph->arraycell[i]->elems;
            while(throughCells)
            {
                GraphElemPTR verticeCheck=throughCells->extdata;
                if(verticeCheck->estado!=VISITADO &&((proxVertice==NULL)||proxVertice->distancia * proxVertice->custoCamiaoKm + proxVertice->custoCaminho > verticeCheck->distancia * verticeCheck->custoCamiaoKm + verticeCheck->custoCaminho))
                    proxVertice=verticeCheck;
                throughCells=throughCells->prox;
            }
        }
        return proxVertice;
} 


GraphPTR cheapestPathGraph(TabelaHashPTR localidades,  char* localidadeorigem, char* localidadedestino, double custoCamiaoKm) 
{
    GraphPTR graph;
    GraphElemPTR verticeOrigem, proxVertice;
    LocalidadePTR localidadeAux;
    int naOrla;

    graph=(GraphPTR)criaTabelaHash(hashFunctionGraph, 100000, searchGraphElemAux);
    verticeOrigem=(GraphElemPTR)newVertex(localidadeorigem, "_PATHSTART_", 0, 0 , custoCamiaoKm, ORLA); 
    naOrla=1;
    insereElementoTabelaHash(graph, verticeOrigem);
    do{
        proxVertice=chooseNextCheapestVertex(graph, NULL);
        localidadeAux=(LocalidadePTR)(procuraTabelaHash(localidades, crialocalidade(proxVertice->nome)))->extdata;
        LinkedListPTR throughList = localidadeAux->ligacoesida->elems;
        while(throughList)
        {
            naOrla=buildPathGraph(graph, throughList->extdata, proxVertice,naOrla);
            throughList=throughList->prox;
        }
        proxVertice->estado = VISITADO;
        if ((strcmp(proxVertice->nome,localidadedestino))==0) return graph;
        naOrla--;
    } while(naOrla>ORLA && (strcmp(proxVertice->nome,localidadedestino)!=0));

    return graph;
}


void imprimedijkstra(GraphPTR graphDijkstra)
{
    LinkedListPTR aux;
    GraphElemPTR vertex;
    int i;
    
    for(i=0; i<graphDijkstra->totalcells; i++)
    {
        aux=(graphDijkstra->arraycell[i]->elems);
        while(aux)
        {
            vertex=(GraphElemPTR)aux->extdata;
            printf("Nome: %s | NomeAnterior: %s | Distância: %.2f | CustoLigação: %.2f | CustoCamiao: %.2f \n", vertex->nome, vertex->nomeAnterior, vertex->distancia, vertex->custoCaminho, vertex->custoCamiaoKm);
            aux=aux->prox;
        }
    }
}




