#include <cs50.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int print_error(string program_name);
string str_copy(string payload);
string str_upper(string payload);
bool is_valid_key(string key);
string substitution(string plaintext, string key);

int main(int argc, string argv[]) {
  if (argc != 2) {
    return print_error(argv[0]);
  }

  string key = str_upper(argv[1]);

  if (!is_valid_key(key)) {
    free(key);
    return print_error(argv[0]);
  }

  string plaintext = get_string("plaintext:  ");
  string ciphertext = substitution(plaintext, key);

  printf("ciphertext: %s\n", ciphertext);

  free(key);
  free(ciphertext);

  return 0;
}

/**
 * Shows an error message explaining the usage of the program
 */
int print_error(string program_name) {
  printf("Usage: %s [key]\n", program_name);
  printf("\nKey must contain 26 unique alphabetic characters.\n");

  return 1;
}

/**
 * Creates a copy of a string
 */
string str_copy(string payload) {
  string copy = malloc(strlen(payload) + 1);
  if (copy == NULL) {
    printf("Memory allocation failed.\n");
    exit(1);
  }

  return strcpy(copy, payload);
}

/**
 * Returns an uppercase version of the string
 */
string str_upper(string payload) {
  string copy = str_copy(payload);

  for (int i = 0, length = strlen(copy); i < length; i++) {
    char c = copy[i];
    if (isalpha(c)) {
      copy[i] = toupper(c);
    }
  }

  return copy;
}

/**
 * Verify if the key has a length of 26 and each character is a unique letter in
 * the alphabet
 */
bool is_valid_key(string key) {
  int key_length = strlen(key);
  if (key_length != 26) {
    return false;
  }

  bool alphabet[26] = {false};
  for (int i = 0; i < key_length; i++) {
    char c = key[i];
    if (!isalpha(c)) {
      return false;
    }

    int index = c - 'A';
    if (alphabet[index]) {
      return false; // Character is duplicated
    }
    alphabet[index] = true;
  }

  return true;
}

/**
 * Cipher the plaintext using the key
 */
string substitution(string plaintext, string key) {
  string ciphertext = str_copy(plaintext);
  for (int i = 0, length = strlen(plaintext); i < length; i++) {
    char c = plaintext[i];
    if (!isalpha(c)) {
      continue;
    }

    if (isupper(c)) {
      ciphertext[i] = key[c - 'A'];
    } else {
      ciphertext[i] = tolower(key[c - 'a']);
    }
  }

  return ciphertext;
}
