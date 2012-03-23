#include <stdlib.h>
#include <stdio.h>
#include "mod_avl_n_dimensional.h"
#include "utils.h"

/* debug, passou para utils.c
int maxInt(int a,int b){
    return a>=b ? a : b;
} */

static int tree_getHeight(TreePt tree, int thisDim){
    return tree!=NULL ? tree->height[thisDim] : 0;
}


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

static void tree_doubleRotateRightLeft( TreePt *thisTreePt, int thisDim ){
    tree_singleRotateRight( &(*thisTreePt)->r[thisDim], thisDim );
    tree_singleRotateLeft( thisTreePt, thisDim );
}

static void tree_doubleRotateLeftRight( TreePt *thisTreePt, int thisDim ){
    tree_singleRotateLeft( &(*thisTreePt)->l[thisDim], thisDim );
    tree_singleRotateRight( thisTreePt, thisDim);
}

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
        }
    }
    return new;
}

static int tree_insertRec( TreePt *thisTree, TreePt allocd, void* node, int thisDim, int (*compare)(void*,void*)){
    int ret=1;
    if( *thisTree == NULL )
        *thisTree = allocd;
    else{
        if( compare((*thisTree)->node, node) < 0 ){ // existente é menor que o que se quer inserir -> inserir à direita
            ret = tree_insertRec( &(*thisTree)->r[thisDim], allocd, node, thisDim, compare );
        }else{                                      // existente é maior que o que se quer inserir -> inserir à esquerda
            ret = tree_insertRec( &(*thisTree)->l[thisDim], allocd, node, thisDim, compare );
        }
    }

    tree_maintain( thisTree, thisDim );

    return ret;
}

int tree_insert( MainTreePt thisMainTree, void* node){
    int i, sucesso = 0;
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
        sucesso = 1;
    }

    for( i=0; i<DIM && sucesso == 1; i++)
        tree_insertRec( &thisMainTree->tree[i], thisTreePt, node, i, thisMainTree->compare[i] );
    
    //for( i=0; i<DIM && sucesso == 1; i++)
    //    tree_maintain( &thisTreePt, i, thisMainTree->compare[i] );

    return sucesso; // 1 - inseriu em todos; 0 - já existe
}

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

static void tree_disconnectTree( TreePt *thisTreePt, int thisDim, int (*compare)(void*,void*) ){
    if( (*thisTreePt)->l[thisDim] != NULL && (*thisTreePt)->r[thisDim] != NULL )
        tree_pushUp( thisTreePt ,&(*thisTreePt)->r[thisDim], thisDim, compare );
    else if( (*thisTreePt)->l[thisDim] == NULL )
        *thisTreePt = (*thisTreePt)->r[thisDim];
    else if( (*thisTreePt)->r[thisDim] == NULL )
        *thisTreePt = (*thisTreePt)->l[thisDim];
}

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

    //tree_maintain( &thisMainTreePt->tree[thisDim], thisDim, thisMainTreePt->compare );
}

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



/*
typedef struct sCoord{
    int x;
    int y;
} Coord;

int comparaX( void* fst, void* snd ){
    if( ((Coord*)fst)->x < ((Coord*)snd)->x )
        return -1;
    else if( ((Coord*)fst)->x > ((Coord*)snd)->x )
        return 1;
    else
        return 0;
}

int comparaY( void* fst, void* snd ){
    if( ((Coord*)fst)->y < ((Coord*)snd)->y )
        return -1;
    else if( ((Coord*)fst)->y > ((Coord*)snd)->y )
        return 1;
    else
        return 0;
}

void print( void *fst, int altura, void* ptr ){
    printf("{%2d,%2d} at %2d with addr %p\n", ((Coord*)fst)->x, ((Coord*)fst)->y, altura, ptr );
}

int main(){
    int (*funcCompara[DIM])(void*,void*) = {comparaX, comparaY};
    void (*funcPrint[DIM])(void*,int,void*) = {print, print};

    MainTreePt arvore = tree_new( funcCompara, funcPrint );

    int i;
    Coord x[20] = {
        {1,11},
        {2,22},
        {3,13},
        {4,24},
        {5,15},
        {6,26},
        {7,17},
        {8,28},
        {9,19},
        {10,10},
        {11,1},
        {12,12},
        {13,13},
        {14,4},
        {15,15},
        {16,16},
        {17,17},
        {18,8},
        {19,19}
    };
    for( i=0; i<20; i++)
        tree_insert( arvore, &x[i] );

    tree_remove( arvore, &x[2] );
    tree_remove( arvore, &x[7] );
    tree_remove( arvore, &x[12] );

    tree_printOrdered(arvore, 0);
    printf("-----\n");
    tree_printOrdered(arvore, 1);

    tree_dispose( &arvore );

    return 0;
}
*/
