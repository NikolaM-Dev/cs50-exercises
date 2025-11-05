#include <cs50.h>
#include <stdio.h>

bool valid_triangle(int a, int b, int c);

int main(void) {
  while (true) {
    int side1 = get_int("Side 1: ");
    int side2 = get_int("Side 2: ");
    int side3 = get_int("Side 3: ");

    if (valid_triangle(side1, side2, side3)) {
      printf("Valid\n");
    } else {
      printf("Invalid\n");
    }
  }
}

bool valid_triangle(int a, int b, int c) {
  // Sides must be positive
  if (a <= 0 || b <= 0 || c <= 0) {

    return false;
  }

  // Triangle inequality
  if (a + b <= c) {
    return false;
  } else if (a + c <= b) {
    return false;
  } else if (b + c <= a) {
    return false;
  }

  return true;
}
