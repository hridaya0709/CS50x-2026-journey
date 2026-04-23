#include <cs50.h>
#include <stdbool.h>
#include <stdio.h>

void findCreditType(long creditNo);
int findLength(long creditNo);
long findSubPart(int n, long creditNo);
bool isCheckSumValid(long creditNo);
int findSumOfDigits(int twiceOfCurrentLastDigit);

const string invalid = "INVALID\n";

int main(void)
{
    // Taking credit number as input from the user
    long creditNo = get_long("Enter the credit card number: ");

    // printf("length: %i\n", findLength(creditNo));
    // printf("From calculateCheckSum: %s\n", calculateCheckSum(creditNo));

    // Calculating the checkSum of the credit number and validating it
    bool checkSumValidOrInvalid = isCheckSumValid(creditNo);

    if (checkSumValidOrInvalid)
    {
        // if checkSum is valid, find the credit type
        findCreditType(creditNo);
    }
    else
    {
        // if checkSum is invalid, print INVALID
        printf("%s", invalid);
    }
}

bool isCheckSumValid(long creditNo)
{
    int checkSum = 0;
    int currentLastDigit;
    bool result = false;

    for (long i = creditNo, counter = 1; i > 0; i /= 10)
    {
        currentLastDigit = i % 10;
        if (counter % 2 == 0)
        {
            int twiceOfCurrentLastDigit = currentLastDigit * 2;

            if (twiceOfCurrentLastDigit > 9)
            {
                twiceOfCurrentLastDigit = findSumOfDigits(twiceOfCurrentLastDigit);
            }

            checkSum += twiceOfCurrentLastDigit; // Add sum of the digits of the product
        }
        else
        {
            checkSum += currentLastDigit;
        }
        counter++;
    }

    // printf("checkSum: %i\n", checkSum);
    if (checkSum % 10 == 0)
    {
        result = true;
    }

    return result;
}

int findSumOfDigits(int twiceOfCurrentLastDigit)
{
    int sumOfDigits = 0;

    for (int i = twiceOfCurrentLastDigit; i > 0; i /= 10)
    {
        sumOfDigits += (i % 10);
    }

    return sumOfDigits;
}

// American Express - 15 digits, starts with 34 or 37
// MasterCard - 16 digits, starts with 51, 52, 53, 54, 55
// Visa - 13 or 16 digits, starts with 4
void findCreditType(long creditNo)
{
    int length = findLength(creditNo);

    if (length == 15 && (findSubPart(2, creditNo) == 34 || findSubPart(2, creditNo) == 37))
    {
        printf("AMEX\n");
    }
    else if (length == 16 && (findSubPart(2, creditNo) == 51 || findSubPart(2, creditNo) == 52 ||
                              findSubPart(2, creditNo) == 53 || findSubPart(2, creditNo) == 54 ||
                              findSubPart(2, creditNo) == 55))
    {
        printf("MASTERCARD\n");
    }
    else if ((length == 13 || length == 16) && findSubPart(1, creditNo) == 4)
    {
        printf("VISA\n");
    }
    else
    {
        printf("%s", invalid);
    }
}

long findSubPart(int n, long creditNo)
{
    long subPart = 0;
    for (long i = creditNo; i > 0; i /= 10)
    {
        if (findLength(i) == n)
        {
            subPart = i;
            break;
        }
    }
    // printf("subPart: %li\n", subPart);
    return subPart;
}

int findLength(long creditNo)
{
    int length = 0;
    for (long i = creditNo; i > 0; i /= 10)
    {
        length++;
    }
    return length;
}
