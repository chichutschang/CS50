/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 * Chi-Chu Tschang
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>
#include <stdio.h>
#include "dictionary.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

//establishes root node of trie
node* root = NULL;

//initialize 'ch' as characters
unsigned int ch;   
    
//sets word count to 0
unsigned int count = 0;

//allows recursion
void clear(node* temp);

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{

int length = strlen(word);

//points to current node as program goes through trie
node* temp = root;

//iterate over word    
for (int i = 0; i < length; i++)
    {
        //checks each letter of word in dictionary
        ch = tolower(word[i]);              
                
        //checks if character is apostrophe
        if (ch == '\'')
        {   
            //alphabet size = 26; ASCII offset = 97
            ch = 26 + 97;
        }
            
        //sets position of letter in character
        int letter = ch - 97;

        //gets address of the next node in the trie
        struct node* nextNode = temp -> children[letter];
                
        //checks corresponding element in children. if NULL, word is misspelled
        if(nextNode == NULL)
        {
            return false;
        }
        else
        {
            temp = nextNode;
        }          
    }
    
    //checks corresponding element in children, if not NULL, move to next letter                
    if (temp -> is_word == true)
        {
            return true;
        }
                 
    return false;     
}    
/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */

bool load(const char* dictionary)
{
    //opens dictionary
    FILE* fp = fopen(dictionary, "r");
    
    //checks if there is anything in dictionary
    if (fp == NULL)
    {   
        return 0;
    }

    //initialize first trie    
    root = calloc(1, sizeof(node));
    
    //initialize temp as a node
    node* temp = root;        
    
    //reads each character in the file
    for(ch = fgetc(fp); ch != EOF; ch = fgetc(fp))
        {

        //counts # of words in file by checking '\n'
        if (ch == '\n')
            {
                    count++;
                    temp -> is_word = true;
                    temp = root;
            }       
                    
        else
            {
                //checks for apostrophe
                if (ch =='\'')
                {    
                    //alphabet size = 26; ASCII offset = 97
                    ch = 26 + 97;  
                }    
            
                //sets position of letter in character
                int letter = tolower(ch) - 97;
               
                //gets address of the next node in the trie
                struct node* nextNode = temp -> children[letter];
                                 
                //if node is NULL, malloc a new node
                if (nextNode == NULL)
                {   
                    //allocate space if there is no space
                    temp -> children[letter] = calloc(1, sizeof(node));                
                        
                    temp = temp -> children[letter];
                }
                //if node is not NULL, move to new node and continue
                else 
                {
                    temp = nextNode;
                } 
            }
        }
                       
    //close file                                      
    fclose(fp);
    
    //return true if successful
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
        return count;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
 
void clear(node* temp)
{
    for (int i=0; i < 27; i++)
    {
        if ( temp -> children[i] != NULL)
        {
            clear(temp -> children[i]);
        }
    }
    free(temp);
} 
bool unload(void)
{
    clear(root);
    
    //return true if successful
    return true;
        
}

