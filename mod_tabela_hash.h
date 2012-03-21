

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



/**
	@fn hashtablecreator
	@brief Cria a tabela de hash e inicia as listas ligadas a NULL
	@param hash_function Função de hash para dispersão de elementos
	@param startcells Numero de elementos iniciais da tabela
	@return Apontador para tabela de hash
 */
TabelaHashPTR hashtablecreator (int(*hash_function)(void*,int), int startcells);



/**
	@fn hashtablecelluse
	@brief Verifica o factor de ocupação da tabela de hash 
	@param table Apontador para a tabela de hash
	@return 0 se está com um factor de ocupação maior que o indicado
	@return 1 se não está com um factor de ocupação maior que o indicado
 */
int hashtablecelluse (TabelaHashPTR table);



/**
	@fn hashtablerealloc
	@brief Aloca mais espaço para a tabela de hash caso esta tenha ultrapassado o factor de ocupação indicado
	@param table Apontador para a tabela de hash
	@return 0 se não conseguiu alocar espaço suficiente
	@return 1 se alocou com sucesso
 */
int hashtablerealloc (TabelaHashPTR table);



/**
	@fn hashtableinsertion
	@brief Insere um elemento na tabela de hash
	@param table Apontador para a tabela de hash
	@param externdata Apontador para o elemento a inserir
	@return 0 se não conseguiu inserir
	@return 1 se inseriu com sucesso
 */
int hashtableinsertion (TabelaHashPTR table, void *externdata);



/**
	@fn hashtablesearch
	@brief Procura um elemento na tabela de hash
	@param table Apontador para a tabela de hash
	@param externdata Apontador para o elemento a procurar
	@return Apontador para o elemento encontrado ou NULL
 */
LinkedListPTR hashtablesearch (TabelaHashPTR table, void *externdata);



/**
	@fn hashtableelemdeletion
	@brief Elimina um elemento dado da tabela de hash
	@param table Apontador para a tabela de hash
	@param externdata Apontador para o elemento a elimiar
	@return 1 se pagado
	@return 0 se não apagado/encontrado
 */
int hashtableelemdeletion (TabelaHashPTR table, void* externdata);



/**
	@fn hashtabledestroy
	@brief Elimina todos os elementos da tabela de hash
	@param table Apontador para a tabela de hash
 */
void hashtabledestroy(TabelaHashPTR table);



/**
	@fn hash_function
	@brief Indica o indice na tabela onde um elemento será inserido/procurado/eliminado
	@param a Apontador para os dados a analisar e criar hashkey
	@param b Numero de elementos total da tabela
 */
int hash_function(void*a,int b);























/***********   ZONA DE TESTES **************/
/***********   ZONA DE TESTES **************/
/***********   ZONA DE TESTES **************/
/***********   ZONA DE TESTES **************/
/***********   ZONA DE TESTES **************/
/***********   ZONA DE TESTES **************/
/***********   ZONA DE TESTES **************/
/********************************************


/*****
typedef struct hash_elem {
	//long long int key;                **< Chave do elemento guardado *
	void *data;             /**< Apontador para os dados guardados *
	struct hash_elem *next; /**< Apontador para o proximo elemento (hash table usando o metodo de chaining) *
} *HashElem;




/*
typedef struct hash_table {
	int useCount;                       **< Total de elementos guardados na tabela *
	int totalCount;                     **< Numero maximo de elementos suportados *
	int (*hashFunction)(void *, int);   **< Apontador para a funcao de hash *
	void *(*getKey)(void *);            **< Funcao que extrai a chave *
	int (*compareKeys)(void *, void *); **< Funcao que compara duas chaves *
        int duplicate;                      /**< Indica se a tabela aceita valores duplicados *
	HashElem *table;                    /**< Apontador para a tabela *
} HashTableStruct, *HashTable;
*/