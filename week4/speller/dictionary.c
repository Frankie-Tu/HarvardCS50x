// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents number of buckets in a hash table
#define N 26

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Represents a hash table
node *hashtable[N];

// Hashes word to a number between 0 and 25, inclusive, based on its first letter
unsigned int hash(const char *word)
{
    return tolower(word[0]) - 'a';
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Initialize hash table
    for (int i = 0; i < N; i++)
    {
        hashtable[i] = NULL;
    }

    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }

    // Buffer for a word
    char word[LENGTH + 1];

    // Insert words into hash table
    while (fscanf(file, "%s", word) != EOF)
    {
        // new node for each word
        node *new_word = malloc(sizeof(node));

        // memory allocation didn't succeed
        if (new_word == NULL)
        {
            unload();
            return false;
        }
        else
        {
            strcpy(new_word->word, word);
        }

        int hash_val = hash(new_word->word);

        // get linkedlist from hashtable array, and if it is null
        if (hashtable[hash_val] == NULL)
        {
            new_word->next = NULL;
            hashtable[hash_val] = new_word;
        }
        else // not null
        {
            // prepend node to linkedlist
            new_word->next = hashtable[hash_val];
            hashtable[hash_val] = new_word;
        }
    }

    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    int word_count = 0;

    // count number of words in hashtable
    for (int i=0; i < N; i++)
    {
        node *head = hashtable[i];
        while (head != NULL)
        {
            head = head->next;
            word_count++;
        }
    }

    return word_count;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    node *cursor = hashtable[hash(word)];

    while (cursor != NULL)
    {
        // check if current node contains the word we are looking for
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }

    return false;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i=0; i < N; i++)
    {
        // find head
        node *currentNode = hashtable[i];

        while (currentNode != NULL)
        {
            node *temp = currentNode;
            currentNode = temp->next;
            free(temp);
        }
    }

    return true;
}
