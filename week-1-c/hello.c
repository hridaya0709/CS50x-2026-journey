#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Prompt the user for their name and greet them
    string name = get_string("What is your name? ");

    // Greeting hello, [name]
    printf("hello, %s\n", name);
}
