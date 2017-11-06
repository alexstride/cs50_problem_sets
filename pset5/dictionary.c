/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include "dictionary.h"
#include <stdlib.h>
#include <string.h>

/**
 * Returns true if word is in dictionary else false.
 */

typedef struct node
{
    char word[LENGTH+1];
    node* next;
}node;

bool check(const char* word)
{
    int compVal;
    node* cursor;
    int wordLength = strlen(word);
    
    char* word_buffer = malloc(wordLength+1);
    for(int i = 0; i<wordLength; i++)
    {
        *(word_buffer+i) = toupper(*(word+i)); // Probably wrong
    }
    *(word_buffer+wordLength) = '\0';
    
    //go the appropriate hash entry with cursor
    cursor = hashtable[hashFunction(word_buffer)];
    
    //loop while cursor is not a NULL pointer
    while (cursor!=NULL)
    {
        compVal = strcmp(word_buffer, cursor->word);
        if(compVal==0)
        {
            free(word_buffer);
            return true;
        }
        else if(compVal<0){break;}
        else
        {
            cursor = cursor->next;
        }
    }
    free(word_buffer);
    return false;
    
}

//************ Definitions inherent to the loading of a dictionary through a hashtable
//declare definition of a node and a hashtable to be used in the load function


//A hash function for use in the hash table

int hashFunction(char* word)
{
    //set index pointer to the beginning of the word
    char* index = word;
    
    //set incrementor to zero
    int incrementor = 0;
    
    //loop throught the word until null stop and add lowercase values (-97) together
    while (*index!='\0')
    {
        incrementor = incrementor + tolower(*index);
        index++;
    }
    
    //return the answer modulo 100
    return incrementor%100;
}

//A hashtable, which is an array of pointers to nodes

node* hashtable[100];
void init_hashtable(void)
{
    for(int i=0; i<100; i++)
    {
        hashtable[i]=NULL;
    }
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    //Open the dictionary file
    FILE* f = fopen(dictionary, "r");
    if(f==NULL)
    {
        return false;
    }
    
    //initialize the hashtable with NULL values
    init_hashtable();
    
    node** cursor = NULL;
    
    //While there has been no end of file, scans a word at a time from the file and inserts it
    while(!feof(f))
    {
        node* new_node = malloc(sizeof(node));
        char buffer[LENGTH+1];
        fscanf(f,"%s", buffer);
        int len = strlen(buffer);
        int charBuffer;
        for (int i=0; i<len; i++)
        {
            charBuffer = buffer[i];
            new_node->word[i] = toupper(charBuffer);
        }
        new_node->word[len] = '\0';
        
        //initialize the next pointer to NULL
        
        new_node->next = NULL;
        //Find hashtable entry
        int hash_entry = hashFunction(new_node->word);
        
        //initialize a cursor and set it to point at the appropriate point in the hash array
        cursor = malloc(sizeof(node*));
        cursor = &hashtable[hash_entry];
        
        //loop while the cursor is not pointing to the final element in the linked list and the next word is not alphabetically greater
        while(((*cursor)!=NULL) && (strcmp( ((*cursor) -> word), (new_node->word) ) < 0))
        {
            //move along the linked list
            cursor = &((**cursor).next);
        }
        //insert the node between what the cursor is pointing to and what the cursor is pointing to is pointing to
        new_node->next = *cursor;
        *cursor = new_node;
        //free(cursor);
    }
    return true;
    free(cursor);
}


//Now a function to use to give a visual representation of a hash table structure
void testHashTable(node* array[])
{
    //Print intro
    printf("\n\nInitializing visualization of hashtable\n\n");
    for(int i = 0; i<100; i++)
    {
        //print out the hash value followed by comma space
        printf("%i: ",i);
        
        //set ptr to first node
        node* ptr = hashtable[i];
        
        //while ptr not NULL
        while(ptr!=NULL)
        {  
            //print next word
            printf(">%s< ",(ptr->word));
            
            //move ptr along
            ptr = ptr->next;
        }
        //print newline
        printf("\n");
    }
    printf("\n\n");
}


//************************************ END OF LOADING SECTION****************************************

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    
    //init counter
    int counter = 0;
    
    for(int i = 0; i<100; i++)
    {
        //set ptr to first node
        node* ptr = hashtable[i];
        
        //while ptr not NULL
        while(ptr!=NULL)
        {  
            //print next word
            counter++;
            
            //move ptr along
            ptr = ptr->next;
        }
    }
    return counter;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */


//a recursive function to free a linked list 
void listRelease(node* ptr)
{
    if (ptr!=NULL)
    {
        listRelease(ptr->next);
        free(ptr);
    }
}

bool unload(void)
{
    //looping through the hash table, recursivelky freeing each linked list
    for (int i = 0; i<100; i++)
    {
        listRelease(hashtable[i]);
    }
    return true;
}


