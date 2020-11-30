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
//struct newbst, function search, insert, inorder were extracted from the site-
// https://www.geeksforgeeks.org/binary-search-tree-set-1-search-and-insertion/

// some of those functions mentioned had to be modified to be used properly

//create a node if not present
struct bst *newbst(char* item, char* string) { 
    struct bst *temp = (struct bst *) malloc(sizeof(struct bst)); 
    temp -> key = item; 
    temp -> data = string;
    temp -> left = temp -> right = NULL;
    temp -> equals = NULL;
    return temp; 
}


	 


// searching for a node with a given key
struct bst* search(struct bst* root, char* key, int count) {
	
	
    // if root is null
    if (root == NULL){ 
		count++;
		root -> totalComparisons = count;
		
       return root; 
    }
     
    if ((strcmp(root -> key, key) ==0 )) {
    	
    	
		count++;
    	root -> totalComparisons = count;
    	
    	return root;
    }

    	
    //if key is greater than root's key 
    if (strcmp(root->key, key) < 0) { 
    	count++;
		
		return search(root->right, key, count);
    }
   
    // if key is smaller than root's key 
    else{
    	count++;
		
    	return search(root -> left, key, count);
    }
    
}





//function to insert nodes at appropriate positions
struct bst* insert(struct bst* node, char* key, char* string) { 
    //If the tree is empty, return a new node 
    if(node == NULL) {
    	return newbst(key, string);
    }
  
    // if key is smaller than node's key, recur left 
    if(strcmp(node -> key, key) > 0) {
        node -> left = insert(node->left, key, string); 
    }
    // if key is equal than node's key, recur to equals linked list 
    else if(strcmp(node -> key, key) == 0){ 
        node -> equals= insert(node -> equals, key, string); 
    }
    // if key is larger than node's key, recur right 
    else if(strcmp(node -> key, key) < 0){
        node->right = insert(node->right, key, string); 
    }
  
    
    return node; 
}


void printDict(char* string, char* file, char* key) {
	FILE *filePointer;
	filePointer = fopen(file, "a");
	int i;
	//list of all the dictionary items
	char list[NUMBER_OF_ITEMS][MAX_INPUT_LENGTH]={{"VendorID"}, {"passenger_count"}, {"trip_distance"}, 
						{"RatecodeID"},{"store_and_fwd_flag"}, {"PULocationID"}, 
						{"DOLocationID"}, {"payment_type"}, {"fare_amount"},
						{"extra"}, {"mta_tax"}, {"tip_amount"},{"tolls_amount"},
						{"improvement_surcharge"}, {"total_amount"}, {"PUdatetime"}, 
						{"DOdatetime"}, {"trip_duration"}};
	
	
	int count = 0, characterPosition = 0;
	
	fprintf(filePointer, "%s -->", key);
	
	//print each item in the dictionary with their proper values
	for(i = 0; i < NUMBER_OF_ITEMS; i++) {
		//if position of key is found in string, go across and dont print it
		if(count == POSITION_OF_PUDATETIME) {
			count++;
			i++;
			characterPosition += strlen(key) + 1;
		}
		fprintf(filePointer, " %s: ", list[i]);
		
		
		//dont print the commas
		while(characterPosition < strlen(string) ) {
			if(string[characterPosition] == ',') {
				characterPosition ++;
				break;
			}
		
			
			//print the characters till the commas
			fprintf(filePointer, "%c", string[characterPosition]);
			characterPosition ++;
			
		}
		
		
		count++;
		fprintf(filePointer, " ||");
		
		
	}
	fprintf(filePointer, "\n");
	
	fclose(filePointer);
	

	
}

							
//freeing the bst
void freeTree(struct bst *parent) {
    if( !parent) {
        return;
    }
    
    //if parent not null, recursively go through and free everything
    freeTree(parent -> left);
    freeTree(parent -> equals);
    freeTree(parent -> right);
    
        
    free(parent);
    parent=NULL;
  
      
    
}
//scan the datafile and count how many lines are there
int getLines(char* datafile) {
	FILE *filePointer;
	
	filePointer = fopen(datafile, "r");
	int count = 0;
	char data[MAX_INPUT_LENGTH];
	
	
	while(fscanf(filePointer, " %[^\n]s", data)!=EOF) { 
		count++;
	}
	
	fclose(filePointer);
	return count;
}
	
	
//scan the string and just pick out the key
char* getKey(char* string) {
	char *key;
	key = malloc(sizeof(char)*MAX_STRING_LENGTH);
	
	assert(key);
	int count = 0, characterPosition = 0, i;
	//we skip characters and count commas till we reach the key position
	//then retrieve the key
	for(i = 0; i < strlen(string); i++) {
    		
    	if(string[i] == ',') {
    		count++;
   		}
   		if (count == POSITION_OF_PUDATETIME && string[i] != ',') {
   			key[characterPosition++] = string[i];
    			
   		}
   		if(count > POSITION_OF_PUDATETIME) {
   			key[characterPosition] = '\0';
   			break;
    			
    		
    	}
    		
    }

    return key;
}
	
	

int findZone(struct bst *node, int input, char* file) {
	FILE *filePointer;
	filePointer = fopen(file, "a");
	//max size of string of the zone
	char *zone = malloc(sizeof(char) * 4);
	int i, count = 0, characterPosition = 0;
	//get to zone position and retrieve it
	for (i = 0; i < strlen(node -> data); i++) {
    	if(node -> data[i] == ',') {
    		count++;
   		}
   		if(count == POSITION_OF_ZONE && node -> data[i] != ',') {
   			zone[characterPosition++] = node -> data[i];
    			
   		}
   		if(count > POSITION_OF_ZONE) {
   			zone[characterPosition] = '\0';
   			break;
    			
    		
    	}		
    }
    //change string zone to integer and compare with input
    //print the things if found and return 1 which indicates a value found
    if (atoi(zone) == input) {
    	
    	fprintf(filePointer, "%s -->", zone);
    	fprintf(filePointer, " %s\n", node->key);
    	fclose(filePointer);
    	return 1;
    }
    
    //if zone not found	
    fclose(filePointer);
    return 0;
    
    

}
//traverse the tree in ascending order of key and find the zone along the way
int inorder(struct bst *root, int input, char* file, int matches) { 
	
    if (root != NULL) { 
    	//matches indicate how many zones found for the input
        matches = inorder(root -> left, input, file, matches); 
        matches = inorder(root -> equals, input, file, matches);
        matches += findZone(root, input, file);
        matches = inorder(root -> right, input, file, matches); 
    }
    return matches;
 
} 
//function to print notfound in outputfile
void notFound(char* file, int input) {
	FILE *filePointer;
	filePointer = fopen(file, "a");
	fprintf(filePointer, "%d --> NOTFOUND\n", input);
	fclose(filePointer);
}
	