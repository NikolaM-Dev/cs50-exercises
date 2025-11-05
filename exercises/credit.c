#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * From long to ASCII
 */
string ltoa(long number) {
  char *buffer;
  buffer = malloc(21);
  sprintf(buffer, "%li", number);

  return buffer;
}

/**
 * From character to ASCII
 */
string ctoa(char c) {
  char *buffer;
  buffer = malloc(2);
  sprintf(buffer, "%c", c);

  return buffer;
}

/**
 * From character to int
 */
int ctoi(char c) { return atoi(ctoa(c)); }

/**
 * From int to ASCII
 */
string itoa(int number) {
  char *buffer;
  buffer = malloc(sizeof(int));
  sprintf(buffer, "%i", number);

  return buffer;
}

/**
 * It's AMEX, If the card has 15 digits and starts with 34 or 37
 */
bool get_is_amex(long credit_card_number) {
  string s_credit_card_number = ltoa(credit_card_number);
  if (strlen(s_credit_card_number) != 15) {
    return false;
  }

  // Get first to characters
  char buffer[3];
  sprintf(buffer, "%c%c", s_credit_card_number[0], s_credit_card_number[1]);
  int first_2_digits = atoi(buffer);

  return first_2_digits == 34 || first_2_digits == 37;
}

/**
 * It's MASTERCARD, If the card has 16 digits and starts with 51, 52, 53, 54, or
 * 55
 */
bool get_is_mastercard(long credit_card_number) {
  string s_credit_card_number = ltoa(credit_card_number);
  if (strlen(s_credit_card_number) != 16) {
    return false;
  }

  // Get first to characters
  char buffer[3];
  sprintf(buffer, "%c%c", s_credit_card_number[0], s_credit_card_number[1]);
  int first_2_digits = atoi(buffer);

  return first_2_digits >= 51 && first_2_digits <= 55;
}

/**
 * It's VISA, If the card has 13 or 16 digits and starts with 4
 */
bool get_is_visa(long credit_card_number) {
  string s_credit_card_number = ltoa(credit_card_number);
  int card_length = strlen(s_credit_card_number);
  if (card_length != 16 && card_length != 13) {
    return false;
  }

  int first_digit = atoi(ctoa(s_credit_card_number[0]));

  return first_digit == 4;
}

/**
 * Luhn’s Algorithm
 */
bool get_is_valid_checksum(long credit_card_number) {
  string s_credit_card_number = ltoa(credit_card_number);

  int counter = 0;

  /**
   * Multiply every other digit by 2, starting with the number's second-to-last
   * digit, and then add those products' digits together.
   */
  for (int i = strlen(s_credit_card_number) - 2; i >= 0; i -= 2) {
    int digit = ctoi(s_credit_card_number[i]);
    int double_digit = digit * 2;

    if (double_digit < 10) {
      counter += double_digit;
    } else {
      string s_digit = itoa(double_digit);
      counter += ctoi(s_digit[0]);
      counter += ctoi(s_digit[1]);
    }
  }

  // Add the sum to the sum of the digits that weren't multiplied by 2.
  for (int i = strlen(s_credit_card_number) - 1; i >= 0; i -= 2) {
    int digit = ctoi(s_credit_card_number[i]);
    counter += digit;
  }

  /**
   * If the total's last digit is 0 (or, put more formally, if the total modulo
   * 10 is congruent to 0), the number is valid!
   */
  return counter % 10 == 0;
}

int main(void) {
  while (true) {
    long credit_card_number = get_long("Number: ");

    bool is_valid_checksum = get_is_valid_checksum(credit_card_number);
    if (!is_valid_checksum) {
      printf("INVALID\n");
      exit(0);
    }

    bool is_amex = get_is_amex(credit_card_number);
    bool is_mastercard = get_is_mastercard(credit_card_number);
    bool is_visa = get_is_visa(credit_card_number);

    if (is_amex) {
      printf("AMEX\n");
    } else if (is_mastercard) {
      printf("MASTERCARD\n");
    } else if (is_visa) {
      printf("VISA\n");
    } else {
      printf("Payment Network not supported.\n");
    }
  }
}
