import csv
import sys
from collections.abc import Collection

PersonRow = dict[str, str]
Match = dict[str, int]


def main():
    # Check for command-line usage
    if len(sys.argv) != 3:
        print(f"Usage {sys.argv[0]} <database> <sequence>")
        exit(1)
    database_filename = sys.argv[1]
    sequence_filename = sys.argv[2]

    # Read database file into a variable
    people: list[PersonRow] = []
    subsequences: list[str] = []
    with open(database_filename) as file:
        reader = csv.DictReader(file)
        fieldnames: Collection[str] | None = reader.fieldnames
        if fieldnames is None:
            print("database file is missing its header row")
            exit(1)

        subsequences = list(fieldnames[1:])
        for person in reader:
            people.append(person)

    # Read DNA sequence file into a variable
    sequence = ""
    with open(sequence_filename) as file:
        sequence = file.read()

    # Find longest match of each STR in DNA sequence
    matches: Match = {}
    for subsequence in subsequences:
        matches[subsequence] = longest_match(sequence, subsequence)

    # Check database for matching profiles
    for person in people:
        is_found = True
        for subsequence in subsequences:
            is_found = is_found and int(person[subsequence]) == matches[subsequence]
            if not is_found:
                break

        if is_found:
            print(person["name"])
            return

    print("No match")


def longest_match(sequence: str, subsequence: str) -> int:
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):
        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:
            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in sequence, return longest run found
    return longest_run


if __name__ == "__main__":
    main()
