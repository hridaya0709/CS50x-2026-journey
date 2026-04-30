#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

bool validateKey(string key);
bool areNotUniqueAlpha(string key);
bool isAlphaNumKey(string key);
string generateCipherText(string plainText, string key);
string getAlphaArray(void);
int findCharacterIndex(char plainTextChar, string alphaArray);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Invalid key\n");
        return 1;
    }

    string key = argv[1];
    bool isInvalidKey = validateKey(key);

    // printf("%i\n", isInvalid);
    if (isInvalidKey)
    {
        return 1;
    }

    string plainText = get_string("plaintext: ");

    printf("ciphertext: %s\n", generateCipherText(plainText, key));

    return 0;
}

string generateCipherText(string plainText, string key)
{
    string alphaArray = getAlphaArray();
    string cipherText = plainText;

    for (int i = 0; cipherText[i] != '\0'; i++)
    {
        if (islower(plainText[i]))
        {
            int index = findCharacterIndex(toupper(plainText[i]), alphaArray);
            cipherText[i] = tolower(key[index]);
        }
        else if (isupper(plainText[i]))
        {
            int index = findCharacterIndex(plainText[i], alphaArray);
            cipherText[i] = toupper(key[index]);
        }
        else
        {
            cipherText[i] = plainText[i];
        }
    }

    return cipherText;
}

int findCharacterIndex(char plainTextChar, string alphaArray)
{
    for (int i = 0; i < 26; i++)
    {
        if (alphaArray[i] == plainTextChar)
        {
            return i;
        }
    }

    return -1;
}

bool validateKey(string key)
{
    if (strlen(key) != 26)
    {
        printf("Length of the key must be 26\n");
        return true;
    }

    if (isAlphaNumKey(key))
    {
        printf("Key must contain all alphabetic characters only\n");
        return true;
    }

    if (areNotUniqueAlpha(key))
    {
        printf("All alphabets should be unique and should be repeated only once in the key\n");
        return true;
    }

    return false;
}

bool isAlphaNumKey(string key)
{
    bool result = false;
    for (int i = 0; key[i] != '\0'; i++)
    {
        if (!(isalpha(key[i])) || isdigit(key[i]))
        {
            result = true;
            // printf("isAlphaNumKey inside for: %i\n", result);
            return result;
        }
    }

    // printf("isAlphaNumKey outside for: %i\n", result);
    return result;
}

bool areNotUniqueAlpha(string key)
{
    bool result = false;

    // printf("%s\n", argv);

    char alpha[26];
    for (int i = 0; i < 26; i++)
    {
        alpha[i] = '0';
        key[i] = toupper(key[i]);
    }

    for (int i = 0; i < 26; i++)
    {
        int asc = key[i];
        // printf("asc: %i\n", asc);
        // printf("alpha[i] %c\n", alpha[i]);
        if (alpha[asc - 65] == '0')
        {
            alpha[asc - 65] = key[i];
            // printf("alpha[asc - 65]: %c\n", alpha[asc - 65]);
            // printf("argv[i]: %c\n", argv[i]);
        }
        else
        {
            result = true;
            // printf("areNotUniqueAlpha inside for: %i\n", result);
            return result;
        }
    }

    // printf("areNotUniqueAlpha outside for: %i\n", result);

    // printf("alpha: %s\n", alpha);
    return result;
}

string getAlphaArray(void)
{
    string alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    return alpha;
}
