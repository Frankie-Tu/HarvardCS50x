#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int checkifstring(char *arg);
char *encrypt(char *plaintext, char *encryption_keys);

int main(int argc, char *argv[])
{
    // check number of arguments, and if argv[1] is of integer value
    if (argc != 2 || checkifstring(argv[1]) == 1)
    {
        printf("Usage ./vigenere key\n");
        exit(1);
    }
    else
    {
        char *encryption_keys = argv[1];
        char *plaintext = get_string("plaintext: ");
        char *ciphertext = encrypt(plaintext, encryption_keys);
        printf("ciphertext: %s\n", ciphertext);
    }
}

int checkifstring(char *arg)
{
    // loop through characters in string
    for (int i = 0; i < strlen(arg); i++)
    {
        if (! isalpha(arg[i]))
        {
            // in case if any character is not a digit, return 1
            return 1;
        }
    }
    return 0;
}

char *encrypt(char *plaintext, char *encryption_keys)
{
    // encrypt string character by charater
    for (int i = 0; i < strlen(plaintext); i++)
    {
        int encryption_key;
        if (isalpha(plaintext[i]))
        {
            // convert current alphabetic value in encryption_keys to encryption_key
            encryption_key = tolower(encryption_keys[i % (strlen(encryption_keys))]) - 'a';

            // encrypting logic, cipher
            if (isupper(plaintext[i]))
            {
                plaintext[i] = 'A' + (plaintext[i] - 'A' + encryption_key) % 26;
            }
            else
            {
                plaintext[i] = 'a' + (plaintext[i] - 'a' + encryption_key) % 26;
            }
        }
    }
    return plaintext;
}
