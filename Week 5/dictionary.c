/**
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

#include "dictionary.h"


/**
 * Returns true if word is in dictionary else false.
 */
 
bool check(const char *word)
{
   int children_position=0;
    node *temp=root;
   
   //move through trie for each letter
   //if \0 is hit and is_word is true-->return true, otherwise false
   //if children[children_position] points to NULL, return false
   //otherwise move through trie
   
    for (int pointer_position=0; pointer_position<46; pointer_position++)
    {
       if (word[pointer_position]=='\0')
       {
           if (temp ->is_word==true)
           {
               return true;
           }
           else
           {
               return false;
           }
       }
       if (word[pointer_position]=='\'')
       {
           children_position =26;
           if (temp->children[children_position]==NULL)
           {
               return false;
           }
           else
           {
               temp = temp ->children[children_position];
           }
      } 
       if (islower(word[pointer_position]))
       {
           children_position =word[pointer_position]-97;
           if (temp->children[children_position]==NULL)
           {
               return false;
           }
           else
           {
               temp = temp ->children[children_position];
           }
      }      
       
       if (isupper(word[pointer_position]))
       {
           children_position =word[pointer_position]- 65;
           if (temp->children[children_position]==NULL)
           {
               return false;
           }
           else
           {
               temp = temp ->children[children_position];
           }
      }        
        
    }
    return false;
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
 
    // create root for trie
    //set all children to NULL
    root = malloc(sizeof(node));
    for (int leaves=0; leaves<27; leaves++)
    {
        root ->children[leaves] = NULL;
    }
 node *temp=root;    
 
 int children_position=0;
 char * letter = malloc(1);
 
 //open file 
  FILE *inptr = fopen(dictionary, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", dictionary);
        return false;
    }
   
   //find size of file
   
    fseek(inptr, 0L, SEEK_END);
    int size_of_file = ftell(inptr);
    fseek(inptr, 0L, SEEK_SET);
    
    //loop through dictionary starts here
    
for (int pointer_position=0; pointer_position<size_of_file; pointer_position++)
{
    
    //read dictionary one char at the time
    fread(letter,1,1,inptr);
   
     //if end of word 
    if (*letter=='\n')
    {
         temp->is_word =true;
         
         word_counter++;
         temp=root;
    }
    
    //if letter is '\'' 
     if (*letter=='\'')
    {
          children_position = 26;
          if (temp->children[children_position]==NULL)
          {
            node * newnode;
            newnode = malloc(sizeof(node));
            temp->children[children_position] = newnode;
            for (int leaves=0; leaves<27; leaves++)
            {
                newnode ->children[leaves] = NULL;
            }
            newnode->is_word=false;
          }
       temp = temp ->children[children_position];
    }

    //if letter is an lower case character
   if (islower(*letter))
    {
         children_position = *letter -97;
         
          if (temp->children[children_position]==NULL)
          {
            node * newnode;
            newnode = malloc(sizeof(node));
            temp->children[children_position] = newnode;
            for (int leaves=0; leaves<27; leaves++)
            {
                newnode ->children[leaves] = NULL;
            }
            newnode->is_word=false;
          }
       temp = temp ->children[children_position];

    }

    //if letter is a upper case character
     if (isupper(*letter))
    {
         children_position = *letter- 65;
         
          if (temp->children[children_position]==NULL)
          {
            node * newnode;
            newnode = malloc(sizeof(node));
            temp->children[children_position] = newnode;
            for (int leaves=0; leaves<27; leaves++)
            {
                newnode ->children[leaves] = NULL;
            }
            newnode->is_word=false;
          }
       temp = temp ->children[children_position];

    }
    
}

 fclose(inptr);
 free(letter);
return true;
}


/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return word_counter;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
void free_all(node* curs);

bool unload(void)
{
//go through all points of the trie until you hit the last, start freeing memory

node *temp=root;

free_all(temp);
return true;

}

void free_all(node* curs)
{
    int i;
    if(!curs) return;   // safe guard including root node. 

    // recursive case (go to end of trie)
    for (i = 0; i < 27; i++)
       free_all(curs->children[i]);


    // base case
    free(curs);
}
