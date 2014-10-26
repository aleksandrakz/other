#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tree.h"
#include <math.h>


//This includes all functions associated with the tree data structure used, including, insertion, balancing
//and destroying the tree

// Tree data structure
struct node {
  char *Key;          // Key stored at node
  Tree L, R;          // left & right children
  Tree sub;           // tree containing pairs
  int height;         //height for balancing
  int Count;          //counts number of pairs (for subtree only)
} Node;


Tree createT (void) {
  Tree T=NULL;
  return T;
}

//makeSubNode makes a new node in the subtree of an artist. It saves the artist name as the key,
//and initiates all the other tree pointers to NULL, count to 1 and height to 0 (because no children)
static Tree makeSubNode (char *s) {
  Tree t = malloc (sizeof(*t));
  t->Key = strdup(s);
  t->L = NULL;
  t->R = NULL;
  t->height=0;
  t->Count =1;
  t->sub=NULL;
  return t;
}

//makeTopNode makes a new node in the subtree of an artist. It saves the artist name as the key,
//and initiates all the other tree pointers to NULL, count to 0 (because it doesn't matter for the
//first in the pair and height to 0 (because no children yet)
static Tree makeTopNode (char *a, char *b) {
  Tree t = malloc (sizeof(*t));
  t->Key = strdup(a);
  t->L = NULL;
  t->R = NULL;
  t->height=0;
  t->sub=(makeSubNode(b));
  t->Count =0;
  return t;
}



//setHeight sets the height of the node to 1 + the height of the child with the larger height
//it makes sure to not call for the height of a nonexistant child
Tree setHeight (Tree t) {
  if (t->L != NULL && t->R !=NULL) {  //only call for the height of both children if both not null
    if ( ((t->L)->height) > ((t->R)->height) ) { //set to 1+ the higher height
      t->height = 1+ (t->L)->height;
    }
    else {
      t->height = 1+ (t->R)->height;
    }
  }
  else if (t->L != NULL) {            //if right child = NULL, but not left, set to 1 + height of left
    t->height = (1+ (t->L)->height);
  }
  else if (t->R != NULL) {          //if left child = NULL, but not right, set to 1 + height of right
    t->height = (1+ (t->R)->height);
  }
  else {
    t->height =0;                 //if both children are NULL, the height is zero
  }
  return t;
}

//checkHeight returns the height of a tree, checking first that the tree is not null. If it is NULL, height
//is returned as -1, so that the height of its parent can be 0
int checkHeight (Tree t) {
  if (t != NULL) {
    return t->height;
  }
  else {
    return -1;
  }
}


//leftRot takes a Tree t, and performs a left rotation by setting the right
//child of the root as the new parent, the root as its left child, and the left
//child of the left child as the right child of the old root. It returns the
//modified tree
Tree leftRot (Tree t) {
  if (t->R ==NULL)
    return t;
  Tree parent = t->R;
  t->R = parent->L;
  setHeight(t);
  parent->L= t;
  setHeight(parent);
  return parent;
}


//rightRot takes a Tree t, and performs a right rotation by setting the left
//child of the root as the new parent, the root as its right child, and the
// right child of the right child as the left child of the old root. It returns
//the modified tree
Tree rightRot (Tree t) {
  if (t->L ==NULL)
    return t;
  Tree parent = t->L;
  t->L = parent->R;
  setHeight(t);
  parent->R= t;
  setHeight(parent);
  return parent;
}

//RLRot performs a right left rotation by calling rightRot on the right child of t
//and then calling a leftRot on t
Tree RLRot (Tree t) {
  t->R = rightRot(t->R);
  t= leftRot(t);
  return t;
}

//LRRot performs a left right rotation by calling leftRot on the left child of t
//and then calling a rightRot on t
Tree LRRot (Tree t) {
  t->L = leftRot(t->L);
  t= rightRot(t);
  return t;
}

//rotateT checks to see if the tree is balanced and, if not, calls the appropriate rotation, then
//returns the modified tree
Tree rotateT(Tree t) {
  if (checkHeight(t->L) > 1+ (checkHeight(t->R))) {                                //if tree is left heavy
    if (t->L != NULL && checkHeight((t->L)->R) > 1 + (checkHeight ((t->L)->L))) {  //and left child is right heavy
      t=LRRot(t);                                                                   //call a LR rotation
      return t;
    }
    else {             //if t is left heavy and its left child is balanced or left heavy
      t=rightRot(t);    //call a right rotation
      return t;
    }
  }
  else if (checkHeight(t->R) > 1+ (checkHeight(t->L))) {                          //if tree is right heavy
    if (t->R != NULL && checkHeight((t->R)->L) > 1 + (checkHeight ((t->R)->R))) {  //and right child is left heavy
      t=RLRot(t);                                                                  //call a RL rotation
      return t;
    }
    else {            //if t is right heavy and its right child is balanced or right heavy
      t=leftRot(t);    //call a left rotation
      return t;
    }
  }
  else {
    
    return t;
  }
}


//insertBT takes inserts string b into Tree t, but if the string is already there
//increments the Count. It then updates the height and calls rotateT to check
//if a rotation would improve the balance after the new insertion
//if the Count reaches 50, it prints the pair a, b
Tree insertBT (Tree t, char *a, char *b) {
  if (t == NULL) {
    return makeSubNode (b);     //create a new node when end is reached
  }
  else if (strcmp (b, t->Key) < 0) {  //search Left child if smaller
    
    t->L = insertBT (t->L, a, b);
    setHeight(t);
  }
  else if (strcmp (b, t->Key) > 0) {  // search Right child if larger
    t->R = insertBT (t->R, a, b);
    setHeight(t);
  }
  else {
    t->Count++;           //incremement count if found and print if ==50
    if( t->Count == 50) {
      printf("%s, %s\n", a, b);
    };
    
    
  }
  t=rotateT(t);      //check if rotations necessary
  return t;
}

//insertAT takes inserts string a into Tree t, and then inserts b into its subtree
//by calling insertBT. It then updates the height and calls rotateT to check
//if a rotation would improve the balance after the new insertion
Tree insertAT (Tree t, char *a, char *b) {
  if (t == NULL) {
    Tree A= makeTopNode (a, b);     //create a new node when end is reached
    return A;
  }
  else if (strcmp (a, t->Key) < 0) {  //search Left child if smaller
    
    t->L = insertAT (t->L, a, b);
    setHeight(t);
  }
  else if (strcmp (a, t->Key) > 0) {  // search Right child if larger
    
    t->R = insertAT (t->R, a, b);
    setHeight(t);
  }
  else {
    
    t->sub = insertBT(t->sub, a, b); //insert b
  }
  t=rotateT(t);      //check if rotations necessary
  return t;
}


// Destroy tree T, by freeing each element and destroying all subtrees
//return NULL
Tree destroyT (Tree t) {
  if (t == NULL)
    return NULL;
  t->L = destroyT (t->L);
  t->R = destroyT (t->R);
  t->sub = destroyT(t->sub);
  free (t->Key);
  free (t);
  return NULL;
}

