#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

string printCipherText(int key, string plainText);
int getNormalizedKey(string argv);
bool isNonNumericKey(string argv);

int main(int argc, char *argv[])
{
    // printf("%i\n", argc);
    if (argc != 2)
    {
        printf("Invalid caeser key, try this : ./caeser key\n");
        return 1;
    }

    bool isNonNumeric = isNonNumericKey(argv[1]);

    if (isNonNumeric)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    int key = getNormalizedKey(argv[1]);

    if (key < 0)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    string plainText = get_string("plaintext:  ");

    string cipherText = printCipherText(key, plainText);

    printf("ciphertext: %s\n", cipherText);
}

bool isNonNumericKey(string argv)
{
    for (int i = 0; argv[i] != '\0'; i++)
    {
        if (isalpha(argv[i]) || !(isdigit(argv[i])))
        {
            return true;
        }
    }

    return false;
}

string printCipherText(int key, string plainText)
{
    string cipherText = plainText;
    // printf("ciphertext: %s\n", cipherText);
    for (int i = 0; plainText[i] != '\0'; i++)
    {
        int asc = plainText[i];
        // printf("asc: %i\n", asc);

        int assciiUpperMin = 65; // A
        int asciiUpperMax = 90;  // Z
        int asciiLowerMin = 97;  // a
        int asciiLowerMax = 122; // z

        if (islower(plainText[i]))
        {
            if ((asc + key) > asciiLowerMax)
            {
                // to wrap the counting around to the beginning of alphabets
                asc = asc + key - asciiLowerMax + (asciiLowerMin - 1);

                // printf("asc in if: %i\n", asc);
            }
            else
            {
                // else no wrapping is needed
                asc = asc + key;
            }
        }
        else if (isupper(plainText[i]))
        {
            if ((asc + key) > asciiUpperMax)
            {
                // to wrap the counting around to the beginning of alphabets
                asc = asc + key - asciiUpperMax + (assciiUpperMin - 1);

                // printf("asc in else if: %i\n", asc);
            }
            else
            {
                // else no warapping is needed
                asc = asc + key;
            }
        }

        // printf("asc + key: %i\n", asc);
        // printf("asc + key: %c\n", ((char) asc));

        cipherText[i] = (char) (asc);
        // printf("ciphertext[i]: %c\n", cipherText[i]);
    }

    return cipherText;
}

int getNormalizedKey(string argv)
{
    int key = atoi(argv);
    // printf("key: %i\n", key);
    key = key % 26; // Reducing the key to stay within (0, 26) range
    // printf("key: %i\n", key);
    return key;
}
