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



GraphDijkstraPTR cheapestPathDijsktra(TabelaHashPTR localidades, char* localidadeorigem, char* localidadedestino, double custoCamiaoKm);
int nextVertexDijkstra(void *elem, void *parametros);
int cheapestPathDijsktraAux(void *elem, void *parametros);

#endif