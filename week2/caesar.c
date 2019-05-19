#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int checkifint(string arg);
string encrypt(string plaintext, int encrypt_key);

int main(int argc, string argv[])
{
    // check number of arguments, and if argv[1] is of integer value
    if (argc != 2 || checkifint(argv[1]) == 1)
    {
        printf("Usage ./caesar key\n");
        exit(1);
    }
    else
    {
        int encryption_key = atoi(argv[1]);
        string plaintext = get_string("plaintext: ");
        string ciphertext = encrypt(plaintext, encryption_key);
        printf("ciphertext: %s\n", ciphertext);
    }
}

int checkifint(string arg)
{
    // loop through characters in string (char[])
    for (int i = 0; i < strlen(arg); i++)
    {
        if (! isdigit(arg[i]))
        {
            // in case if any character is not a digit, return 1
            return 1;
        }
    }
    return 0;
}

string encrypt(string plaintext, int encrypt_key)
{
    // encrypt string character by charater
    for (int i = 0; i < strlen(plaintext); i++)
    {
        if (isalpha(plaintext[i]))
        {
            // encripting logic, cipher
            if (isupper(plaintext[i]))
            {
                plaintext[i] = 'A' + (plaintext[i] - 'A' + encrypt_key) % 26;
            }
            else
            {
                plaintext[i] = 'a' + (plaintext[i] - 'a' + encrypt_key) % 26;
            }
        }   
    }
    return plaintext;
}

