#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int calculate_score(string word);
void print_results(int score1, int score2);

int main(void) {
  while (true) {
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    int score1 = calculate_score(word1);
    int score2 = calculate_score(word2);

    print_results(score1, score2);
  }
}

int calculate_score(string word) {
  const char LETTER_POINTS[] = {
      1, 3, 3, 2,  1, 4, 2, 4, 1, 8, 5, 1, 3,
      1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10,
  };

  int score = 0;
  for (int i = 0, length = strlen(word); i < length; i++) {
    char c = toupper(word[i]);

    if (isalpha(c)) {
      score += LETTER_POINTS[c - 'A'];
    }
  }

  return score;
}

void print_results(int score1, int score2) {
  if (score1 > score2) {
    printf("Player 1 wins!\n");
  } else if (score2 > score1) {
    printf("Player 2 wins!\n");
  } else {
    printf("Tie!\n");
  }
}
