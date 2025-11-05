/**
 * In a file called readability.c in a folder called readability, you’ll
 * implement a program that calculates the approximate grade level needed to
 * comprehend some text. Your program should print as output “Grade X” where “X”
 * is the grade level computed, rounded to the nearest integer. If the grade
 * level is 16 or higher (equivalent to or greater than a senior undergraduate
 * reading level), your program should output “Grade 16+” instead of giving the
 * exact index number. If the grade level is less than 1, your program should
 * output “Before Grade 1”.
 */

#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

float calculate_coleman_liau_index(string text);
bool is_punctuation_symbol(char c);
void display_results(float index);

int main(void) {
  while (true) {
    string text = get_string("Text: ");

    float index = calculate_coleman_liau_index(text);
    display_results(index);
  }
}

/**
 * Returns true if the `c` is `.`, `!` or `?`
 */
bool is_punctuation_symbol(char c) {
  bool is_punctuation_symbol = false;
  int puntuation_symbols[] = {'.', '!', '?'};

  int puntuation_symbols_lenght = 3;
  for (int j = 0; j < puntuation_symbols_lenght; j++) {
    if (c == puntuation_symbols[j]) {
      is_punctuation_symbol = true;
      break;
    }
  }

  return is_punctuation_symbol;
}

/**
 * Returns the Coleman-Liau index
 * index = 0.0588 * L - 0.296 * S - 15.8
 * Where L is the average number of letters per 100 words in the text, and S is
 * the average number of sentences per 100 words in the text.
 */
float calculate_coleman_liau_index(string text) {

  float total_letters = 0;
  float total_sentences = 0;
  float total_words = 0;

  for (int i = 0, length = strlen(text); i < length; i++) {
    char c = text[i];

    if (isalpha(c)) { /* Count leters */
      total_letters++;
    } else if (is_punctuation_symbol(c)) { /* Count sentences */
      total_sentences++;
    }

    // Count total words
    if (c == ' ') {
      total_words++;
    } else if (i == (length - 1) && c != ' ' && total_words > 0) {
      total_words++;
    }
  }

  float L = total_letters / total_words * 100;
  float S = total_sentences / total_words * 100;

  return 0.0588 * L - 0.296 * S - 15.8;
}

void display_results(float index) {
  int rounded_index = lrintf(index);

  if (index < 1) {
    printf("Before Grade 1\n");
  } else if (index >= 16) {
    printf("Grade 16+\n");
  } else {
    printf("Grade %i\n", rounded_index);
  }
}
