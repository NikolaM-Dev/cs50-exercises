#include <cs50.h>
#include <stdio.h>

int calculate_fraction(int cents, int fraction) { return cents / fraction; }

int calculate_remaining_cents(int cents, int fraction) {
  return cents % fraction;
}

int main(void) {
  const int DIME = 10;
  const int NICKEL = 5;
  const int PENNY = 1;
  const int QUARTER = 25;

  int cents = 0;
  do {
    cents = get_int("Change owed: ");
  } while (cents <= 0);

  int remaining_cents = cents;
  int result = 0;

  result += calculate_fraction(remaining_cents, QUARTER);
  remaining_cents = calculate_remaining_cents(remaining_cents, QUARTER);

  result += calculate_fraction(remaining_cents, DIME);
  remaining_cents = calculate_remaining_cents(remaining_cents, DIME);

  result += calculate_fraction(remaining_cents, NICKEL);
  remaining_cents = calculate_remaining_cents(remaining_cents, NICKEL);

  result += calculate_fraction(remaining_cents, PENNY);
  remaining_cents = calculate_remaining_cents(remaining_cents, PENNY);

  printf("%i\n", result);
}
