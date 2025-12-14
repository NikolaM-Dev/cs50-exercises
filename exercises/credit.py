def main():
    card_number = get_card_number()
    if not is_valid_card_number(card_number):
        print("INVALID")
        return

    print_card_standard(card_number)


def get_card_number() -> int:
    """Returns the card number from the user and verifies that it's a proper int"""
    while True:
        try:
            card_number = int(input("Number: "))
            return card_number
        except ValueError:
            pass


def is_valid_card_number(card_number: int) -> bool:
    """Verifies the credit card's checksum using the Luhn's Algorithm"""
    sum = 0
    digits = [int(ch) for ch in str(card_number)]
    for i in range(len(digits) - 2, -1, -2):
        current = digits[i] * 2
        if current > 9:
            sum += 1 + (current % 10)
        else:
            sum += current

    for i in range(len(digits) - 1, -1, -2):
        sum += digits[i]

    return sum % 10 == 0


def print_card_standard(card_number: int) -> None:
    """Prints the standard of the Credit Card based on their number properties"""
    card_number_str = str(card_number)
    prefix = int(card_number_str[:2])
    size = len(card_number_str)

    if size == 15 and (prefix == 34 or prefix == 37):
        print("AMEX")
    elif size == 16 and (prefix >= 51 and prefix <= 55):
        print("MASTERCARD")
    elif (size == 13 or size == 16) and card_number_str[0] == "4":
        print("VISA")
    else:
        print("INVALID")


if __name__ == "__main__":
    main()
