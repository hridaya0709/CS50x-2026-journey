#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

void getReadingGrade(string text);
int *getCalculations(string text);
float calculateAverage(int n1, int n2);
void determineReadingGrade(int index);

int main(void)
{
    string text = get_string("Text: ");

    getReadingGrade(text);
}

void getReadingGrade(string text)
{
    int *calculations = getCalculations(text);

    int noOfLetters = calculations[0];
    int noOfWords = calculations[1];
    int noOfSentences = calculations[2];

    // printf("No of letters: %i\n", noOfLetters);
    // printf("No of words: %i\n", noOfWords);
    // printf("No of sentences: %i\n", noOfSentences);

    // Coleman-Liau index = 0.0588 * L - 0.296 * S - 15.8
    // where L is the average number of letters per 100 words in the text,
    // and S is the average number of sentences per 100 words in the text.

    float L = calculateAverage(noOfLetters, noOfWords);
    float S = calculateAverage(noOfSentences, noOfWords);

    // printf("L: %f\n", L);
    // printf("S: %f\n", S);

    int index = round((0.0588 * L) - (0.296 * S) - 15.8);

    // printf("index: %i\n", index);

    determineReadingGrade(index);
}

float calculateAverage(int n1, int n2)
{
    float avg = (float) n1 * 100 / n2;

    // printf("n1: %i\n", n1);
    // printf("n2: %i\n", n2);
    // printf("avg: %f\n", avg);

    return avg;
}

int *getCalculations(string text)
{
    static int calculations[3];

    int noOfLetters = 0;
    int noOfWords = 0;
    int noOfSentences = 0;
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (isalpha(text[i]))
        {
            noOfLetters++;
        }
        if (text[i] == ' ')
        {
            noOfWords++;
        }
        if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            noOfSentences++;
        }
    }

    calculations[0] = noOfLetters;
    calculations[1] = ++noOfWords;
    calculations[2] = noOfSentences;

    return calculations;
}

void determineReadingGrade(int index)
{
    if (index <= 0 || index == 1)
    {
        printf("%s\n", "Before Grade 1");
    }
    else if (index >= 1 && index <= 10)
    {
        printf("%s %i\n", "Grade", index);
    }
    else
    {
        printf("%s\n", "Grade 16+");
    }
}
