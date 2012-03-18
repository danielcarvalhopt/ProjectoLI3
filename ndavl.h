#ifndef NDAVL_H_INCLUDED
#define NDAVL_H_INCLUDED

/******************
 *
 * N-Dimensional AVL
 *
 * ****************/

#define DIM 2

typedef struct sTree;
    void *node;
    struct sTree *l[DIM];
    struct sTree *r[DIM];
    int height; // HEIGHT
} Tree, *TreePt;

typedef struct sMainTree;
    TreePt tree[DIM];
    int nodes;
    int (*compare[DIM])(void*,void*);
    void (*print[DIM])(void*,int);
} MainTree, *MainTreePt;


int tree_getHeight(TreePt tree);
TreePt tree_searchRec(TreePt thisTreePt, void* node, int thisDim, int (*compare)(void*,void*));
TreePt tree_search(MainTreePt thisMainTree, void* node, int thisDim);
MainTreePt tree_new( int (*compare[DIM])(void*,void*), void (*print[DIM])(void*,int));
int tree_insert( MainTreePt thisMainTree, void* node);
int tree_insertRec( TreePt *thisTree, void* node, int thisDim, int (*compare)(void*,void*));
void tree_printOrderedRec( TreePt thisTree, void (*print)(void*,int), int thisDim );
void tree_printOrdered(MainTreePt thisMainTree, int thisDim);

#endif /* NDAVL_H_INCLUDED */
