#include <cs50.h>
#include <stdio.h>

int getAndValidateUserInput(void);

int main(void)
{
    int user_input = getAndValidateUserInput();

    // For every row
    for (int row = 0; row < user_input; row++)
    {
        // First part of the row, prints the first triangle
        for (int colPart1 = (user_input - 1); colPart1 >= 0; colPart1--)
        {
            if (row >= colPart1)
            {
                printf("#");
            }
            else
            {
                printf(" ");
            }
        }

        // Maintains the 2-# space between two triangles
        for (int colPart2 = 0; colPart2 < 2; colPart2++)
        {
            printf(" ");
        }

        // Prints the second triangle
        for (int colPart3 = 0; colPart3 < user_input; colPart3++)
        {
            if (row >= colPart3)
            {
                printf("#");
            }
        }

        printf("\n");
    }
}

// Gets the input from the user and validates it for negative numbers, 0,
// greater than or equals to 9 and any empty or non empty strings
int getAndValidateUserInput(void)
{
    int user_input;

    do
    {
        user_input = get_int("Provide the input number: ");
    }
    while (user_input <= 0 || (user_input > 0 && user_input >= 9));

    return user_input;
}
