// This program reads in lines from standard input, processes the lines to separate
// artist names separated by commas, inputs all of the pairs in a line into a tree,
// and outputs any pairs that appear in at least 50 lines
//
// By Aleksandra Zakrzewska


#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "tree.h"



int main(int argc, char * argv[]) {
  
  Tree aTree=NULL; // initialize a tree in which artist names will be stored
  
  //for every artist in line, create one string-- add characters to artist name until
  //a comma, newline or EOF is reached, or if a name is over 30 chars long
  char c=getchar();
  while (c!= EOF) {
    char ** line = malloc (sizeof(char **) *50); // array of strings for artist names
    int k=0;
    
    //loop to read all names of artists (<=50) into an array of strings
    while (k<50) {
      char * artist = malloc (31); //initialize strings for names
      int i=0;
      //build string of name while c is not a comma, new line or EOF, or name is
      //over 30 characters
      while (i<30 && c != ',' && c!= EOF && c!= '\n') {
        artist[i] = c;
        i++;
        c=getchar();
      }
      if(i==30) { // if name is over 30 char, get characters until the end of the name
        while(c!= ','&& c !=EOF && c!='\n') {
          c=getchar();
        }
      }
      artist[i]= '\0'; // null terminate the name
      line[k] = artist;
      if (c== EOF || c == '\n'){ // stop reading characters if at end of a line or file
        c=getchar();
        break;
      }
      c=getchar();
      k++;
    }
    
    int j=0;
    //double loop through array of names to input all pairs into the tree
    while(j<k && line[j]!=NULL) {
      int h=0;
      while(h<k && line[h]!=NULL) {
        //to avoid duplicates, only input pairs where the first name in the pair is
        //less than the second
        if (strncmp(line[j], line[h], strlen(line[j])) <0) {
          aTree =insertAT (aTree, line[j],line[h]); // insert the pair into the tree
        }
        h++;
      }
      j++;
    }
    for (int h=0;h<=k;h++) {  //free the array of names from this line
      free(line[h]);
    }
    free(line);
  }
  
  aTree= destroyT (aTree); // free memory by destroying the tree
  
  
  
}

