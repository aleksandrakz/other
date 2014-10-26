//
//  bst.h
//  
//
//  Created by Aleksandra Zakrzewska on 10/13/14.
//
//

//#ifndef _bst_h
//#define _bst_h

#include <stdio.h>

/*// Tree data structure
typedef struct node *Tree;

// Return an empty tree
Tree createT (void);

// Destroy tree T; return NULL
Tree destroyT (Tree t);

// Insert string S in T; return the modified T
Tree insertT (Tree t, char *s);

// Delete string K from T (if it exists) and return modified tree
Tree deleteT (Tree t, char *k);

// Print keys in T in preorder, one per line
void preorderT (Tree t);

// Print keys in T in inorder, one per line
void inorderT (Tree t);

// Return number of nodes in T
int sizeT (Tree t);

// Return height of T
int heightT (Tree t);

// Return internal path length of T
int iplT (Tree t);

// Placeholder
void setBF (int bf);

#endif
 
 */



typedef struct node * Tree;

// Tree data structure

Tree createT (void);
//static Tree makeSubNode (char *s);
//static Tree makeTopNode (char *a, char *b) ;
Tree leftRot (Tree t) ;
Tree rightRot (Tree t) ;
Tree insertBT (Tree t, char *a, char *b) ;
Tree insertAT (Tree t, char *a, char *b) ;
Tree LRRot( Tree t);
Tree RLRot (Tree t);
Tree destroyT (Tree t);
void preorderT(Tree t);

void inorderT (Tree t) ;
