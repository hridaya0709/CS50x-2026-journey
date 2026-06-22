from cs50 import get_string


def getCalculations(text):
    noOfLetters, noOfWords, noOfSentences = 0, 0, 0
    for i in range(len(text)):
        if text[i].isalpha():
            noOfLetters = noOfLetters + 1
        elif text[i] == " ":
            noOfWords = noOfWords + 1
        elif text[i] in [".", "?", "!"]:
            noOfSentences = noOfSentences + 1

    return noOfLetters, noOfWords+1, noOfSentences


def determineReadingGrade(index):
    if index <= 0 or index == 1:
        print("Before Grade 1")
    elif index > 1 and index <= 10:
        print("Grade", index)
    else:
        print("Grade 16+")


def getReadingGrade(text):
    noOfLetters, noOfWords, noOfSentences = getCalculations(text)

    L = noOfLetters * 100 / noOfWords
    S = noOfSentences * 100 / noOfWords

    # print("L:", L)
    # print("S:", S)

    index = round((0.0588 * L) - (0.296 * S) - 15.8)
    # print("index:", index)

    determineReadingGrade(index)


def main():
    text = get_string("Text: ")
    getReadingGrade(text)


main()
