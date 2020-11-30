//Coded by Md.Fahmi Islam. mdfahmii@student.unimelb.edu.au. id - 961935;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include "bst.h"

#define MAX_INPUT_LENGTH 256
#define MAX_STRING_LENGTH 128
#define SIZE_OF_PUDATETIME 19
#define NUMBER_OF_ITEMS 18
#define POSITION_OF_PUDATETIME 15
#define POSITION_OF_ZONE 5

struct bst {
    struct bst *left;
    struct bst *right;
    struct bst *equals;
    char  *data;
    char *key;
    int totalComparisons;
    
};

//going to create a BST by scanning a file, then take input and search all
//nodes for that value and print the keys to a different file.

int main(int argc, char **argv) { 
	
	int i, matches = 0;
	int input;
	
    struct bst *root = NULL; 
    char *files = argv[1];
    FILE *readFilePointer, *writeFilePointer;
    readFilePointer = fopen(files, "r");
    char *outputfile = argv[2];
    writeFilePointer = fopen(outputfile, "w");
    
    //get the total input lines in the file and make 2 pointers to arrays of the 
    //appropriate rows
    int lines = getLines(files);
   
   
    //store the whole string from file and into data and collect the key from
    //data and store it in keys
    //then create the binary search tree
    char *data[lines];
    char *key[lines];
    for (i = 0; i < lines; i++) {
    	data[i] = malloc(sizeof(char) * MAX_INPUT_LENGTH);
    	assert(data[i]);
    	
    	fscanf(readFilePointer, " %[^\n]s", data[i]);
    	
    	key[i] = getKey(data[i]);
    	root = insert(root, key[i], data[i]);
    }
    
    
    	
    
    
 
    
   //scan keyfile and traverse tree in ascending key order looking for input
    while(scanf("%d", &input) == 1) {
    	
    	
    	matches = 0;
    	matches = inorder(root, input, outputfile, matches);
    	//if none found for a particular input, print notfound
    	if(matches == 0) {
    		notFound(outputfile, input);
    	}
    	printf("%d --> %d\n", input, lines);
		
    	
    }
    
   
    //free data and close files
    for(i = 0; i < lines; i++) {
    	free(key[i]);
    	free(data[i]);
    }
    
    fclose(readFilePointer);
    fclose(writeFilePointer);
    readFilePointer = writeFilePointer = NULL;
    freeTree(root);
    root = NULL;
    
   
    return 0; 
} 



