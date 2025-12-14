def main():
    height = get_height()
    print_pyramid(height)


def get_height() -> int:
    while True:
        try:
            height = int(input("Height: "))
            if height < 1 or height > 8:
                continue

            return height
        except ValueError:
            pass


def print_pyramid(height: int) -> None:
    for lvl in range(1, height + 1):
        print(" " * (height - lvl), end="")
        print("#" * lvl)


if __name__ == "__main__":
    main()
