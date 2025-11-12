#include <cs50.h>
#include <stdio.h>

bool is_even(int n);
int collatz(int n, int steps);
int collatz_doug(int n);

int main(void) {
  int n = get_int("Enter number: ");
  int steps = collatz_doug(n);
  printf("For the number %i, is required %i steps.\n", n, steps);
}

/**
 * Returns true if n is even
 */
bool is_even(int n) { return n % 2 == 0; }

/**
 * Calculates how many steps it takes to get to 1 if you start in n
 * Doug's version
 */
int collatz_doug(int n) {
  if (n <= 1) {
    return 0;
  }

  if (is_even(n)) {
    return 1 + collatz_doug(n / 2);
  } else {
    return 1 + collatz_doug(3 * n + 1);
  }
}

int collatz(int n, int steps) {
  if (n <= 1) {
    return steps;
  }

  steps++;
  if (is_even(n)) {
    return collatz(n / 2, steps);
  } else {
    return collatz(3 * n + 1, steps);
  }
}
