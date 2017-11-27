/**
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#include "dictionary.h"

// defining offset value to get word index
#define OFFSET 'a'
// defining \' 
#define OFFSET1 26

// trie structure
typedef struct _node
{
    bool is_word;
    struct _node *children[27];
}
node;

// int to count word
int word_count = 0;
    
// root pointer to the trie
node *root = NULL;

// current pointer to node
node *current = NULL;

/**
 * Function to free trienode
 */
void free_node(node *trie)
{
    // looping through each children element
    for(int i = 0; i < 27; i++)
    {
        // checking if null
        if(trie->children[i] != NULL)
        {
            // recursive call
            free_node(trie->children[i]);
        }
    }
    
    // free trie
    free(trie);
    
    return;
}

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    // getting trie pointer
    current = root;
    
    // getting characters of word
    int i = 0;
    while(word[i] != '\0') 
    {
        if(isalpha(word[i]))
        {
            int index = (int)tolower(word[i]) - OFFSET;
            
            // checking if node is not null
            if(current->children[index] == NULL)
            {
                return false;
            }
            else
            {
                current = current->children[index];
                i++;
            }
        }
        else if(word[i] == '\'' && i > 0)
        {
            // checking if node exists
            if(current->children[OFFSET1] == NULL)
            {
                return false;
            }
            else
            {
                current = current->children[OFFSET1];
                i++;
            }
        }
    }
    
    // checking if it is a word
    if(current->is_word == false)
    {
        return false;
    }
    
    // return true if all cases are passed
    return true;
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    // open dictionary
    FILE *file = fopen(dictionary, "r");
    // checking if dictionay is actually opened
    if(file == NULL)
    {
        return false;
    }
    
    // mallocing root
    root = (node*)malloc(sizeof(node));
    // checking
    if(root == NULL)
    {
        return false; 
    }
    // setting bool variable as false
    root->is_word = false;
    // setting children elements as null
    for(int i = 0; i < 27; i++)
    {
        root->children[i] = NULL;
    }
    
    // current position in children array
    int character = 0;
    // looping through dictionary until EOF
    while(EOF != (character = fgetc(file)))
    {
        // assigning current to root
        current = root;
        
        // iterating through character and adding each letter to children until "\n"
        for(; character != '\n'; character = fgetc(file))
        {
            // creating index
            int index = 0;
            
            if(isalpha(character))
            {
                index = character - OFFSET;
            }
            else if(character == '\'')
            {
                index = OFFSET1;
            }
        
            // if node doesn't exist create one
            if(current->children[index] == NULL)
            {
                node *new_node = (node*)malloc(sizeof(node));
                if(new_node == NULL)
                {
                    return false;
                }
             
                // setting bool as false
                new_node->is_word = false;
                // setting all elements of children as null
                for(int i = 0; i < 27; i++)
                {
                    new_node->children[i] = NULL;
                }
            
                current->children[index] = new_node;
                current = current->children[index];
            }
            else
            {
                current = current->children[index];
            }
        }
        
        // adding as a word in structure
        current->is_word = true;
        word_count++;
    }
    
    // close open file
    fclose(file);
    
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return word_count;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    // assigning current to root
    current = root;
    
    // freeing node
    free_node(current);
    
    return true;
}
