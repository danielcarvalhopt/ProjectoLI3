#include <stdlib.h>
#include <stdio.h>
#include "ndavl.h"
#include "utils.h"

int maxInt(int a,int b){
    return a>=b ? a : b;
}

int tree_getHeight(TreePt tree, int thisDim){
    return tree!=NULL ? tree->height[thisDim] : 0;
}

TreePt tree_searchRec(TreePt thisTreePt, void* node, int thisDim, int (*compare)(void*,void*)){
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

MainTreePt tree_new( int (*compare[DIM])(void*,void*), void (*print[DIM])(void*,int,void*)){
    int i;
    MainTreePt new;
    if( (new = (MainTreePt) malloc( sizeof(MainTree))) != NULL ){
        new->nodes = 0;
        for( i=0; i<DIM; i++){
            new->compare[i] = compare[i];
            new->print[i] = print[i];
            new->tree[i] = NULL;
        }
    }
    return new;
}

int tree_insert( MainTreePt thisMainTree, void* node){
    int i, sucesso = 0;
    TreePt thisTreePt = NULL;
    for( i=0; i<DIM && thisTreePt == NULL; i++)
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

int tree_insertRec( TreePt *thisTree, TreePt allocd, void* node, int thisDim, int (*compare)(void*,void*)){
    int i, cmp, ret=1;
    if( *thisTree == NULL )
        *thisTree = allocd;
    else{
        if( compare((*thisTree)->node, node) < 0 ){ // existente é menor que o que se quer inserir -> inserir à direita
            ret = tree_insertRec( &(*thisTree)->r[thisDim], allocd, node, thisDim, compare );
        }else{                                      // existente é maior que o que se quer inserir -> inserir à esquerda
            ret = tree_insertRec( &(*thisTree)->l[thisDim], allocd, node, thisDim, compare );
        }
    }

    tree_maintain( thisTree, thisDim, compare );

    return ret;
}

void tree_maintain( TreePt *thisTree, int thisDim, int (*compare)(void*,void*) ){
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
    
    


                                                            /* actualizar altura do nó */
}

void tree_printOrderedRec( TreePt thisTree, void (*print)(void*,int,void*), int thisDim ){
    if( thisTree != NULL ){
        printf("LEFT -> ");
        tree_printOrderedRec( thisTree->l[thisDim], print, thisDim);
        printf("THIS -> ");
        print(thisTree->node, thisTree->height[thisDim], thisTree);
        printf("RIGHT -> ");
        tree_printOrderedRec( thisTree->r[thisDim], print, thisDim);
    }else
        printf("NULL\n");
}

void tree_printOrdered(MainTreePt thisMainTree, int thisDim){
    if( thisMainTree != NULL )
        tree_printOrderedRec( thisMainTree->tree[thisDim], thisMainTree->print[thisDim], thisDim );
}

void tree_singleRotateLeft( TreePt *thisTreePt, int thisDim ){
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

void tree_singleRotateRight( TreePt *thisTreePt, int thisDim ){
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

void tree_doubleRotateRightLeft( TreePt *thisTreePt, int thisDim ){
    tree_singleRotateRight( &(*thisTreePt)->r[thisDim], thisDim );
    tree_singleRotateLeft( thisTreePt, thisDim );
}

void tree_doubleRotateLeftRight( TreePt *thisTreePt, int thisDim ){
    tree_singleRotateLeft( &(*thisTreePt)->l[thisDim], thisDim );
    tree_singleRotateRight( thisTreePt, thisDim);
}

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
    Coord x[8] = { {6,1}, {4,10}, {8,3}, {9,4}, {3,5}, {4,6}, {2,1}, {7,2} };
    for( i=0; i<8; i++)
        tree_insert( arvore, &x[i] );
    tree_printOrdered(arvore, 0);
    printf("-----\n");
    tree_printOrdered(arvore, 1);

    return 0;
}
