



typedef struct doomz{
    char *num1;
    char *num2;
}doomz;


/* Lista Ligada */
typedef struct linkedList {
	void *extdata;             
	struct linkedList *prox; 
} *LinkedListPTR;

/**
 * Estrutura de uma lista ligada
 */
typedef struct MainList {
	LinkedListPTR elems;                         
	int nelems;                              
} *MainListPTR;

/**
 * @fn List_Create
 * @brief Cria uma nova lista
 * 
 * @param compareFunction Funcao de comparacao para insercao ordenada
 * @return Lista criada
 */
MainListPTR crialistaligada(MainListPTR lista);

/**
 * @fn List_Push
 * @brief Insere um elemento no topo da lista
 *
 * @param list Lista a usar
 * @param newData dados a inserir
 * @return 0 em caso de sucesso
 */
int List_Push(MainListPTR list, void *extdata);
