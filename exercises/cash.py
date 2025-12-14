import math


def main():
    change = get_change()
    print(get_money_count(change))


def get_change() -> float:
    while True:
        try:
            change = float(input("Change: "))
            if change > 0:
                return change
        except ValueError:
            pass


def calc_change_and_fractions(change: float, currency: float) -> tuple[float, int]:
    fractions = math.floor(change / currency)
    change = round(change - fractions * currency, 2)

    return change, fractions


def get_money_count(change: float) -> int:
    currencies = [
        0.25,  # QUARTER
        0.1,  # DIME
        0.05,  # NICKEL
        0.01,  # PENNY
    ]

    money_count = 0
    for currency in currencies:
        if change == 0:
            return int(money_count)

        if change >= currency:
            change, fractions = calc_change_and_fractions(change, currency)
            money_count += fractions

    return int(money_count)


if __name__ == "__main__":
    main()
