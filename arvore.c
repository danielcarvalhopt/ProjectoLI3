#include <stdlib.h>
#include <stdio.h>

#define DIM 2

typedef struct sTree{
    void *node;
    struct sTree *l[DIM];
    struct sTree *r[DIM];
    int height; // HEIGHT
} Tree, *TreePt;

typedef struct sMainTree{
    TreePt tree[DIM];
    int nodes;
    int (*compare[DIM])(void*,void*);
    void (*print[DIM])(void*,int);
} MainTree, *MainTreePt;

int maxInt(int a, int b){
    return a>=b ? a : b;
}

int tree_getHeight(TreePt tree){
    return tree!=NULL ? tree->height : 0;
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

MainTreePt tree_new( int (*compare[DIM])(void*,void*), void (*print[DIM])(void*,int)){
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
    int i, sucesso=1;
    for( i=0; i<DIM && sucesso == 1; i++)
        sucesso = (tree_search(thisMainTree, node, i) == NULL ? 1 : 0);

    for( i=0; i<DIM && sucesso == 1; i++)
        sucesso = tree_insertRec( &thisMainTree->tree[i], node, i, thisMainTree->compare[i]);

    return sucesso; // 1 - inseriu em todos; 0 - já existe
}

int tree_insertRec( TreePt *thisTree, void* node, int thisDim, int (*compare)(void*,void*)){
    int i, cmp, ret=1;
    if( *thisTree == NULL ){
        *thisTree = (TreePt)malloc(sizeof(Tree));
        (*thisTree)->node = node;
        for(i=0; i<DIM; i++){
            (*thisTree)->l[i] = NULL;
            (*thisTree)->r[i] = NULL;
        }
    }else{
        cmp = compare((*thisTree)->node, node);
        if( cmp < 0 ) // existente é menor que o que se quer inserir -> inserir à direita
            ret = tree_insertRec( &(*thisTree)->r[thisDim], node, thisDim, compare );
        else if( cmp > 0 ) // existente é maior que o que se quer inserir -> inserir à esquerda
            ret = tree_insertRec( &(*thisTree)->l[thisDim], node, thisDim, compare );
    }

    (*thisTree)->height = maxInt( tree_getHeight( (*thisTree)->r[thisDim]), tree_getHeight((*thisTree)->l[thisDim]) ) +1;
    
    return ret;
}

void tree_printOrderedRec( TreePt thisTree, void (*print)(void*,int), int thisDim ){
    if( thisTree != NULL ){
        tree_printOrderedRec( thisTree->l[thisDim], print, thisDim);
        print(thisTree->node, thisTree->height);
        tree_printOrderedRec( thisTree->r[thisDim], print, thisDim);
    }
}

void tree_printOrdered(MainTreePt thisMainTree, int thisDim){
    if( thisMainTree != NULL )
        tree_printOrderedRec( thisMainTree->tree[thisDim], thisMainTree->print[thisDim], thisDim );
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

void print( void *fst, int altura ){
    printf("{%d,%d} at %d\n", ((Coord*)fst)->x, ((Coord*)fst)->y, altura );
}

int main(){
    int (*funcCompara[DIM])(void*,void*) = {comparaX, comparaY};
    void (*funcPrint[DIM])(void*,int) = {print, print};
    
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
