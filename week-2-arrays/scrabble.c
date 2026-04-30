#include <cs50.h>
#include <ctype.h>
#include <stdio.h>

int calculateScore(string player);
string compareScores(string player1, string player2);
int *initializeScoresArray(void);

int main(void)
{
    string player1 = get_string("Player 1: ");
    string player2 = get_string("Player 2: ");

    printf("%s\n", compareScores(player1, player2));
}

string compareScores(string player1, string player2)
{
    int score1 = calculateScore(player1);
    int score2 = calculateScore(player2);

    string result;

    if (score1 > score2)
    {
        result = "Player 1 wins!";
    }
    else if (score1 < score2)
    {
        result = "Player 2 wins!";
    }
    else
    {
        result = "Tie!";
    }

    return result;
}

int calculateScore(string player)
{
    int score = 0;

    int *scoresArray = initializeScoresArray();

    const int upperCaseStartValue = 65;
    const int lowerCaseStartValue = 97;

    for (int i = 0; player[i] != '\0'; i++)
    {
        int c = player[i];

        if (isupper(player[i]))
        {
            score += scoresArray[c - upperCaseStartValue];
        }
        else if (islower(player[i]))
        {
            score += scoresArray[c - lowerCaseStartValue];
        }
    }

    // printf("%i\n", score);
    return score;
}

int *initializeScoresArray(void)
{
    static int scoresArray[26];
    scoresArray[0] = 1;   // A
    scoresArray[1] = 3;   // B
    scoresArray[2] = 3;   // C
    scoresArray[3] = 2;   // D
    scoresArray[4] = 1;   // E
    scoresArray[5] = 4;   // F
    scoresArray[6] = 2;   // G
    scoresArray[7] = 4;   // H
    scoresArray[8] = 1;   // I
    scoresArray[9] = 8;   // J
    scoresArray[10] = 5;  // K
    scoresArray[11] = 1;  // L
    scoresArray[12] = 3;  // M
    scoresArray[13] = 1;  // N
    scoresArray[14] = 1;  // O
    scoresArray[15] = 3;  // P
    scoresArray[16] = 10; // Q
    scoresArray[17] = 1;  // R
    scoresArray[18] = 1;  // S
    scoresArray[19] = 1;  // T
    scoresArray[20] = 1;  // U
    scoresArray[21] = 4;  // V
    scoresArray[22] = 4;  // W
    scoresArray[23] = 8;  // X
    scoresArray[24] = 4;  // Y
    scoresArray[25] = 10; // Z

    return scoresArray;
}
