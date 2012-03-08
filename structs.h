

/* Grafo - Localidades */


/* Lista ligada de Vertices */
typedef struct sListaVertices {
	char *nome;
	struct sListaVertices *prox;
} ListaVertices;


/* Lista Ligada de Adjacências */
typedef struct sListaAdj {
	char *nome;
	ListaVertices *adj;
	struct sListaAdj *prox;
} ListaAdj;
