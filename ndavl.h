#ifndef NDAVL_H_INCLUDED
#define NDAVL_H_INCLUDED

/******************
 *
 * N-Dimensional AVL
 *
 * ****************/

#define DIM 2

typedef struct sTree{
    void *node;
    struct sTree *l[DIM];
    struct sTree *r[DIM];
    int height[DIM];
} Tree, *TreePt;

typedef struct sMainTree{
    TreePt tree[DIM];
    int (*compare[DIM])(void*,void*);
} MainTree, *MainTreePt;


MainTreePt tree_new( int (*compare[DIM])(void*,void*) );
int tree_insert( MainTreePt thisMainTree, void* node);
TreePt tree_search(MainTreePt thisMainTree, void* node, int thisDim);
void tree_applyToAllOrdered(MainTreePt thisMainTree, int thisDim, void (*func)(void*));
void tree_remove( MainTreePt thisMainTreePt, void* node );
void tree_dispose( MainTreePt *thisMainTree );

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

#endif /* NDAVL_H_INCLUDED */
