PUNCTUATION_SYMBOLS = frozenset({".", "!", "?"})


def main():
    text = get_text()
    grade = calc_index(text)
    display_grade(grade)


def get_text() -> str:
    """Read a non-empty line of text from the user."""
    while True:
        text = input("Text: ").strip()
        if text:
            return text


def calc_index(text: str) -> float:
    """Compute the Coleman-Liau index for the supplied text."""
    words = text.split()
    if not words:
        raise ValueError("text must contain at least one word")

    letters = sum(1 for c in text if c.isalpha())
    sentences = sum(1 for c in text if c in PUNCTUATION_SYMBOLS)

    total_words = len(words)
    L = letters / total_words * 100
    S = sentences / total_words * 100

    return 0.0588 * L - 0.296 * S - 15.8


def display_grade(grade: float) -> None:
    """Show a user-friendly grade label for the index."""
    index = round(grade)
    if index < 1:
        print("Before Grade 1")
    elif index >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {index}")


if __name__ == "__main__":
    main()
