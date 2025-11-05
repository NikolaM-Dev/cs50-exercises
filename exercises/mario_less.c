#include <cs50.h>
#include <stdio.h>

int main(void) {
  const int MAX_HEIGHT = 8;
  const int MIN_HEIGHT = 1;

  int height = 0;
  do {
    height = get_int("Height: ");
  } while (height > MAX_HEIGHT || height < MIN_HEIGHT);

  for (int row = MIN_HEIGHT; row <= height; row++) {
    for (int col = height; col >= MIN_HEIGHT; col--) {
      if (col <= row) {
        printf("#");
      } else {
        printf(" ");
      }
    }

    printf("\n");
  }
}
