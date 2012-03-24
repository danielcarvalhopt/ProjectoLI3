/**
 * @file mod_avl_n_dimensional.h
 * @brief Módulo de árvores AVL com N dimensões
 * @detail Módulo de árvores AVL que utiliza um array de apontadores para a esquerda e para
 *         a direita, com o objectivo de ter várias árvores AVL a ocuparem o mesmo espaço de memória.
 *         Esta árvore permite que estejam, no mesmo espaço de memória, N árvores AVL, organizadas por
 *         campos diferentes (por exemplo: nome, idade e número de aluno).
 *         As várias "dimensões" da árvore são as várias maneiras como a árvore está logicamente organizada.
 * */
#ifndef MOD_AVL_N_DIMENSIONAL_H_INCLUDED
#define MOD_AVL_N_DIMENSIONAL_H_INCLUDED

#define DIM 2 /**< Número de dimensões da árvore */

/** Estrutura de sub-árvore */
typedef struct sTree{
    void *node;           /**< Apontador para dados externos                                     */
    struct sTree *l[DIM]; /**< Array de apontadores para a esquerda                              */
    struct sTree *r[DIM]; /**< Array de apontadores para a direita                               */
    int height[DIM];      /**< Array que indica a altura da sub-árvore em cada uma das dimensões */
} Tree, *TreePt;

/** Estrutura de controlo da árvore AVL de N dimensões */
typedef struct sMainTree{
    TreePt tree[DIM];                 /**< Array de apontadores para o topo da árvore                */
    int (*compare[DIM])(void*,void*); /**< Array de apontadores para a função de comparação de nodos */
} MainTree, *MainTreePt;

/**
 * @brief Inicializa um nova árvore
 * @param compare Array de apontadores para funções de comparação nas várias dimensões da árvore
 * @return Apontador para a estrutura de controlo da árvore
 * */
MainTreePt tree_new( int (*compare[DIM])(void*,void*) );

/**
 * @brief Insere um nodo na árvore
 * @param thisMainTree Apontador para a estrutura principal da árvore
 * @param node Apontador para o nodo a inserir na árvore
 * @return Inteiro com o seguinte significado:
 *         0 - nodo já existe
 *         1 - nodo inserido em todas as dimensões
 * */
int tree_insert( MainTreePt thisMainTree, void* node);

/**
 * @brief Procura o nodo em determinada dimensão da árvore
 * @param thisMainTree Apontador para a estrutura principal da árvore
 * @param node Apontador para o nodo com a informação a procurar
 * @param thisDim Dimensão em que se deve fazer a procura
 * @return Apontador para a sub-árvore onde foi encontrada uma correspondência com 'node'
 *         NULL caso não encontre nenhuma correspondência
 * */
TreePt tree_search(MainTreePt thisMainTree, void* node, int thisDim);

/**
 * @brief Aplicar uma função a todos os elementos da árvore em determinada dimensão
 * @param thisMainTree Apontador para a estrutura de controlo da árvore
 * @param thisDim Dimensão em que se quer aplicar a função
 * @param func Apontador para a função que se quer aplicar
 * */
void tree_applyToAllOrdered(MainTreePt thisMainTree, int thisDim, void (*func)(void*));

/**
 * @brief Remover um elemento da árvore
 * @detail Procura o elemento semelhante ao apontado por node, se encontrar, remove-o
 * @param thisMainTreePt Apontador para a estrutura de controlo da árvore
 * @param node Apontador para o nodo com informação de procura
 * */
void tree_remove( MainTreePt thisMainTreePt, void* node );

/**
 * @brief Apagar a árvore e todas as suas sub-árvores
 * @param thisMainTree Apontador para a estrutura de controlo da árvore
 * */
void tree_dispose( MainTreePt *thisMainTree );

/**
 * @brief Obter o nodo a partir da sub-árvore
 * @param thisTreePt Apontador para a sub-árvore
 * @return Apontador para o nodo da sub-árvore
 * */
void* tree_getElem( TreePt thisTreePt );

/*
 * STATIC
static int tree_getHeight(TreePt tree, int thisDim);
static TreePt tree_searchRec(TreePt thisTreePt, void* node, int thisDim, int (*compare)(void*,void*));
static int tree_insertRec( TreePt *thisTree, TreePt allocd, void* node, int thisDim, int (*compare)(void*,void*));
static void tree_printOrderedRec( TreePt thisTree, void (*print)(void*,int,void*), int thisDim );
static void tree_maintain( TreePt *thisTree, int thisDim);
static void tree_singleRotateLeft( TreePt *thisTreePt, int thisDim );
static void tree_singleRotateRight( TreePt *thisTreePt, int thisDim );
static void tree_doubleRotateLeftRight( TreePt *thisTreePt, int thisDim );
static void tree_doubleRotateRightLeft( TreePt *thisTreePt, int thisDim );

static void tree_searchTreeToDisconnect( TreePt *thisTreePt, int thisDim, void* node, int (*compare)(void*,void*) );
static void tree_disconnectTree( TreePt *thisTreePt, int thisDim, int (*compare)(void*,void*) );
static void tree_pushUp( TreePt *master, TreePt *thisTreePt, int thisDim, int (*compare)(void*,void*) );

static void tree_disposeRec( TreePt *thisTreePt );
*/

#endif /* MOD_AVL_N_DIMENSIONAL_H_INCLUDED */
