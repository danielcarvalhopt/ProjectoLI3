#ifndef ARVORE_H_INCLUDED
#define ARVORE_H_INCLUDED

/********************************
 * Grafo / Árvore - Localidades *
 ********************************/

 /* Arvore de Adjacências */
typedef struct sAdjacente {
       char *nome;
       int custo;
       int distancia;
       struct sAdjacente *esq, *dir;
} Adjacente;

/* Arvore de Vertices */
typedef struct sVertice {
       char *nome;
       Adjacente *adj;
       struct sVertice *esq, *dir;
} Vertice;


/*********************
 * Arvore de Camioes *
 *********************/
/* Arvore de Camioes */
typedef struct sCamiao {
	unsigned int id;
	int capacidadecarga;
	char *matricula;
	float consumo;
	struct sCamiao *iesq, *idir; // arvore de identificador de camiao
	struct sCamiao *mesq, *mdir; // arvore de matrícula de camiao
} Camiao;

/*************************************************
 * Arvore de Clientes e Lista Ligada de Serviços *
 *************************************************/
/* Lista Ligada de Serviços */
typedef struct sServico {
	unsigned int timestamp; //acho que era de valor ter uma data e hora do pedido
	Camiao *camiao;
	Vertice *estava;  // localizaçao do camiao aquando do pedido
	Vertice *carga;   // local onde o camiao foi carregado
	Vertice *destino; // local onde o camiao ficou no fim da viagem
	struct sServico *ant;    // apontador para o servico anterior
} Servico;

/* Arvore de Clientes */
typedef struct sCliente {
	unsigned int contribuinte; // NIF vai de 000,000,000 a +999,999,999, unsigned int vai de 0 a +4,294,967,295, mais que suficiente
	char *nome;
	char *morada;
	Servico *ultimo;
	struct sCliente *cesq, *cdir; // arvore de contribuintes de clientes
	struct sCliente *nesq, *ndir; // arvore de nomes de clientes
} Cliente;

#endif /* ARVORE_H_INCLUDED */
