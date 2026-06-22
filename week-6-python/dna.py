import csv
import sys


def fetch_headers_from_db_csv(argv_db_csv):
    headers = []
    with open(argv_db_csv, "r") as csv_file:
        csv_reader = csv.reader(csv_file)
        headers = next(csv_reader)
    # print(headers)
    return headers


def load_db_csv_entries(argv_db_csv, headers):
    dna_database = []
    with open(argv_db_csv) as csv_file:
        reader = csv.DictReader(csv_file)
        for row in reader:
            dict_row = {}

            for i in range(len(headers)):
                dict_row.update({headers[i]: row[headers[i]]})

            dna_database.append(dict_row)
    return dna_database


def get_dna_sequence(argv_dna_sequence):
    with open(argv_dna_sequence, "r") as file:
        sequence = file.read()
    return sequence


def create_longest_match_dict(sequence, headers):
    longest_match_dict = {}
    for i in headers:
        longest_match_dict[f"{i}_count"] = int(longest_match(sequence, i))
    return longest_match_dict


def print_result(dna_database, headers, longest_match_dict):
    for i in range(0, len(dna_database)):
        count = 0
        for j in range(1, len(headers)):

            # print(headers[j])
            database_value = str(int(dna_database[i][headers[j]]))
            longest_match_dict_value = str(longest_match_dict[f"{headers[j]}_count"])
            if longest_match_dict_value == database_value:
                count = count + 1

        if count == len(headers)-1:
            print(dna_database[i]["name"])
            break
    else:
        print("No match")


def main():

    # TODO: Check for command-line usage

    argv = sys.argv
    if (len(argv) != 3):
        print("Invalid command line arguments", len(sys.argv))
        return False

    # TODO: Read database file into a variable
    headers = fetch_headers_from_db_csv(argv[1])

    dna_database = load_db_csv_entries(argv[1], headers)

    # TODO: Read DNA sequence file into a variable
    sequence = get_dna_sequence(argv[2])

    # TODO: Find longest match of each STR in DNA sequence
    longest_match_dict = create_longest_match_dict(sequence, headers)

    # TODO: Check database for matching profiles
    print_result(dna_database, headers, longest_match_dict)

    return


def longest_match(sequence, subsequence):
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


main()
