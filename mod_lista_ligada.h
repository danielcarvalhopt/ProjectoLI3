/**
 * @file mod_lista_ligada.h
 * @brief Listas ligadas
 * @details Define listas ligadas genéricas e as suas funções
 * */
#ifndef MOD_LISTA_LIGADA_H_INCLUDED
#define MOD_LISTA_LIGADA_H_INCLUDED

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



/**
	@brief Cria a estrutura de controlo de uma lista ligada
	@param func_compare Função de comparação
	@return Apontador para a estrutura de controlo criada
 */
MainListPTR criaListaLigada(int(*func_compare)(void*,void*));



/**
	@brief Insere um elemento na cabeça da lista
	@param lista Estrutura de controlo da lista onde se irá inserir o elemento
	@param externdata Apontador para os dados a inserir na lista
	@return 0 em caso de falha
	@return 1 em caso de sucesso
 */
 int insereListaInicio(MainListPTR lista, void *externdata); 



 /**
	@brief Insere um elemento na lista ordenadamente de forma crescente
	@param lista Estrutura de controlo da lista onde se irá inserir o elemento
	@param externdata Apontador para os dados a inserir na lista
	@return 0 em caso de falha
	@return 1 em caso de sucesso
 */
 int insereListaOrdenado (MainListPTR lista, void *externdata);



/**
	@brief Liberta um elemento da memória
	@param elem Apontador para um apontador para uma lista ligada
 */
void apagaElemento (LinkedListPTR *elem);



/**
	@brief Apaga um elemento de uma lista ligada libertando-o da memória
	@param lista Apontador para a estrutura de controlo da lista ligada
        @param externdata Apontador para os dados que se querem remover da lista
	@return 1 se houve remoção
	@return 0 se não houve remoção
 */
int apagaElementoLista (MainListPTR lista, void* externdata);



/**
	@brief Procura um dado elemento na lista ligada
	@param lista Apontador para a estrutura de controlo da lista ligada
	@param externdata Elemento a procurar na lista
	@return Apontador para o elemento encontrado na lista ou NULL caso não seja encontrado
 */
LinkedListPTR procuraElementoLista (MainListPTR lista, void *externdata);



/**
	@brief Apaga da memória uma lista ligada completa
	@param lista Apontador para a estrutura de controlo da lista ligada
 */
void apagaListaAux(LinkedListPTR *lista);



/**
	@brief Apaga da memória uma lista ligada e actualiza a estrutura de controlo em função disso
	@param lista Apontador para a estrutura de controlo da lista ligada
 */
void apagaLista(MainListPTR lista);



#endif /* MOD_LISTA_LIGADA_H_INCLUDED */
