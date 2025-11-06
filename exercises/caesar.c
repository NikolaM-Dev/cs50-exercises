#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int print_error(string program_name);
bool is_int(string key);
string encipher(string plaintext, int key);

int main(int argc, string argv[]) {
  if (argc == 1 || argc > 2) {
    return print_error(argv[0]);
  }

  if (!is_int(argv[1])) {
    return print_error(argv[0]);
  }

  string plaintext = get_string("plaintext:  ");

  int key = atoi(argv[1]);
  string ciphertext = encipher(plaintext, key);

  printf("ciphertext: %s\n", ciphertext);
  return 0;
}

/**
 * Prints the error message and return 1 as the error code
 */
int print_error(string program_name) {
  printf("Usage: %s key\n", program_name);
  return 1;
}

/**
 * Verify if an ASCII is an int
 */
bool is_int(string key) {
  bool is_digit = true;

  for (int i = 0, length = strlen(key); i < length; i++) {
    if (!isdigit(key[i])) {
      is_digit = false;
      break;
    }
  }

  return is_digit;
}

/**
 * Applies the Caesar's algorithm to encipher the payload
 */
string encipher(string plaintext, int key) {
  int plaintext_lenght = strlen(plaintext);
  string ciphertext = plaintext;

  for (int i = 0; i < plaintext_lenght; i++) {
    char c = plaintext[i];

    if (!isalpha(c)) {
      continue;
    }

    if (isupper(c)) {
      ciphertext[i] = (c - 'A' + key) % 26 + 'A';
    } else {
      ciphertext[i] = (c - 'a' + key) % 26 + 'a';
    }
  }

  return ciphertext;
}
