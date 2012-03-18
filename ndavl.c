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
        }
        sucesso = 1;
    }

    for( i=0; i<DIM && sucesso == 1; i++)
        tree_insertRec( &thisMainTree->tree[i], thisTreePt, node, i, thisMainTree->compare[i]);

    return sucesso; // 1 - inseriu em todos; 0 - já existe
}

int tree_insertRec( TreePt *thisTree, TreePt allocd, void* node, int thisDim, int (*compare)(void*,void*)){
    int i, cmp, ret=1;
    if( *thisTree == NULL )
        *thisTree = allocd;
    else{
        cmp = compare((*thisTree)->node, node);
        if( cmp < 0 ) // existente é menor que o que se quer inserir -> inserir à direita
            ret = tree_insertRec( &(*thisTree)->r[thisDim], allocd, node, thisDim, compare );
        else if( cmp > 0 ){ // existente é maior que o que se quer inserir -> inserir à esquerda
            ret = tree_insertRec( &(*thisTree)->l[thisDim], allocd, node, thisDim, compare );
            //if( tree_getHeight( &(*thisTree)->l[thisDim] ) - Height( T->Right ) == 2 )
            //    if( X < T->Left->Element )
            //        T = SingleRotateWithLeft( T );
            //    else
            //        T = DoubleRotateWithLeft( T );
        }
    }

    (*thisTree)->height[thisDim] = maxInt( tree_getHeight( (*thisTree)->r[thisDim], thisDim), tree_getHeight((*thisTree)->l[thisDim], thisDim) ) + 1;

    return ret;
}

void tree_printOrderedRec( TreePt thisTree, void (*print)(void*,int,void*), int thisDim ){
    if( thisTree != NULL ){
        tree_printOrderedRec( thisTree->l[thisDim], print, thisDim);
        print(thisTree->node, thisTree->height[thisDim], thisTree);
        tree_printOrderedRec( thisTree->r[thisDim], print, thisDim);
    }
}

void tree_printOrdered(MainTreePt thisMainTree, int thisDim){
    if( thisMainTree != NULL )
        tree_printOrderedRec( thisMainTree->tree[thisDim], thisMainTree->print[thisDim], thisDim );
}
/*
TreePt tree_singleRotateWithLeftChild( TreePt thisTreePt, int thisDim ){
    TreePt aux;
    aux = thisTreePt->l[thisDim];
    thisTreePt->l[thisDim] = aux->r[thisDim];
    aux->r[thisDim] = thisTreePt;
    thisTreePt->height = maxInt( tree_getHeight( thisTreePt->l[thisDim] ), tree_getHeight( thisTreePt->r[thisDim] )) + 1;
    aux->height = maxInt( tree_getHeight( aux->l[thisDim] ), thisTreePt->height ) + 1;
    return aux;
}

TreePt tree_singleRotateWithRightChild( TreePt thisTreePt, int thisDim ){
    TreePt aux;
    aux = thisTreePt->r[thisDim];
    thisTreePt->l[thisDim] = aux->r[thisDim];
    aux->r[thisDim] = thisTreePt;
    thisTreePt->height = maxInt( tree_getHeight( thisTreePt->l[thisDim] ), tree_getHeight( thisTreePt->l[thisDim] )) + 1;
    aux->height = maxInt( tree_getHeight( aux->l[thisDim] ), thisTreePt->height ) + 1;
    return aux;
}
*/


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
