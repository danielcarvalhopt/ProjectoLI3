#ifndef MOD_GRAPH_H_INCLUDED

#define MOD_GRAPH_H_INCLUDED 1
#include "mod_tabela_hash.h"
#include "dados.h"



#define VISITADO 1
#define ORLA 0
#define DESCONHECIDO -1 

typedef TabelaHashPTR GraphPTR;

typedef struct GraphElem{
    char *nome;
    char *nomeAnterior;
    double distancia;
    double custoCaminho;
    double custoCamiaoKm;
    int estado;
} *GraphElemPTR;

typedef struct sParametrosMap{
	void* params[3];
}ParametrosMap;

GraphElemPTR newVertex(char* nome, char* nomeAnterior, double distancia, double custoCaminho, double custoCamiaoKm, int estado);
GraphElemPTR chooseNextCheapestVertex (GraphPTR graph, GraphElemPTR proxVertice);
GraphPTR cheapestPathGraph(TabelaHashPTR localidades, char* localidadeorigem, char* localidadedestino, double custoCamiaoKm);
int buildPathGraph(GraphPTR graph, LigacoesidaPTR ligacao,GraphElemPTR vertex,int naOrla);
void imprimedijkstra(GraphPTR graphDijkstra);
#endif