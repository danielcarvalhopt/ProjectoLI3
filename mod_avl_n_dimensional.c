/**
 * @file mod_avl_n_dimensional.c
 * @brief Definições estáticas do módulo de árvores
 * */
#include <stdlib.h>
#include <stdio.h>
#include "mod_avl_n_dimensional.h"
#include "utils.h"

/**
 * @brief Obter a altura de determinada sub-árvore em determinada dimensão
 * @param tree Apontador para a sub-árvore
 * @param thisDim Dimensão em questão
 * @return Altura da sub-árvore ou 0 se a sub-árvore nao existir
 * */
static int tree_getHeight(TreePt tree, int thisDim){
    return tree!=NULL ? tree->height[thisDim] : 0;
}

/**
 * @brief Rodar sub-árvore com a sub-árvore èsquerda
 * @param thisTreePt Apontador para o apontador para a sub-árvore
 * @param thisDim Dimensão em que se deve fazer troca
 * */
static void tree_singleRotateLeft( TreePt *thisTreePt, int thisDim ){
    TreePt node = (*thisTreePt)->r[thisDim];
    unsigned int lh, rh;

    (*thisTreePt)->r[thisDim] = node->l[thisDim];
    node->l[thisDim] = (*thisTreePt);

    lh = tree_getHeight( (*thisTreePt)->l[thisDim], thisDim );
    rh = tree_getHeight( (*thisTreePt)->r[thisDim], thisDim );
    (*thisTreePt)->height[thisDim] = lh > rh ? lh+1 : rh+1;

    lh = (*thisTreePt)->height[thisDim];
    rh = tree_getHeight( node->l[thisDim], thisDim );

    node->height[thisDim] = lh > rh ? lh+1 : rh+1;

    *thisTreePt = node;
}


/**
 * @brief Rodar sub-árvore com a sub-árvore direita
 * @param thisTreePt Apontador para o apontador para a sub-árvore
 * @param thisDim Dimensão em que se deve fazer troca
 * */
static void tree_singleRotateRight( TreePt *thisTreePt, int thisDim ){
    TreePt node = (*thisTreePt)->l[thisDim];
    unsigned int lh, rh;

    (*thisTreePt)->l[thisDim] = node->r[thisDim];
    node->r[thisDim] = (*thisTreePt);

    lh = tree_getHeight( (*thisTreePt)->l[thisDim], thisDim );
    rh = tree_getHeight( (*thisTreePt)->r[thisDim], thisDim );
    (*thisTreePt)->height[thisDim] = lh > rh ? lh+1 : rh+1;

    lh = tree_getHeight( node->l[thisDim], thisDim );
    rh = (*thisTreePt)->height[thisDim];

    node->height[thisDim] = lh > rh ? lh+1 : rh+1;

    *thisTreePt = node;
}


/**
 * @brief Dupla rotação direita esquerda
 * @param thisTreePt Apontador para o apontador para a sub-árvore
 * @param thisDim Dimensão em que se deve fazer troca
 * */
static void tree_doubleRotateRightLeft( TreePt *thisTreePt, int thisDim ){
    tree_singleRotateRight( &(*thisTreePt)->r[thisDim], thisDim );
    tree_singleRotateLeft( thisTreePt, thisDim );
}


/**
 * @brief Dupla rotação esquerda direita
 * @param thisTreePt Apontador para o apontador para a sub-árvore
 * @param thisDim Dimensão em que se deve fazer troca
 * */
static void tree_doubleRotateLeftRight( TreePt *thisTreePt, int thisDim ){
    tree_singleRotateLeft( &(*thisTreePt)->l[thisDim], thisDim );
    tree_singleRotateRight( thisTreePt, thisDim);
}

/**
 * @brief Balancear a árvore em determinada dimensão
 * @param thisTree Apontador para apontador para a sub-árvore
 * @param thisDim Dimensão a balancear
 * */
static void tree_maintain( TreePt *thisTree, int thisDim){
    if( *thisTree == NULL ) return;

    unsigned int lh = tree_getHeight( (*thisTree)->l[thisDim], thisDim );
    unsigned int rh = tree_getHeight( (*thisTree)->r[thisDim], thisDim );
    
    if( lh - rh == 2 ){ //sub arvore esquerda desequilibrada?
        lh = tree_getHeight( (*thisTree)->l[thisDim]->l[thisDim], thisDim );
        rh = tree_getHeight( (*thisTree)->l[thisDim]->r[thisDim], thisDim );
        if( lh >= rh ) tree_singleRotateRight( &(*thisTree), thisDim );
                  else tree_doubleRotateLeftRight( &(*thisTree), thisDim );
    }else if( rh - lh == 2 ){ //sub arvore direita desequilibrada?
        rh = tree_getHeight( (*thisTree)->r[thisDim]->r[thisDim], thisDim );
        lh = tree_getHeight( (*thisTree)->r[thisDim]->l[thisDim], thisDim );
        if( rh >= lh ) tree_singleRotateLeft( &(*thisTree), thisDim );
                  else tree_doubleRotateRightLeft( &(*thisTree), thisDim );
    }else{
        (*thisTree)->height[thisDim] = lh > rh ? lh+1 : rh+1;
    }
}

/**
 * @brief Função recursiva de procura (auxiliar)
 * @param thisTreePt Apontador para a sub-árvore
 * @param node Apontador para o nodo com a informação a procurar
 * @param thisDim Dimensão em que se deve fazer a procura
 * @param compare Apontador para a função de comparação
 * @return Apontador para a sub-árvore onde foi encontrada uma correspondência com 'node'
 *         NULL caso não encontre nenhum correspondência
 * @see tree_search()
 * */
static TreePt tree_searchRec(TreePt thisTreePt, void* node, int thisDim, int (*compare)(void*,void*)){
    int cmp = 0;
    if( thisTreePt == NULL )
        return NULL;
    
    cmp = compare(thisTreePt->node, node);

    if( cmp > 0 )
        return tree_searchRec( thisTreePt->l[thisDim], node, thisDim, compare );
    else if( cmp < 0 )
        return tree_searchRec( thisTreePt->r[thisDim], node, thisDim, compare );
    else
        return thisTreePt;
}

TreePt tree_search(MainTreePt thisMainTree, void* node, int thisDim){
    return tree_searchRec(thisMainTree->tree[thisDim], node, thisDim, thisMainTree->compare[thisDim]);
}

MainTreePt tree_new( int (*compare[DIM])(void*,void*) ){
    int i;
    MainTreePt new;
    if( (new = (MainTreePt) malloc( sizeof(MainTree))) != NULL ){ 
        for( i=0; i<DIM; i++){
            new->compare[i] = compare[i];
            new->tree[i] = NULL;
            new->nodos = 0;
        }
    }
    return new;
}

/**
 * @brief Função auxiliar de inserção recursiva
 * @param thisTree Apontador para apontador para a sub-árvore
 * @param allocd Apontador para uma sub-árvore previamente alocada
 * @param node Apontador para o nodo, para efeitos de comparação
 * @param thisDim Dimensão em que se quer inserir o nodo
 * @param compare Apontador para a função de comparação
 * */
static void tree_insertRec( TreePt *thisTree, TreePt allocd, void* node, int thisDim, int (*compare)(void*,void*)){
    if( *thisTree == NULL )
        *thisTree = allocd;
    else{
        if( compare((*thisTree)->node, node) < 0 ){ // existente é menor que o que se quer inserir -> inserir à direita
            tree_insertRec( &(*thisTree)->r[thisDim], allocd, node, thisDim, compare );
        }else{                                      // existente é maior que o que se quer inserir -> inserir à esquerda
            tree_insertRec( &(*thisTree)->l[thisDim], allocd, node, thisDim, compare );
        }
    }

    tree_maintain( thisTree, thisDim );
}

int tree_insert( MainTreePt thisMainTree, void* node){
    int i;
    TreePt thisTreePt = NULL;
    for( i=0; i<DIM && thisTreePt == NULL; i++ )
        thisTreePt = tree_search(thisMainTree, node, i);

    if( thisTreePt == NULL ){ //alocar o espaço dele, depois é que se vai preencher com apontadores esq e dir
        thisTreePt = (TreePt)malloc(sizeof(Tree));
        thisTreePt->node = node;
        for(i=0; i<DIM; i++){
            thisTreePt->l[i] = NULL;
            thisTreePt->r[i] = NULL;
            thisTreePt->height[i] = 1;
        }
        for( i=0; i<DIM; i++)
            tree_insertRec( &thisMainTree->tree[i], thisTreePt, node, i, thisMainTree->compare[i] );
        thisMainTree->nodos++;
        return 1;
    }
    return 0;
}

/**
 * @brief Mover o menor nodo da sub-árvore direita de forma a poder remover o nodo actual com segurança
 * @details A função vai encontrar a menor sub-árvore (thisTreePt) na sub-árvore direita do 'master'
 *          e vai trocar as ligações de modo a transformar a 'thisTreePt' na nova 'master' sem perder
 *          as ligações já existentes.\n
 *          Esta função só é necessária quando o nodo que se quer remover tem sub-árvores esquerda e direita.
 * @param master Apontador para apontador para a sub-árvore a trocar
 * @param thisTreePt Apontador para apontador para a sub-árvore que vai subir
 * @param thisDim Dimensão em que se quer balancear a árvore
 * @param compare Apontador para a função de comparação de nodos
 * */
static void tree_pushUp( TreePt *master, TreePt *thisTreePt, int thisDim, int (*compare)(void*,void*) ){
    TreePt aux = NULL;
    if( (*thisTreePt)->l[thisDim] == NULL ){ // direita e Xvezes esquerda
        aux = (*thisTreePt)->r[thisDim];
        (*thisTreePt)->l[thisDim] = (*master)->l[thisDim];
        if( (*thisTreePt) != (*master)->r[thisDim] )
            (*thisTreePt)->r[thisDim] = (*master)->r[thisDim];
        else
            (*thisTreePt)->r[thisDim] = NULL;
        *master = *thisTreePt;

        *thisTreePt = aux;
    }else tree_pushUp( master ,&(*thisTreePt)->l[thisDim], thisDim, compare ); // mais uma vez para a esquerda

    tree_maintain( thisTreePt, thisDim );
}

/**
 * @brief Desconectar a sub-árvore
 * @param thisTreePt Apontador para apontador da sub-árvore a remover
 * @param thisDim Dimensão em que se quer remover a sub-árvore
 * @param compare Apontador para a função de comparação
 * */
static void tree_disconnectTree( TreePt *thisTreePt, int thisDim, int (*compare)(void*,void*) ){
    if( (*thisTreePt)->l[thisDim] != NULL && (*thisTreePt)->r[thisDim] != NULL )
        tree_pushUp( thisTreePt ,&(*thisTreePt)->r[thisDim], thisDim, compare );
    else if( (*thisTreePt)->l[thisDim] == NULL )
        *thisTreePt = (*thisTreePt)->r[thisDim];
    else if( (*thisTreePt)->r[thisDim] == NULL )
        *thisTreePt = (*thisTreePt)->l[thisDim];
}

/**
 * @brief Procura a sub-árvore, e quando a encontrar, chama a função para a desconectar
 * @param thisTreePt Apontador para apontador para a sub-árvore
 * @param thisDim Dimensão em que se quer remover a sub-árvore
 * @param node Apontador para o nodo a procurar
 * @param compare Apontador para a função de comparação
 * */
static void tree_searchTreeToDisconnect( TreePt *thisTreePt, int thisDim, void *node, int (*compare)(void*,void*) ){
    int cmp = 0;
    if( *thisTreePt == NULL ) return;
    
    cmp = compare( (*thisTreePt)->node, node);

    if( cmp > 0 )
        tree_searchTreeToDisconnect( &(*thisTreePt)->l[thisDim], thisDim, node, compare );
    else if( cmp < 0 )
        tree_searchTreeToDisconnect( &(*thisTreePt)->r[thisDim], thisDim, node, compare );
    else
        tree_disconnectTree(thisTreePt, thisDim, compare);
        
    tree_maintain(thisTreePt, thisDim);
}

void tree_remove( MainTreePt thisMainTreePt, void* node ){
    int i;
    TreePt elem = tree_search( thisMainTreePt, node, 0);
    if( elem == NULL ) return;

    for( i=0; i<DIM; i++ )
        tree_searchTreeToDisconnect( &thisMainTreePt->tree[i], i, node, thisMainTreePt->compare[i] );

    free(elem);
    thisMainTreePt->nodos--;
}

/**
 * @brief Função auxiliar recursiva para aplicar uma função a todos os elementos da árvore InOrder
 * @param thisTree Apontador para a sub-árvore na qual se vai aplicar a função
 * @param func Apontador para a função a aplicar
 * @param thisDim Dimensão onde se vai aplicar a função
 * @see tree_applyToAllOrdered()
 * */
static void tree_applyToAllOrderedRec( TreePt thisTree, void (*func)(void*), int thisDim ){
    if( thisTree != NULL ){
        tree_applyToAllOrderedRec( thisTree->l[thisDim], func, thisDim);
        func(thisTree->node);
        tree_applyToAllOrderedRec( thisTree->r[thisDim], func, thisDim);
    }
}

void tree_applyToAllOrdered(MainTreePt thisMainTree, int thisDim, void (*func)(void*)){
    if( thisMainTree != NULL )
        tree_applyToAllOrderedRec( thisMainTree->tree[thisDim], func, thisDim );
}

/**
 * @brief Faz recursivamente free às sub-árvores da árvore
 * @param thisTreePt sub-árvore a que se quer fazer free
 * */
static void tree_disposeRec( TreePt *thisTreePt ){
    if( *thisTreePt != NULL ){
        tree_disposeRec( &(*thisTreePt)->l[0] );
        tree_disposeRec( &(*thisTreePt)->r[0] );
        free( *thisTreePt );
    }
}

void tree_dispose( MainTreePt *thisMainTree ){
    tree_disposeRec( &(*thisMainTree)->tree[0] );
    free( *thisMainTree );
}

void* tree_getElem( TreePt thisTreePt ){
    if( thisTreePt == NULL )
        return NULL;
    return thisTreePt->node;
}

