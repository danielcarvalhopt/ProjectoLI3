
/*----------------------------------------------*/
/* Módulo de Lista Ligada -> Estrutura de Dados */
/*----------------------------------------------*/


/**
	@brief Lista Ligada
	@details Lista ligada que guarda um apontador para dados externos e um apontador para o elemento seguinte
	@param extdata Apontador para dados externos
	@param prox Apontador para elemento seguinte da lista
 */
typedef struct linkedList {
	void *extdata;      		// Apontador para o elemento da lista       
	struct linkedList *prox;	// Próximo elemento da lista
} *LinkedListPTR; 				// Apontador para a lista ligada



/**
	@brief Estrutura de controlo de uma Lista Ligada
	@details Estrutura que permite controlar uma lista ligada
	@param elems Apontador para uma lista ligada
	@param nelems Número de elementos contidos na lista ligada
	@param func_compare Função de comparação de elementos da lista ligada
 */
typedef struct MainList {
	LinkedListPTR elems;     			// Apontador para uma lista ligada                    
	int nelems;  						// Numero de elementos da lista ligada
	int (*func_compare)(void*,void*);   // Função de comparação de elementos da lista ligada
} *MainListPTR; 						// Apontador para a estrutura de controlo





typedef struct Ligacoesida
{
	char* nome;
	float custo;
	float distancia;
}*LigacoesidaPTR;

typedef struct Ligacoesvinda
{
	char* nome;
}*LigacoesvindaPTR;


typedef struct Localidade
{
	char* nome;
	MainListPTR ligacoesida;
	MainListPTR ligacoesvinda;
}*LocalidadePTR;








/*------------------------------------------------*/
/* Módulo de Tabela de Hash -> Estrutura de Dados */
/*------------------------------------------------*/

/**
	@brief Tabela de Hash com chaining
	@details Tabela de Hash com elementos encadeados com listas ligadas
	@param arraycell Array de apontadores para uma lista ligada
	@param hash_function Função de hash para dispersão dos elementos pela tabela
	@param nelems Número de elementos inseridos na tabela
	@param totalcells Número de elementos da tabela
 */

typedef struct TabelaHash{
	MainListPTR *arraycell;
	int (*hash_function)(void*,int);
	int nelems;
	int totalcells;
}*TabelaHashPTR;


int removerligacao (TabelaHashPTR table, char *nomeorigem, char *nomedestino);
