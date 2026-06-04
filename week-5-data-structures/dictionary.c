// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 156;

// Hash table
node *table[N];
FILE *dict;

int count = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    unsigned int hashValue = hash(word);

    node *n1 = table[hashValue];
    while (n1 != NULL)
    {
        char *s = n1->word;
        if (strcasecmp(s, word) == 0)
        {
            return true;
        }
        n1 = n1->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    // return toupper(word[0]) - 'A';
    // return (strlen(word)-1);

    int ascii = toupper(word[0]) - 'A';
    int secondIndex = 0;
    if ('A' == toupper(word[1]))
    {
        secondIndex = 1;
    }
    else if ('E' == toupper(word[1]))
    {
        secondIndex = 2;
    }
    else if ('I' == toupper(word[1]))
    {
        secondIndex = 3;
    }
    else if ('O' == toupper(word[1]))
    {
        secondIndex = 4;
    }
    else if ('U' == toupper(word[1]))
    {
        secondIndex = 5;
    }

    return (6 * ascii) + secondIndex;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    dict = fopen(dictionary, "r");

    if (dict == NULL)
    {
        printf("dict is null");
        return false;
    }

    char string[LENGTH + 1];
    while (fscanf(dict, "%s", string) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            printf("n is null");
            fclose(dict);
            return false;
        }

        strcpy(n->word, string);
        n->next = NULL;

        unsigned int hashValue = hash(string);

        n->next = table[hashValue];
        table[hashValue] = n;

        count++;
    }

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    int status = fclose(dict);

    for (int i = 0; i < N; i++)
    {
        node *a = table[i];

        while (a != NULL)
        {
            node *b = a;
            a = a->next;
            free(b);
        }
    }

    if (status == 0)
    {
        return true;
    }
    return false;
}
