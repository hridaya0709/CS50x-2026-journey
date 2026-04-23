#include <cs50.h>
#include <stdio.h>

int findNoOfCoinsToBeReturned(int changeOwed);

int main(void)
{
    int changeOwed;

    // Prompt user for change owed and checking for negative entries
    do
    {
        changeOwed = get_int("Change owed: ");

        if (changeOwed >= 0)
            break;
    }
    while (changeOwed < 0);

    int noOfCoins = findNoOfCoinsToBeReturned(changeOwed);

    printf("%i\n", noOfCoins);
}

int findNoOfCoinsToBeReturned(int changeOwed)
{
    int noOfCoins = 0;

    // Following greedy pattern to find the minimum no. of coins needed
    for (int i = changeOwed; i > 0;)
    {
        if (i >= 25)
        {
            noOfCoins++;
            i -= 25;
        }
        else if (i >= 10)
        {
            noOfCoins++;
            i -= 10;
        }
        else if (i >= 5)
        {
            noOfCoins++;
            i -= 5;
        }
        else
        {
            noOfCoins++;
            i -= 1;
        }
    }

    return noOfCoins;
}
