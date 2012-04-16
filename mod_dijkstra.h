#ifndef _DIJKSTRA_H

#define _DIJKSTRA_H 1
#include "mod_tabela_hash.h"


#define VISITADO 1
#define ORLA 0
#define DESCONHECIDO -1 

typedef TabelaHashPTR GraphDijkstraPTR;

typedef struct GraphElem{
    char* nome;
    char *nomeAnterior;
    double distancia;
    double custoligacao;
    double custoCamiaoKm;
    int estado;
} *GraphElemPTR;

typedef struct sParametrosMap{
	void* params[3];
}ParametrosMap;


GraphDijkstraPTR startGraphDijkstra(TabelaHashPTR localidades, int(*hash_function)(void*,int), int startcells, int (*func_compare)(void*,void*),char* localidadeorigem, char*localidadedestino, double custocamiao);
GraphDijkstraPTR cheapestPathDijsktra(TabelaHashPTR localidades, GraphDijkstraPTR graphDijkstra, char* localidadeorigem, char* localidadedestino, double custoCamiaoKm);
void nextVertexDijkstra(void *elem, void *parametros);
void cheapestPathDijsktraAux(void *elem, void *parametros);

#endif