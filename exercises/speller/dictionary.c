// Implements a dictionary's functionality

#include <cs50.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct ht_node {
  char word[LENGTH + 1];
  struct ht_node *next;
} ht_node;

bool ht_put(unsigned int hash, char word[LENGTH + 1]);

// Choose number of buckets in hash table
enum { BUCKET_COUNT = 1000 };

// Hash table
ht_node *table[BUCKET_COUNT];
unsigned int word_count = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word) {
  unsigned int h = hash(word);
  if (!table[h]) {
    return false;
  }

  ht_node *head = table[h];
  while (head) {
    if (strcasecmp(head->word, word) == EXIT_SUCCESS) {
      return true;
    }

    head = head->next;
  }

  return false;
}

// Hashes word to a number
unsigned int hash(const char *word) {
  int sum = 0;
  for (int i = 0, length = strlen(word); i < length; i++) {
    if (isalpha(word[i])) {
      sum += toupper(word[i]) - 'A';
    } else {
      sum += word[i];
    }
  }

  return sum % BUCKET_COUNT;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary) {
  FILE *dictionary_file = fopen(dictionary, "r");
  if (!dictionary_file) {
    return false;
  }

  char word[LENGTH + 1];
  while (fscanf(dictionary_file, "%s", word) != EOF) {
    if (!ht_put(hash(word), word)) {
      fclose(dictionary_file);
      return false;
    }

    word_count++;
  }
  if (ferror(dictionary_file)) {
    fclose(dictionary_file);
    return false;
  }

  fclose(dictionary_file);
  return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void) { return word_count; }

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void) {
  for (int i = 0; i < BUCKET_COUNT; i++) {
    while (table[i]) {
      ht_node *head = table[i];
      table[i] = head->next;
      free(head);
    }
  }

  return true;
}

bool ht_put(unsigned int hash, char word[LENGTH + 1]) {
  ht_node *new = malloc(sizeof(ht_node));
  if (!new) {
    fprintf(stderr, "Memory Allocation failed.\n");
    return false;
  }

  // If has a collision
  if (table[hash]) {
    new->next = table[hash];
  } else {
    new->next = NULL;
  }

  strcpy(new->word, word);
  table[hash] = new;

  return true;
}
